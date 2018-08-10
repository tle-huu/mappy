#include "Ai.class.hpp"
#include "utils.hpp"

#include <queue>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <math.h>

Ai::Ai(Map & map) : _heatmap(map), _graph()
{
	int index;
	int mapWidth = _heatmap.size();
	int mapHeight = _heatmap[0].size();

	_graph = Graph(map);

	_graph2.resize(_heatmap.size() * _heatmap[0].size());

	/* add nodes */
	for (int i = 0; i < _heatmap.size(); i++)
	{
		for (int j = 0; j < _heatmap[0].size(); j++)
		{
			if (_heatmap[i][j].is_road)
			{
				index = coord_to_index(i, j, mapWidth, mapHeight);;
				// _graph2[i][j] = 1;
				if (i + 1 < mapWidth && _heatmap[i + 1][j].is_road)
					_graph2[index][coord_to_index(i + 1, j, mapWidth, mapHeight)] = 1;

				if (i - 1 >= 0 && _heatmap[i - 1][j].is_road)
					_graph2[index][coord_to_index(i - 1, j,  mapWidth, mapHeight)] = 1;

				if (j + 1 < mapHeight && _heatmap[i][j + 1].is_road)
					_graph2[index][coord_to_index(i, j + 1, mapWidth, mapHeight)] = 1;

				if (j - 1 >= 0 && _heatmap[i][j - 1].is_road)
					_graph2[index][coord_to_index(i, j - 1, mapWidth, mapHeight)] = 1;
				// this->addNode(i, j, map[i][j]);
			}
		}
	}
	for (int x = 0; x < _graph2.size();x++)
	{
		std::cout << x << " ==> ";
		for (auto& c : _graph2[x])
			std:: cout << c.first << " ;; ";
		std::cout << std::endl;
	}
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

double h1(int pos, int des, int width)
{
	Position		start;
	Position		end;

	double			distance;

	index_to_coor(pos, start.x, start.y, width);
	index_to_coor(des, end.x, end.y, width);
	distance = sqrt((start.x - end.x) * (start.x - end.x) +  (start.y - end.y) * (start.y - end.y));
	return (distance);
}

Position		Ai::where_to(Position pos, Position dest, double &speed)
{
	std::vector<int> path;
	int start = coord_to_index(pos.x, pos.y, _heatmap.size(), _heatmap[0].size());
	int end = coord_to_index(dest.x, dest.y, _heatmap.size(), _heatmap[0].size());

	Position	next;
	int			next_index;

	// path = this->bfs2(dest, pos, path);
	if (start == end)
	{
		std::cout << KGRN << "DESTIANTION REACHED" << std::endl;
		sleep(10);
		return pos;
	}
	// path = this->bfs2(start, end);
	path = this->a_star_search(start, end, h1);
	std::cout << std::endl;
	// while (path[0] < 0)
		// path.erase(path.begin());
	// path.erase( remove( path.begin(), path.end(), -1 ), path.end() );
	int test = 0;
	next_index = start;
	while (end != start)
	{
		next_index = end;
		end = path[end];
	}
	std::cout << "next move : " << next_index << std::endl;
	index_to_coor(next_index, next.x, next.y, _heatmap.size());
	speed = 0.5;
	// speed = cost(_heatmap[next.x][next.y].total_cars);
	return next;
}

std::vector<int>	Ai::bfs2(int start, int end)
{
	std::queue<int>		queue;
	int					current;
	std::vector<int>	came_from(_heatmap.size() * _heatmap[0].size(), -1);

	current = start;

	queue.push(current);
	while (!queue.empty() && current != end)
	{
		current = queue.front();
		queue.pop();
		for (auto& n : _graph2[current])
		{
			if (came_from[n.first] < 0)
			{
				queue.push(n.first);
				came_from[n.first] = current;
			}
		}
	}
	int i = end;
	std::cout << "ici start : " <<start << std::endl;
	std::cout << "ici end : " << end << std::endl;
	while (i != start)
	{
		std::cout << i << " <= ";
		i = came_from[i];
	}
	return (came_from);
}

// std::vector<size_t>    Ai::astar(size_t begin, size_t end, std::function<double(size_t)> heuristic)
// {
// 	size_t index = begin;
// 	double distanceFromStart = 0;
// 	std::set<std::pair<double, size_t>> neighbors; // distance from start + index, sorted using heuristic
// 	std::map<size_t, double> neighborNodes; // node index -> distance from start
// 	std::unordered_set<size_t> visited;
//double h1(int pos, int des, int width)
// }

std::vector<int>			Ai::a_star_search(int start, int goal, std::function<double(int, int, int)> heuristic)
{
	std::priority_queue<std::pair<double, int>,
	 		std::vector<std::pair<double, int> >,
			 std::greater<std::pair<double, int> > >			queue;

	std::vector<int>			neighbors;
	std::vector<int>			came_from(_heatmap.size() * _heatmap[0].size(), -1);
	std::vector<double>			cost_sofar(_heatmap.size() * _heatmap[0].size(), -1);


	double						new_cost;
	double						priority;

	queue.push(std::make_pair(0, start));
	cost_sofar[start] = 0;

	int current = start;

	/* early exit */
	while (!queue.empty() && current != goal)
	{
		current = queue.top().second;
		// std::cout << "\n top : " << current << std::endl;
		queue.pop();
		for (auto& next : _graph2[current])
		{
			new_cost = cost_sofar[current] + next.second;
			if (came_from[next.first] < 0 || new_cost < cost_sofar[next.first])
			{
				cost_sofar[next.first] = new_cost;
				priority = new_cost + heuristic(next.first, goal, _heatmap.size());
				queue.push(std::make_pair(priority, next.first));
				// std::cout << "pushing : " << next.first << " priority : " << priority << " with : " << new_cost<< std::endl;

				came_from[next.first] = current;
			}
		}
		std::cout << std::endl;
	}
	return (came_from);
}


// void			Ai::bfs(const Position& dest, const Position& start, std::vector<int>& path)
// {
//
// 	Map mymap = this->_heatmap;
// 	int width = _graph.getMapWidth();
// 	int height = _graph.getMapHeight();
// 	std::vector<bool> visited(width * height);
// 	int s;
// 	int level = 0;
//
// 	for (int i = 0; i < visited.size();i++)
// 		visited[i] = false;
//
// 	std::queue<int>		queue;
// 	/* launching the bfs from the end to get the next node */
// 	s = coord_to_index(dest.x, dest.y, width, height);
//
// 	visited[s] = true;
// 	queue.push(s);
// 	(this->_graph.getNode(s)).color = level;
// 	while (!queue.empty())
// 	{
// 		s = queue.front();
// 		queue.pop();
// 		level = this->_graph.getNode(s).color;
// 		for (auto& n : (_graph.getNode(s)).adjacency_list)
// 		{
// 			// if (_graph._nodes[n].index > width * height)
// 				// break;
// 			if (!(visited[_graph._nodes[n].index]))
// 			{
//
// 				visited[_graph._nodes[n].index] = true;
// 				queue.push(_graph._nodes[n].index);
// 				_graph.getNode(_graph._nodes[n].index).color = level + 1;
// 				// std::cout << "Coloring [" << _graph.nodes[n].index << "] with " << level + 1 << std::endl;
// 			}
//
// 		}
// 	}
// 	int current = coord_to_index(start.x, start.y, _graph.getMapWidth(), _graph.getMapHeight());
// 	int end = coord_to_index(dest.x, dest.y, _graph.getMapWidth(), _graph.getMapHeight());
//
// 	int color = _graph.getNode(current).color;
// 	int index = current;
// 	while (current != end)
// 	{
// 		int min = _graph._nodes[current].color;
// 		for (auto& n : (_graph.getNode(current)).adjacency_list)
// 		{
// 			// std::cout << "parent color : " << color << " n color : " << _graph.nodes[n].color << std::endl;
// 			if ((_graph._nodes)[n].color < min)
// 			{
// 				min = (_graph._nodes)[n].color;
// 				index = n;
// 			}
// 		}
// 		path.push_back(index);
// 		current = index;
// 		// std::cout << "[" << index << "] => ";
// 	}
// 	// sleep(3);
// 	return ;
// }
