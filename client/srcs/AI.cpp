#include "AI.hpp"

AI::AI(const Map& map) : _map(map)
{
}

Position	AI::where_to(Position current, Position dest, double& cooldown)
{
}

void		AI::update(std::vector<std::pair<Position, Position>> changes)
{
	for (auto& change : changes)
	{
		_map[change.first.x][change.first.y] -= 1;
		_map[change.second.x][change.second.y] += 1;
	}
}
