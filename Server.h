#ifndef SERVER_H
#define SERVER_H
#include <unordered_map>
#include "SFML/Network.hpp"
#include "PacketType.h"
#include <vector>

class Server
{
private:
	typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
	Clients clients;
	sf::TcpListener listener;

	void handlePackets();
	void broadCast(PacketType type, const std::string & msg);
public:
	Server(unsigned short port);
	~Server();

	void run();
};

#endif

