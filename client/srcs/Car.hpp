#pragma once

#include "mappy_client.hpp"
#include "AI.hpp"
#include "CommunicationSocket.hpp"
#include <unordered_map>

class	Car
{
	Position _current_pos;
	Position _destination;
	AI _ai;
	CommunicationSocket _communicator;
	Map _map;
	std::unordered_map<std::string, std::function<void(std::string)>> _events;

public:

	Car();
	~Car();

	void	move();
};
