#ifndef CSI_HPP
# define CSI_HPP


# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <netdb.h>
# include <sys/uio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <fstream>
# include <string>
# include <vector>
# include <iostream>
# include <sstream>
# include <queue>
# include "Datagram.hpp"

# define BUFF_SIZE 8192

class Map;

class CommunicationSocket
{
	private:
		std::string											_addr;
		int													_port;
		int													_socket;
		bool												_connected;
		// map<std::string, function<void(std::string)>> 	_events;
		std::queue<Datagram>								_datagram_queue;


		CommunicationSocket(CommunicationSocket const & src);
		CommunicationSocket &		operator=(CommunicationSocket const & rhs);
		CommunicationSocket();

		std::string		read(void) const;
		void			get_datagram(void);
		void			disconnect();
		void			get_peer(std::string, Map &) const;
		void			get_peers(Map &map) const;

	public:
		CommunicationSocket(char * addr, int port);
		~CommunicationSocket();

		void			listen();
		void			send_datagram(std::string header, std::string message) const;
		void			send_datagram(Datagram const & Datagram) const;
		void 			get_info(Map& map, Position& start, Position& dest);
		// Map			get_map() const;
		// Position								get_position(void)		const;
		// Position								get_destination(void)	const;
		// std::vector<Pair<Position, Position>>	get_updates(void);

};

#endif
