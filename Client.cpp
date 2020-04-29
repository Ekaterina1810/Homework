#include "Client.h"
#include "PacketType.h"
#include <iostream>
#include "ChatBox.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Client::Client(const std::string & name_):name(name_)
{

}

Client::~Client(void)
{
}

//sf::Socket::Status Client::connect(const sf::IpAddress & IP, unsigned short port)
sf::Socket::Status Client::connect()
{
	//connect to server
	sf::Socket::Status stat= me.connect("127.0.0.1", 53000);
	me.setBlocking(false);
	return stat;
}

sf::Socket::Status Client::send (PacketType type, const std::string & msg)
{
	sf::Packet packet;
	packet<<type<<msg;
	return me.send(packet);
}

sf::Socket::Status Client::receive(std::string & msg)
{
	sf::Packet packet;
	sf::Socket::Status status=me.receive(packet);
	PacketType type;
	packet>>type;
	if(status==sf::Socket::Done)
	{
		//std::cout<<msg<<"\n";
		packet>>msg;
	}
	return status;
}

int main()
{
	std::string name;
	std::cout<<"What's your name: ";
	std::getline(std::cin, name);
	std::cout<<"\n";
	Client client(name);

	sf::Socket::Status status;
	status=client.connect();

	if(status!=sf::Socket::Done)
	{
		std::cout<<"Sorry we couldn't connect\n";
		return -1;
	}
	client.send(INITIAL_NAME_DATA, name);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Chat window");
	sf::Font font;
	font.loadFromFile("ubuntu.ttf");
	ChatBox chatBox(sf::Vector2f(50, 100), 500, 5, 20, 15, font);
	chatBox.setFillColor(sf::Color::White);
	chatBox.setOutlineColor(sf::Color::Black);
	chatBox.setCharColor(sf::Color::Black);
	chatBox.connectOnEnter([&](const std::string & s){client.send(GENERAL_MSG, s);});

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
				window.close();
			chatBox.handleEvent(event);
		}
		std::string toBePushed;

		sf::Socket::Status status=client.receive(toBePushed);
		if(status==sf::Socket::Done)
		{
			//std::cout<<toBePushed<<"\n";
			chatBox.push(toBePushed);
		}
		else if(status==sf::Socket::Disconnected)
		{
			chatBox.push("You have been disconnected");
			chatBox.draw(window);
			window.display();
			sf::sleep(sf::seconds(2));
			return -1;
		}

		window.clear(sf::Color::White);
		chatBox.update();
		chatBox.draw(window);
		window.display();
	}
}
