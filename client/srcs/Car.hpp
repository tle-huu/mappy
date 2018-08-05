#pragma once

#include "mappy_client.hpp"
#include "AI.hpp"
#include "CommunicationSocket.hpp"

class	Car
{
	Position _current_pos;
	Position _destination;
	AI* _ai;
	CommunicationSocket _communicator;
	double _cooldown;

public:

	Car();
	~Car();

	void	update(double dt);
}
