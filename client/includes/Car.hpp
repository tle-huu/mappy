#pragma once

#include "Ai.class.hpp"
#include "CommunicationSocket.hpp"
#include <unordered_map>

class	Car
{
	Position _current_pos;
	Position _destination;
	Ai* _ai;
	CommunicationSocket _communicator;
	Map _map;
	std::unordered_map<std::string, std::function<void(std::string)>> _events;

public:

	Car(const char * addr, int port);
	~Car();

	void	move();
};
