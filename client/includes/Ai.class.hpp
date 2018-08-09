#ifndef AI_CLASS_HPP
# define AI_CLASS_HPP

# include "mappy_client.hpp"
# include <iostream>
# include "Graph.class.hpp"

class Ai
{
	const Map& _heatmap;
	Graph _graph;
	graph<int>	_graph2;

	double	cost(int carNum);
	double	node_weight(Position pos, Position dest, Position mapSquare);

public:
	Ai(Map & map);
	~Ai();

	Position	where_to(Position pos, Position dest, double &speed);
	// void		bfs(const Position& dest, const Position&, std::vector<int>& v);
	std::vector<int>		bfs2(int, int);
	std::vector<int>		a_star_search(int start, int goal, std::function<double(int, int, int)> heuristic);

};

#endif
