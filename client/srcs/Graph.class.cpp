#include "Graph.class.hpp"
#include "utils.hpp"

#include <iostream>

Graph::Graph() {}

Graph::Graph(Map & map, Position const & start, Position const & destination)
{
	_mapWidth = map.size();
	_mapHeight = map[0].size();
	_vertexNumber = _mapHeight * _mapWidth;

	std::cout << _mapWidth << " -- " << _mapHeight << std::endl;
	std::cout << "vertex umber : " << _vertexNumber;

	this->_nodes.resize(_vertexNumber);
	// this->_graph.resize(_vertexNumber);

	_start = coord_to_index(start.x, start.y, _mapWidth, _mapHeight);
	_destination = coord_to_index(destination.x, destination.y, _mapWidth, _mapHeight);

	/* add nodes */
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			this->addNode(i, j, map[i][j]);
		}
	}
	/* add edeges */
	for (auto& n : _nodes)
	{
		if (n.is_road)
			addNeighbors(n, map);
	}

}

Graph::~Graph() {}

void		Graph::addNode(int i, int j, Square & square)
{
	int			index = coord_to_index(i, j, _mapWidth, _mapHeight);
	Node		node(index, square.is_road, square.total_cars);

	this->_nodes[index] = node;
}


void		Graph::addNeighbors(Node &node, Map const & map)
{
	int		x;
	int		y;

	index_to_coor(node.index , x, y , _mapWidth);
	if (x + 1 < _mapWidth && map[x + 1][y].is_road)
		node.adjacency_list.push_back(&_nodes[coord_to_index(x + 1, y, _mapWidth, _mapHeight)]);
	if (x - 1 >= 0 && map[x - 1][y].is_road)
		node.adjacency_list.push_back(&_nodes[coord_to_index(x - 1, y, _mapWidth, _mapHeight)]);
	if (y + 1 < _mapHeight && map[x][y + 1].is_road)
		node.adjacency_list.push_back(&_nodes[coord_to_index(x, y + 1, _mapWidth, _mapHeight)]);
	if (y - 1 >= 0 && map[x][y - 1].is_road)
		node.adjacency_list.push_back(&_nodes[coord_to_index(x, y - 1, _mapWidth, _mapHeight)]);
}

void		Graph::addEdge(Edge edge)
{

}

void		Graph::removeNode(Node node)
{

}
void		Graph::removeEdge(Edge edge)
{

}

Node &		Graph::getNode(int index)
{
	return (_nodes[index]);
}

// Edge		Graph::getEdge(int , int) const
// {
//
// }

void		Graph::print_graph() const
{
	for (auto& node : _nodes)
	{
		int x;
		int y;
		index_to_coor(node.index, x , y , _mapWidth);
		std::cout << "Node [" << node.index << "] ("<< x <<  ","<< y <<  ")==> ";
		for (auto& n : node.adjacency_list)
		{
			index_to_coor(n->index, x , y , _mapWidth);
			std::cout << "[" << n->index << "] ("<< x <<  ","<< y <<  ") :: ";
		}
		std::cout << std::endl;
	}
}

/*
**			GETTERS
*/

int			Graph::getMapWidth(void) const
{
	return this->_mapWidth;
}

int			Graph::getMapHeight(void) const
{
	return this->_mapHeight;
}

/*
**			OPERATOR OVERLOAD
*/
/*
std::ostream & operator<<( std::ostream & o, Graph const & rhs)
{
	for (auto& x : map)
	{
		for (auto& s : x)
		{
			if (s.is_road)
				o << KGRN << "Road" << KNRM;
			else
				o << KRED << "Wall" << KNRM;
			o << "  ";
		}
		o << std::endl;
	}
	return (o);
}
*/
