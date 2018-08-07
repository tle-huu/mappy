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

	Map					mymap = this->_heatmap;
	int					width = _graph.getMapWidth();
	int					height = _graph.getMapHeight();
	std::vector<bool>	visited(width * height);
	int					s;

	for (int i = 0; i < visited.size();i++)
		visited[i] = false;
	// for (auto& b : visited)
		// b = false;

	std::queue<int>		queue;

	s = coord_to_index(pos.x, pos.y, width, height);
	std::cout << "starting node : " << s << std::endl;
	visited[s] = true;
	queue.push(s);
	while (!queue.empty())
	{
		s = queue.front();
		/* Action */
		std::cout << " Dealing with [" << s << "]" << std::endl;
		/* Action */
		queue.pop();
		for (auto& n : _graph.getNode(s).adjacency_list)
		{
			if (!(visited[n.index]))
			{
				visited[n.index] = true;
				queue.push(n.index);
			}
		}
	}
	return (pos);
}

//
// void		Graph::BFS(int s)
// {
//     // Mark all the vertices as not visited
//     bool *visited = new bool[V];
//     for(int i = 0; i < V; i++)
//         visited[i] = false;
//
//     // Create a queue for BFS
//     list<int> queue;
//
//     // Mark the current node as visited and enqueue it
//     visited[s] = true;
//     queue.push_back(s);
//
//     // 'i' will be used to get all adjacent
//     // vertices of a vertex
//     list<int>::iterator i;
//
//     while(!queue.empty())
//     {
//         // Dequeue a vertex from queue and print it
//         s = queue.front();
//         cout << s << " ";
//         queue.pop_front();
//
//         // Get all adjacent vertices of the dequeued
//         // vertex s. If a adjacent has not been visited,
//         // then mark it visited and enqueue it
//         for (i = adj[s].begin(); i != adj[s].end(); ++i)
//         {
//             if (!visited[*i])
//             {
//                 visited[*i] = true;
//                 queue.push_back(*i);
//             }
//         }
//     }
// }
