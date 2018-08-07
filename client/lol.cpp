#include <string>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include "mappy_client.hpp"
#include <vector>

#include "Datagram.hpp"
#include "CommunicationSocket.hpp"
#include "utils.hpp"
#include "Graph.class.hpp"
#include "Ai.class.hpp"
typedef struct coucou

{
	int lol;
}				t_coucou;

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

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
	Map 			map;
	Position		start;
	Position		destination;
	std::string		ip("10.114.12.13");
	// std::string		ip("localhost");

	// 10.114.12.13 8888

	CommunicationSocket		sock(ip.c_str(), 8888);
	sock.send_datagram("car", "\n");
	sock.get_first_info(map, start, destination);
	display_map(map);
	sock.wait_for_game();

	print_map(map);

	Graph		graph(map, start, destination);
	std::cout << "\nGraph\n\n";
	graph.print_graph();

	Ai			nick(map, graph);

	double speed = 12;
	Position proute = nick.where_to(start, destination, speed);

	// std::cout << "next move is " << coord_to_index(proute.x, proute.y, graph.getMapWidth(), graph.getMapHeight()) << " (" << proute.x << ", " << proute.y << ")\n";


	return 0;
}
