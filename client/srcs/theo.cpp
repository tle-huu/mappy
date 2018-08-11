


std::vector<size_t>	Ai::a_star(size_t begin, size_t end, std::function<double(size_t, size_t)> heuristic)
{
	size_t index = begin;
	double distanceFromStart = 0;

	struct	node
	{
		size_t index;
		size_t from;
		double dfs;
	};

	auto comparison = [&heuristic, end](const node& n1, const node& n2)
	{
		return (n1.dfs + heuristic(n1.index, end) < n2.dfs + heuristic(n2.index, end));
	};

	// all the neighboring nodes sorted based on heuristic
	std::set<node, comparison> neighbors;

	// gets the nodes 'dfs' and 'from' data, from its index
	std::map<size_t, std::pair<size_t, double>> neighborNodes;

	// stores all visited nodes
	std::vector<node> visited;

	visited.push_back(node{index, -1, 0});

	while (1)
	{
		// add connected nodes to set of neighbors
		for (const auto& nodeData : _graph[index])
		{
			const size_t nodeIndex = nodeData.first;
			const size_t nodeDFS = *nodeData.second + distanceFromStart;
			if (visited.count(nodeIndex))
			continue;
			if (neighborNodes.count(nodeIndex) && nodeDFS < neighborNodes[nodeIndex])
			{
				auto setpair = std::make_pair(neighborNodes[nodeIndex], nodeIndex);
				neighbors.erase(setpair);
				setpair.first = nodeDFS;
				neighbors.insert(setpair);
			}
			else if (!neighborNodes.count(nodeIndex))
			{
				neighbors.insert(std::make_pair(nodeDFS, nodeIndex));
				neighborNodes[nodeIndex] = nodeDFS;
			}
		}

		std::pair<double, size_t> bestNode = *(neighbors.begin());
		neighbors.erase(neighbors.begin());
		index = bestNode.second;
		neighborNodes.erase(index);
		distanceFromStart = bestNode.first;
	}
}
