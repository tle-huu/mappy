#include "Ai.class.hpp"
#include "utils.hpp"

#include <queue>
#include <vector>
#include <unistd.h>

Ai::Ai(Map & map) : _heatmap(map), _graph()
{
	_graph = Graph(map);
}

Ai::~Ai() {}

Position		Ai::where_to(Position pos, Position dest, double &speed)
{
	Position			nextmove;
	int					index = -1;
	int					color = -1;
	int					current = coord_to_index(pos.x, pos.y, _graph.getMapWidth(), _graph.getMapHeight());
	int					end = coord_to_index(dest.x, dest.y, _graph.getMapWidth(), _graph.getMapHeight());
	bool fortest = false;

	static std::vector<int> 		path;
	static int 				i = 0;

	std::cout << dest.x << " " << dest.y << std::endl;
	std::cout << "current : " << current << std::endl;

	/* calculating best path */
	if (i == path.size())
		i = 0;
	if (i == 0)
		this->bfs(dest, pos, path);
	std::cout << "after bfs" << std::endl;
	// for (auto& n : _graph.getNode(current).adjacency_list)
	// {
	// 	if (color < 0 || _graph.nodes[n].color < color)
	// 	{
	// 		index = _graph.nodes[n].index;
	// 		color = _graph.nodes[n].color;
	// 	}
	// }
	// std::cout << "[" << current << "] => " << std::endl;
	// static int lol = 0;
	// color = _graph.getNode(current).color;
	// while (current != end)
	// {
	// 	for (auto& n : _graph.getNode(current).adjacency_list)
	// 	{
	// 		if (color < 0)
	// 		{
	// 			color = _graph.nodes[n].color;
	// 			current = _graph.nodes[n].index;
	// 		}
	// 		if (_graph.nodes[n].color < color)
	// 		{
	// 			std::cout << "[" << _graph.nodes[n].index << "] => ";
	// 			if (!fortest)
	// 			{
	// 				index = _graph.nodes[n].index;
	// 				fortest = true;
	// 			}
	// 			color = _graph.nodes[n].color;
	// 			current = _graph.nodes[n].index;
	// 		}
	// 	}
	// }
	std::cout << "path size : " << path.size() << std::endl;
	Position printcurrent;
	index_to_coor(current, printcurrent.x, printcurrent.y, _graph.getMapWidth());
	std::cout << "i => " << i << "; current (" << printcurrent.x << "," << printcurrent.y << ") ;";
	index_to_coor(path[i], pos.x, pos.y, _graph.getMapWidth());
	std::cout << " next (" << pos.x << "," << pos.y << ") ;";
	speed = 1;
	i++;
	return (pos);
}

void			Ai::bfs(Position &dest, Position &start, std::vector<int> &path)
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

	std::cout << "starting node : ( " << dest.x << "," << dest.y << ")" << s << std::endl;
	visited[s] = true;
	queue.push(s);
	(this->_graph.getNode(s)).color = level;
	while (!queue.empty())
	{
		s = queue.front();
		std::cout << "icibfs0" << std::endl;
		queue.pop();
		level = this->_graph.getNode(s).color;
		for (auto& n : (_graph.getNode(s)).adjacency_list)
		{
			// if (_graph._nodes[n].index > width * height)
				// break;
			if (!(visited[_graph._nodes[n].index]))
			{

				visited[_graph._nodes[n].index] = true;
				queue.push(_graph._nodes[n].index);
				_graph.getNode(_graph._nodes[n].index).color = level + 1;
				// std::cout << "Coloring [" << _graph.nodes[n].index << "] with " << level + 1 << std::endl;
			}

		}
	}
	int current = coord_to_index(start.x, start.y, _graph.getMapWidth(), _graph.getMapHeight());
	int end = coord_to_index(dest.x, dest.y, _graph.getMapWidth(), _graph.getMapHeight());

	int color = _graph.getNode(current).color;
	int index = current;
	while (current != end)
	{
		int min = _graph._nodes[current].color;
		for (auto& n : (_graph.getNode(current)).adjacency_list)
		{
			// std::cout << "parent color : " << color << " n color : " << _graph.nodes[n].color << std::endl;
			if ((_graph._nodes)[n].color <= min)
			{
				min = (_graph._nodes)[n].color;
				index = n;
			}
		}
		path.push_back(index);
		current = index;
		std::cout << "[" << index << "] => ";
	}
	std::cout << "ending bfs : " << path.size() << std::endl;;
	// sleep(3);
	return ;
}
