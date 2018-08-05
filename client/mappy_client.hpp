#pragma once

#include <vector>

struct	Position
{
	int x;
	int y;
};

struct	Square
{
	bool is_road;
	int total_cars;
};

typedef Map std::vector<std::vector<Square>>;
