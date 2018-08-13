#include "AStar.hpp"

std::vector<int>	a_star(graph<double*> graph,
					int start,
					int goal,
					std::function<double(int, int)> heuristic)
{
	std::priority_queue<std::pair<double, int>,
				std::vector<std::pair<double, int>>,
				std::greater<std::pair<double, int>>>	queue;

	std::vector<int>	neighbors;
	std::vector<int>	came_from(graph.size(), -1);
	std::vector<double>	cost_sofar(graph.size(), -1);


	double	new_cost;
	double	priority;

	queue.push(std::make_pair(0, start));
	cost_sofar[start] = 0;

	int current = start;

	 /* early exit */
	while (!queue.empty() && current != goal)
	{
		current = queue.top().second;
		// std::cout << "\n top : " << current << std::endl;
		queue.pop();
		for (auto& next : graph[current])
		{
			new_cost = cost_sofar[current] + *next.second;
			if (came_from[next.first] < 0 || new_cost < cost_sofar[next.first])
			{
				cost_sofar[next.first] = new_cost;
				priority = new_cost + heuristic(next.first, goal);
				queue.push(std::make_pair(priority, next.first));

				came_from[next.first] = current;
			}
		}
	}
	return (came_from);
}
