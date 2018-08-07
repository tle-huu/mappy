#ifndef AI_CLASS_HPP
# define AI_CLASS_HPP

# include "mappy_client.hpp"
# include <iostream>
# include "Graph.class.hpp"

class Ai
{
	private:
		Map&		_heatmap;
		Graph		_graph;
		Ai();

	public:
		Ai(Map & map);
		~Ai();

		Position	where_to(Position pos, Position dest, double &speed);
		void		bfs(Position &dest, Position &, std::vector<int> &v);

};

#endif
