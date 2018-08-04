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
# include <queue>
# include "Datagram.hpp"

class CommunicationSocket
{
	private:
		std::string					_addr;
		int							_port;
		int							_socket;
		bool						_connected;
		std::queue<Datagram>		_datagram_queue;


		CommunicationSocket(CommunicationSocket const & src);
		CommunicationSocket &		operator=(CommunicationSocket const & rhs);
		CommunicationSocket();

		void			get_datagram(void);
		void			disconnect();

	public:
		CommunicationSocket(char * addr, int port);
		~CommunicationSocket();

		void			listen();

		void			send_datagram(std::string header, std::string message) const;
		void			send_datagram(Datagram const & Datagram) const;

};

#endif
