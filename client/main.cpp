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

int main(int argc, char *argv[])
{
	if (argc != 3)
		return 1;
	Car car(argv[1], std::atoi(argv[2]));
	while (1)
		car.move();
	return 0;
}
