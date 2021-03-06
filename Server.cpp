#include "Server.h"
#include "PacketType.h"
#include <iostream>

Server::Server(unsigned short port)
{
	listener.listen(port);
	listener.setBlocking(false);
}

Server::~Server()
{
}

void Server::handlePackets()
{
	//handle incoming data
	for(Clients::iterator it=clients.begin(); it!=clients.end();)
	{
		sf::Packet packet;
		sf::Socket::Status status=it->first->receive(packet);

		switch (status)
		{
		case sf::Socket::Done:
			PacketType type;
			packet>>type;
			if(type==INITIAL_NAME_DATA)
			{
				//store the name
				packet>>it->second;
				//std::cout<<it->second<<" has joined\n";
				broadCast(INITIAL_NAME_DATA, it->second+" has joined\n");
			}
			else if(type==GENERAL_MSG)
			{
				std::string msg;
				packet>>msg;
				//std::cout<<it->second<<": "<<msg<<"\n";
				broadCast(GENERAL_MSG, it->second+": "+msg);
			}
			++it;
			break;

		case sf::Socket::Disconnected:
			//std::cout<<it->second<<" has been disconnected\n";
			broadCast(GENERAL_MSG, it->second+" has been disconnected\n");
			it=clients.erase(it);
			break;

		default:
			++it;
		}
	}
}

void Server::broadCast(PacketType type, const std::string & msg)
{
	for(Clients::iterator it=clients.begin(); it!=clients.end(); ++it)
	{
		sf::Packet pack;
		pack<<type<<msg;
		it->first->send(pack);
	}
}

void Server::run()
{

	sf::TcpSocket * nextClient=nullptr;
	while(1)
	{
		//Handle newcoming clients
		if(nextClient==nullptr)
		{
			nextClient=new sf::TcpSocket;
			nextClient->setBlocking(false);
		}
		if(listener.accept(*nextClient) == sf::Socket::Done)
		{
			clients.insert(std::make_pair(nextClient, ""));
			nextClient=nullptr;
		}
		handlePackets();
	}
}

int main()
{
	Server server(53000);
	server.run();
	return 0;
}

