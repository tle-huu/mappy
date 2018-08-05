#include <string>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include "mappy_client.hpp"
#include <vector>

// #include "Datagram.hpp"
// #include "CommunicationSocket.hpp"

typedef struct coucou

{
	int lol;
}				t_coucou;

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{

	std::string header;
	int x , y;

	std::string coucou("bonjour 1 3");
	std::stringstream ss(coucou);

	ss >> header >> x >> y;

	std::cout << "header : " << header << " x : " <<  x << " y : " << y << std::endl;


	// while (ss)
	// {
	// 	if (ss >> lol)
	// 		std::cout << lol << std::endl;
	// }
	// std::string s2("bonjour");
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
