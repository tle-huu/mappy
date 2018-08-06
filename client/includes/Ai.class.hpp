#ifndef AI_CLASS_HPP
# define AI_CLASS_HPP

# include "mappy_client.hpp"
# include <iostream>

class Ai
{
	private:
		Map&		_heatmap;

		bool		bfs(int start);

	public:
		Ai();
		Ai(Map &);
		~Ai();

		Position	where_to(Position &pos, Position &dest, double &speed);
};

#endif
