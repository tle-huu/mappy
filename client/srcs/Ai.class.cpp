#include "Ai.class.hpp"
#include "utils.hpp"

#include <queue>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <math.h>

Ai::Ai(Map& map) : _traffic(map)
{
	_estimatedCosts.resize(_traffic.size());
	for (size_t i = 0; i < _estimatedCosts.size(); i++)
		_estimatedCosts[i].resize(_traffic[i].size());

	//constructing graph
	size_t width = _traffic.size();
	auto index = [width](size_t x, size_t y){ return x + y * width; };

	_graph.resize(_traffic.size() * _traffic[0].size());
	for (size_t x = 0; x < _traffic.size(); x++)
	{
		for (size_t y = 0; y < _traffic[0].size(); y++)
		{
			if (!_traffic[x][y].is_road)
				continue;
			if (x >= 1 && _traffic[x - 1][y].is_road)
				_graph[index(x, y)][index(x - 1, y)] = &_estimatedCosts[x - 1][y];
			if (x < _traffic.size() - 1 && _traffic[x + 1][y].is_road)
				_graph[index(x, y)][index(x + 1, y)] = &_estimatedCosts[x + 1][y];
			if (y >= 1 && _traffic[x][y - 1].is_road)
				_graph[index(x, y)][index(x, y - 1)] = &_estimatedCosts[x][y - 1];
			if (y < _traffic[0].size() && _traffic[x][y + 1].is_road)
				_graph[index(x, y)][index(x, y + 1)] = &_estimatedCosts[x][y + 1];
		}
	}
}

Ai::~Ai() {}

bool		Ai::is_intersection(Position pos) const
{
	int		x = pos.x;
	int		y = pos.y;
	int		nb = 0;
	bool	ret = false;

	if (x >= 1 && _traffic[x - 1][y].is_road)
		nb++;
	if (x < _traffic.size() - 1 && _traffic[x + 1][y].is_road)
		nb++;
	if (y >= 1 && _traffic[x][y - 1].is_road)
		nb++;
	if (y < _traffic[0].size() && _traffic[x][y + 1].is_road)
		nb++;
	if (nb >= 3)
		return (true);
	return (false);
}

double	Ai::cost(int carNum)
{
	if (carNum < 0)
	{
		std::cout << KRED << "OUPS CARNUM NEGATIVE : " << carNum << KNRM;
		carNum = 0;
	}
	// Put the cost to 1 for no information
	// return 1;
	return carNum * 2 + 1;
}

Position	Ai::where_to(Position pos, Position dest, double &speed)
{
	int width = _traffic.size();


	// If arrived
	if (pos.x == dest.x && pos.y == dest.y)
	{
		speed = cost(0);
		return pos;
	}

	for (size_t x = 0; x < _estimatedCosts.size(); x++) {
		for (size_t y = 0; y < _estimatedCosts[0].size(); y++) {
			_estimatedCosts[x][y] = cost(_traffic[x][y].total_cars);
		}
	}

	auto heuristic = [width, this](int loc, int dest)
	{
		Position p_loc = {loc % width, loc / width};
		Position p_dest = {dest % width, dest / width};

		int distance =  std::abs(p_loc.x - p_dest.x) + std::abs(p_loc.y - p_dest.y);
		return cost(0) * (double)distance * (1 + (1 / 1000));
	};

	auto heuristic2 = [width, this](int loc, int dest)
	{
		return 0;
	};

	auto index = [width](size_t x, size_t y){ return x + y * width; };

	std::vector<int> path = a_star(_graph, index(pos.x, pos.y), index(dest.x, dest.y), heuristic);

	int start_indx = index(pos.x, pos.y);
	int end_indx = index(dest.x, dest.y);
	int next_indx;
	while (end_indx != start_indx)
	{

		next_indx = end_indx;
		end_indx = path[end_indx];
	}

	Position next = { next_indx % (int)_traffic.size(), next_indx / (int)_traffic.size() };

	speed = fmin(_traffic[next.x][next.y].total_cars + 1, 7);
	if (is_intersection(next))
		speed = 1;
	return next;
}

/*
std::vector<int>	Ai::bfs(int start, int end)
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
		i = came_from[i];
	return (came_from);
}
*/
