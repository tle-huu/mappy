#pragma once

#include "mappy_client.hpp"
#include <utility>

class	AI
{
	Map _map;

public:
	AI(const Map& map);

	Position	where_to(Position current, Position dest, double& cooldown);
	void		update(std::vector<std::pair<Position, Position>>);
};
