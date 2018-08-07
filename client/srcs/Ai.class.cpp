#include "Ai.class.hpp"
#include "utils.hpp"

#include <queue>
#include <vector>

Ai::Ai(Map & map, Graph & graph) : _heatmap(map), _graph(graph)
{

}

Ai::~Ai() {}


Position		Ai::where_to(Position &pos, Position &dest, double &speed)
{
	Position			nextmove;
	int					index = -1;
	int					color = -1;
	std::vector<int>	path;
	int					current = coord_to_index(pos.x, pos.y, _graph.getMapWidth(), _graph.getMapHeight());
	int					end = coord_to_index(dest.x, dest.y, _graph.getMapWidth(), _graph.getMapHeight());
	bool fortest = false;
	std::cout << dest.x << " " << dest.y << std::endl;
	std::cout << "current : " << current << std::endl;

	this->bfs(dest);
	std::cout << "\nwhere to \n";
	color = _graph.getNode(current).color;
	while (current != end)
	{
		for (auto& n : _graph.getNode(current).adjacency_list)
		{
			if (color < 0)
			{
				color = n->color;
				current = n->index;
			}
			if (n->color < color)
			{
				std::cout << "[" << n->index << "] => ";
				color = n->color;
				current = n->index;

			}
			if (!fortest && n->color < color)
			{
				fortest = true;
				index = n->index;
			}
		}
	}
	std::cout << "\nwhere to end\n";
	index_to_coor(index, pos.x, pos.y, _graph.getMapWidth());
	return (pos);
}

void			Ai::bfs(Position &dest)
{

	Map					mymap = this->_heatmap;
	int					width = _graph.getMapWidth();
	int					height = _graph.getMapHeight();
	std::vector<bool>	visited(width * height);
	int					s;
	int					level = 0;

	for (int i = 0; i < visited.size();i++)
		visited[i] = false;
	// for (auto& b : visited)
		// b = false;

	std::queue<int>		queue;

	/* launching the bfs from the end to get the next node */
	s = coord_to_index(dest.x, dest.y, width, height);
	std::cout << "starting node : " << s << std::endl;
	visited[s] = true;
	queue.push(s);
	(this->_graph.getNode(s)).color = level;
	while (!queue.empty())
	{
		s = queue.front();
		/* Action */
		/* Action */
		level = this->_graph.getNode(s).color;
		for (auto& n : (_graph.getNode(s)).adjacency_list)
		{
			if (!(visited[n->index]))
			{
				visited[n->index] = true;
				queue.push(n->index);
				_graph.getNode(n->index).color = level + 1;
				std::cout << "Coloring [" << n->index << "] with " << level + 1 << std::endl;
			}
		}
		queue.pop();
	}
}
