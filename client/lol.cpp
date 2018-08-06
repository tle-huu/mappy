#include <string>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include "mappy_client.hpp"
#include <vector>

#include "Datagram.hpp"
#include "CommunicationSocket.hpp"

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
	Position		end;

	CommunicationSocket		sock("localhost", 1337);
	sock.send_datagram("car", "\n");
	sock.get_first_info(map, start, end);
	display_map(map);
    //
	// // Datagram		datagram("header : ", "message");
    //
	// std::string				test(s1 + " " + s2 + "\n");
	// CommunicationSocket		sock("127.0.0.1", 1337);
	// sock.send_datagram("bonjour", " les copains");
	// sock.listen();
	// sock.send_datagram(datagram);
	return 0;
}
