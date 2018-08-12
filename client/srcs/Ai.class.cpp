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

double	Ai::cost(int carNum)
{
	if (carNum < 0)
	{
		std::cout << KRED << "OUPS CARNUM NEGATIVE : " << carNum << KNRM;
		exit(1);
	}
	return 1;
}

Position	Ai::where_to(Position pos, Position dest, double &speed)
{
	if (pos.x == dest.x && pos.y == dest.y)
	{
		// exit(42); // Only difference with working version, seems to make everything crash
		// sleep(50);
		speed = cost(0);
		return pos;
	}
	for (size_t x = 0; x < _estimatedCosts.size(); x++)
		for (size_t y = 0; y < _estimatedCosts[0].size(); y++)
			_estimatedCosts[x][y] = cost(_traffic[x][y].total_cars);

	int width = _traffic.size();
	auto heuristic = [width, this](int loc, int dest)
	{
		Position p_loc = {loc % width, loc / width};
		Position p_dest = {dest % width, dest / width};

		int distance =  std::abs(p_loc.x - p_dest.x) + std::abs(p_loc.y - p_dest.y);
		return cost(0) * (double)distance * (1 / 1000);
	};

	auto heuristic2 = [width, this](int loc, int dest)
	{
		return 0;
	};

	auto index = [width](size_t x, size_t y){ return x + y * width; };
	std::vector<int> path = a_star(_graph, index(pos.x, pos.y), index(dest.x, dest.y), heuristic2);
	int start_indx = index(pos.x, pos.y);
	int end_indx = index(dest.x, dest.y);
	int next_indx;
	while (end_indx != start_indx)
	{
		next_indx = end_indx;
		end_indx = path[end_indx];
	}
	Position next = { next_indx % (int)_traffic.size(), next_indx / (int)_traffic.size() };
	// speed = 0.2;
	speed = cost(_traffic[next.x][next.y].total_cars);
	speed = fmin(_traffic[next.x][next.y].total_cars + 1, 7);
	return next;
}

/*

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

*/

// std::vector<size_t>    Ai::astar(size_t begin, size_t end, std::function<double(size_t)> heuristic)
// {
// 	size_t index = begin;
// 	double distanceFromStart = 0;
// 	std::set<std::pair<double, size_t>> neighbors; // distance from start + index, sorted using heuristic
// 	std::map<size_t, double> neighborNodes; // node index -> distance from start
// 	std::unordered_set<size_t> visited;
//double h1(int pos, int des, int width)
// }
