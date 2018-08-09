#include <string>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include "mappy_client.hpp"
#include <vector>
#include <queue>
#include <functional>

#include "Datagram.hpp"
#include "CommunicationSocket.hpp"
#include "utils.hpp"
#include "Graph.class.hpp"
#include "Ai.class.hpp"
#include "Car.hpp"
// 
// double h1(int n)
// {
// 	return (n);
// }
//
// int mycmp(std::pair<double, int> a, std::pair<double, int> b)
// {
// 	return (b.first - a.first);
// }
//
// std::vector<int>		astar(graph<int> _graph, int start, int goal, std::function<double(int)> heuristic)
// {
// 	std::cout << "a start size graph : " << _graph.size() << std::endl;
// 	std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > >			queue;
// 	std::vector<int>			neighbors;
// 	std::vector<int>			came_from(_graph.size(), -1);
// 	std::vector<double>			cost_sofar(_graph.size(), -1);
//
// 	double						new_cost;
// 	double						priority;
//
// 	queue.push(std::make_pair(0, start));
// 	cost_sofar[start] = 0;
//
// 	int current = start;
// 	/* early exit */
// 	while (!queue.empty() && current != goal)
// 	{
// 		current = queue.top().second;
// 		std::cout << "\n top : " << current << std::endl;
// 		queue.pop();
// 		for (auto& next : _graph[current])
// 		{
// 			new_cost = cost_sofar[current] + next.second;
// 			if (came_from[next.first] < 0 || new_cost < cost_sofar[next.first])
// 			{
// 				cost_sofar[next.first] = new_cost;
// 				priority = new_cost + heuristic(next.first);
// 				queue.push(std::make_pair(priority, next.first));
// 				std::cout << "pushing : " << next.first << " priority : " << priority << " with : " << new_cost<< std::endl;
// 				came_from[next.first] = current;
// 			}
// 		}
// 		std::cout << std::endl;
// 	}
// 	return (came_from);
// }

std::vector<int>	bfs2(int start, int end, graph<int> _graph)
{
	std::queue<int>		queue;
	int					current;
	std::vector<int>	came_from(_graph.size(), -1);

	current = start;

	queue.push(current);
	while (!queue.empty() && current != end)
	{
		current = queue.front();
		queue.pop();
		for (auto& n : _graph[current])
		{
			if (came_from[n.first] < 0)
			{
				queue.push(n.first);
				came_from[n.first] = current;
			}
		}
	}
	return (came_from);
}

void display_map(Map & map)
{
	std::cout << "I am entering display map\n\n";
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
			std::cout << "[" << i << "," << j << ", " << map[i][j].is_road << "]    ";
		std::cout << std::endl;
	}
}
// int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
// {
// 	graph<int>			g;
//
// 	g.resize(25);
// 	// g[0][1] = 1;
// 	// g[0][4] = 1;
// 	// g[0][6] = 1;
// 	// g[6][7] = 1;
// 	// g[7][8] = 1;
// 	// g[8][3] = 1;
// 	// g[1][2] = 5;
// 	// g[2][3] = 1;
// 	// g[4][5] = 1;
// 	// g[5][2] = 1;
// 	g[0][1] = 1;
// 	g[1][2] = 1;
// 	g[2][3] = 1;
// 	g[3][4] = 1;
// 	g[4][9] = 1;
// 	g[9][14] = 1;
// 	g[14][19] = 1;
// 	g[19][18] = 1;
// 	g[18][17] = 1;
// 	g[17][16] = 1;
// 	g[16][15] = 1;
//
//
// 	std::vector<int>  path = bfs2(0, 15, g);
// 	std::vector<int>  path2 = astar(g, 0, 15, h1);
// 	int i = 15;
// 	for (auto& k : path)
// 		std::cout << k << " , ";
// 	std::cout << std::endl;
// 	std::cout << "bfs " << std::endl;
// 	while (i >= 0)
// 	{
// 		std::cout << i << " <= ";
// 		i = path[i];
// 	}
// 	std::cout << std::endl;
// 	std::cout << " A star" << std::endl;
// 	i = 15;
// 	while (i >= 0)
// 	{
// 		std::cout << i << " <= ";
// 		i = path2[i];
// 	}
// 	return 0;
// }

int main(int argc, char *argv[])
{
	if (argc != 3)
		return 1;
	Car car(argv[1], std::atoi(argv[2]));
	while (1)
		car.move();
	return 0;
}
