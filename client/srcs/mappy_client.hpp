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

typedef std::vector<std::vector<Square>> Map;
