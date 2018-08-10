#ifndef AI_CLASS_HPP
# define AI_CLASS_HPP

# include "mappy_client.hpp"
# include <iostream>
# include "Graph.class.hpp"

#include "AStar.hpp"

class Ai
{
	const Map& _traffic;
	std::vector<std::vector<double>> _estimatedCosts;
	graph<double*>	_graph;

	double	cost(int carNum);

public:
	Ai(Map & map);
	~Ai();

	Position	where_to(Position pos, Position dest, double &speed);
	// void		bfs(const Position& dest, const Position&, std::vector<int>& v);
//	std::vector<int>	bfs2(int, int);
};

#endif
