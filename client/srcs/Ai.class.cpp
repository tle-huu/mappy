#include "Ai.class.hpp"
#include "utils.hpp"

Ai::Ai() {}

Ai::Ai(Map & map) : _heatmap
{

}



Position		Ai::where_to(Position &pos, Position &dest, double &speed)
{

	Map					mymap = this->_heatmap;
	int					width = mymap.size();
	int					height = mymap[0].size();
	std::vector<bool>	visited(width * length);
	int					s;
	int					x;
	int					y;


	for (auto& b : visited)
		b = false;

	std::queue<int>		queue;
	s = coord_to_index(pos.x, pos.y);
	visited[s] = true;
	queue.push(s);
	while (!queue.empty())
	{
		s = queue.front();
		index_to_coor(x , y, width);
		/* Action */
		std::cout << "(" << x << " , " << y << " )" << std::endl;
		/* Action */
		queue.pop();

		int tmp = coord_to_index(x + 1, y);
		if (mymap[x + 1, y] && !visited(tmp))
		{
			visited[tmp] = true;
			queue.push(tmp);
		}
		int tmp = coord_to_index(x + 1, y);
		if (!visited(tmp))
		{
			visited[tmp] = true;
			queue.push(tmp);
		}
		int tmp = coord_to_index(x + 1, y);
		if (!visited(tmp))
		{
			visited[tmp] = true;
			queue.push(tmp);
		}
		int tmp = coord_to_index(x + 1, y);
		if (!visited(tmp))
		{
			visited[tmp] = true;
			queue.push(tmp);
		}
	}
}


oid Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}
