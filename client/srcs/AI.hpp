#pragma once

#include "mappy_client.hpp"
#include <utility>

class	AI
{
	Map& _map;

public:
	AI(Map& map);

	Position	where_to(Position current, Position dest, double& cooldown);
};
