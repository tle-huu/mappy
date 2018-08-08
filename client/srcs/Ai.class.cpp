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

double	Ai::cost(int carNum)
{
	return carNum;
}

double	Ai::node_weight(Position pos, Position dest, Position mapSquare)
{
	return cost(_heatmap[mapSquare.x][mapSquare.y].total_cars);
}

Position		Ai::where_to(Position pos, Position dest, double &speed)
{
	std::vector<int> path;
	this->bfs(dest, pos, path);
	Position next;
	
	if (path.size() == 0)
	{
		speed = 1;
		return pos;
	}
	
	index_to_coor(path[0], next.x, next.y, _heatmap.size());
	speed = cost(_heatmap[next.x][next.y].total_cars);
	return next;
}

void			Ai::bfs(const Position& dest, const Position& start, std::vector<int>& path)
{

	Map mymap = this->_heatmap;
	int width = _graph.getMapWidth();
	int height = _graph.getMapHeight();
	std::vector<bool> visited(width * height);
	int s;
	int level = 0;

	for (int i = 0; i < visited.size();i++)
		visited[i] = false;

	std::queue<int>		queue;
	/* launching the bfs from the end to get the next node */
	s = coord_to_index(dest.x, dest.y, width, height);

	visited[s] = true;
	queue.push(s);
	(this->_graph.getNode(s)).color = level;
	while (!queue.empty())
	{
		s = queue.front();
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
			if ((_graph._nodes)[n].color < min)
			{
				min = (_graph._nodes)[n].color;
				index = n;
			}
		}
		path.push_back(index);
		current = index;
		// std::cout << "[" << index << "] => ";
	}
	// sleep(3);
	return ;
}
