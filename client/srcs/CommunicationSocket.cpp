
#include "CommunicationSocket.hpp"
# define BUFF_SIZE 3072000

/*
** ==================		CONSTRUCTORS DESTRUCTORS	 	==================
*/

CommunicationSocket::CommunicationSocket()
{}

CommunicationSocket::CommunicationSocket(const char* addr, int port) : _addr(addr), _port(port)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	_tv.tv_sec = 0;
	_tv.tv_usec = 0;

	if (!(proto = getprotobyname("tcp")))
		throw(std::runtime_error("CommunicationSocket(): getprotobyname error"));
	if ((this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		throw(std::runtime_error("CommunicationSocket(): socket error"));
	try
	{
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		sin.sin_addr.s_addr = (std::string(addr) == "localhost") ? inet_addr("127.0.0.1")
									: inet_addr(addr);
	}
	catch (...)
	{
		std::cout << "Communincaton socket sin.sin crash" << std::endl;
		exit(2);
	}
	if (connect(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		throw(std::runtime_error("CommunicationSocket(): connect error"));
	this->_connected = true;
	if (this->read() != "WELCOME\n")
	{
		std::cout << "\ncrash trying to receive the welcome\n";
		exit(1);
	}
	this->send_datagram("car", "\n");

	std::cout << "CommunicationSocket has been connected to " << addr << ":" << port<< std::endl;
}

CommunicationSocket::~CommunicationSocket()
{
	std::cout << "Communication socket destroyed" << std::endl;
}

/*
** ==================		PRIVATE	 	==================
*/


std::string			CommunicationSocket::read(void) const
{
	char				buffer[BUFF_SIZE] = {0};
	int					ret;
	Datagram			datagram;

	if ((ret = recv(this->_socket, buffer, BUFF_SIZE - 1, 0)) < 0)
		throw(std::runtime_error("CommunicationSocket(): read recv error"));
	buffer[ret] = 0;
	std::cout << "I have read " << ret << " bytes [" << buffer << "]\n";
	return (std::string(buffer));
}

/* the private get_datagram has to be rewritten depending on the format of a datagram */


bool				CommunicationSocket::get_datagram(void)
{
	Datagram			datagram;
	std::size_t			spliter;
	std::string			raw;
	bool				hasok = false;

	raw = this->read();
	std::stringstream ss(raw);
	for (std::string line; std::getline(ss, line);)
	{
		if ((spliter = line.find(" ")) == std::string::npos)
		{
			std::cout << "CommunicationSocket(): get_datagram line.find error" << std::endl;
			return false;
		}
		datagram.setHeader(line.substr(0, spliter));
		datagram.setMessage(line.substr(spliter));
		// std::cout << datagram.getHeader() << "| === |" << datagram.getMessage() << std::endl;
		if (datagram.getHeader() == "ok")
		{
			std::cout << KYEL << " OK " << KNRM << std::endl;
			hasok = true;
		}
		else
		{
			try
			{
				this->_datagram_queue.push(datagram);
			}
			catch (std::exception &e)
			{
				std::cout << "CommunicationSocket::getDatagram(): " << e.what() << std::endl;
			}
		}
	}
	return hasok;
}

void	CommunicationSocket::get_peer(std::string data, Map &map) const
{
	std::string				header;
	int						x;
	int						y;
	int						id;
	std::stringstream		ss(data);

	ss >> header >> x >> y >> id;
	(map[x][y].total_cars)++;
}

void	CommunicationSocket::get_peers(Map &map) const
{
	std::string			raw;
	std::string			header;
	bool				done = false;

	while (!done)
	{
		raw = this->read();
		std::stringstream ss(raw);
		for (std::string line; std::getline(ss, line);)
		{
			std::stringstream ss2(line);
			ss2 >> header;
			if (header == "pnw")		/* Position of the peers */
				this->get_peer(line, map);
			else if (header == "done")
				done = true;
			else
				std::cout << "CommunicationSocket::get_peers() : Wrong header\n";
		}
	}
}

void				CommunicationSocket::disconnect()
{
	this->_connected = false;
	if (close(this->_socket) < 0)
		throw(std::runtime_error("CommunicationSocket(): disconnect close error"));
}

/*
** ==================		PUBLIC	 	==================
*/
/*		send datagram into the _socket		*/
void		CommunicationSocket::send_datagram(std::string header, std::string message) const
{
	std::string			data(header + message);

	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
		throw("CommunicationSocket:send_datagram(): send error\n");
}

void		CommunicationSocket::send_datagram(Datagram const & datagram) const
{
	std::string			data(datagram.getHeader() + datagram.getMessage());
	// std::cout << "sending datagram : [" << data << "]" << std::endl;;
	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
		throw("CommunicationSocket:send_datagram(): send error\n");
}

Map		CommunicationSocket::get_first_info(Map &map, Position& start, Position &end)
{
	std::string					header;
	std::string					raw;
	std::vector<std::string>	tokens;
	int							done = 0;
	bool						gotsize = false;

	this->_events["msz"] = [&map, &gotsize](std::string data)
	{
		int					x;
		int					y;
		std::string			header;
		std::stringstream	ss(data);

		ss >> header >> x >> y;
		map.resize(x);
		for (auto& m : map)
			m.resize(y);
		gotsize = true;
	};

	this->_events["bct"] = [&map, &gotsize](std::string data)
	{
		if (!gotsize)
		{
			std::cout << "No size\n";
			exit(1);
		}
		int				x;
		int				y;
		std::string		header;
		std::stringstream	ss(data);
		Square			square;

		ss >> header >> x >> y >> square.is_road;
		square.total_cars = 0;
		map[x][y] = square;
	};
	this->_events["ppo"] = [&start, &gotsize](std::string data)
	{
		if (!gotsize)
		{
			std::cout << "No size\n";
			exit(1);
		}
		std::cout << "je suis en " << data << std::endl;
		std::string			header;
		std::stringstream	ss(data);
		int					id;

		ss >> header >> id >> start.x >> start.y;
	};

	this->_events["des"] = [&end, &gotsize](std::string data)
	{
		if (!gotsize)
		{
			std::cout << "No size\n";
			exit(1);
		}

		std::string			header;
		std::stringstream	ss(data);

		ss >> header >> end.x >> end.y;
	};
	this->_events["pnw"] = [&map, &gotsize](std::string data)
	{
		if (!gotsize)
		{
			std::cout << "No size\n";
			exit(1);
		}
		std::string			header;
		std::stringstream	ss(data);
		int					x;
		int					y;
		int					id;

		ss >> header >> id >> x >> y;
		map[x][y].total_cars++;
	};
	while (done != 2)
	{
		raw = this->read();
		std::stringstream ss(raw);
		for (std::string line; std::getline(ss, line);)
		{
			std::stringstream ss2(line);
			ss2 >> header;
			if (this->_events.count(header) > 0)
			{
				this->_events[header](line);
			}
			else
			{
				std::cout << KRED << "get_first_info(): Should not go here : " << KNRM << KYEL << line << KNRM << std::endl;
				done++;
			}
		}
		// std::stringstream ss(raw);
	}

	return (map);
}

void		CommunicationSocket::wait_for_game(void) const
{
	std::string		data;
	bool			start = false;

	std::cout << "wait for game\n";
	while (!start)
	{
		data = this->read();
		std::stringstream ss(data);
		for (std::string line; std::getline(ss, line);)
		{
			if (line == "start")
				start = true;
			else
			{
				std::cout << "Waiting for game to start but received : " << data << std::endl;
			}
		}
	}
	std::cout << KGRN << " !! Simulation started !! " << KNRM << std::endl;
}

bool		CommunicationSocket::get_datagram(Datagram & datagram)
{
	try
	{
		if (!this->_datagram_queue.empty())
		{
			datagram = this->_datagram_queue.front();
			this->_datagram_queue.pop();
			return (true);
		}
	}
	catch (...)
	{
		return (false);
	}
	return (false);
}

// void			CommunicationSocket::wait_for_move(void) const
// {
//
// }


/*	while loop with a select statement to get message from server */
void				CommunicationSocket::wait_for_move(void)
{
	struct timeval		tv;
	fd_set				rfds;
	fd_set				copy;
	int					ret;
	bool				moved = false;
	Datagram			data;

	FD_ZERO(&_rfds);
	FD_SET(_socket, &_rfds);
	FD_ZERO(&copy);
	FD_COPY(&_rfds, &copy);

	/* Need to think about the structure, multithreaded or not */
	while (!moved && select(_socket + 1, &_rfds, NULL, NULL, NULL) >= 0)
	{
		if (FD_ISSET(_socket, &copy))
		{
			moved = this->get_datagram();
			FD_ZERO(&_rfds);
			FD_COPY(&copy, &_rfds);
		}
	}
}
