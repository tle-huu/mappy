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
# include <sys/select.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <fstream>
# include <string>
# include <vector>
# include <iostream>
# include <sstream>
# include <queue>
# include <map>
# include <stack>
# include "mappy_client.hpp"
# include <numeric>
# include <chrono>
# include <sys/time.h>
# include <time.h>
# include "Datagram.hpp"
# include <fstream>


class CommunicationSocket
{
	private:
		std::string													_addr;
		int															_port;
		int															_socket;
		bool														_connected;
		std::map<std::string, std::function<void(std::string)>> 	_events;

		/* need a mutex to access this variable if multithreaded */
		std::queue<Datagram>										_datagram_queue;

		int					_id;
		double				_diff;
		timeval				_start;
		double				_distance;

		/*  Select related << listen_loop >> */
		fd_set				_rfds;
		struct timeval		_tv;


		CommunicationSocket(CommunicationSocket const & src);
		CommunicationSocket &		operator=(CommunicationSocket const & rhs);
		CommunicationSocket();

		std::string		read(void) const;
		bool			get_datagram(void);
		void			get_peer(std::string, Map &) const;
		void			get_peers(Map &map) const;

	public:
		CommunicationSocket(const char * addr, int port);
		~CommunicationSocket();

		void			listen_loop(void);
		void			disconnect();
		void			send_datagram(std::string header, std::string message) const;
		void			send_datagram(Datagram const & Datagram) const;
		Map 			get_first_info(Map& map, Position& start, Position& dest);
		void			wait_for_game(void) const;
		void			wait_for_move(void);
		bool			get_datagram(Datagram & datagram);
		int				get_id(void) const;
		void			dump(void) ;
};

#endif
