#include "CommunicationSocket.hpp"

/*
** ==================		CONSTRUCTORS DESTRUCTORS	 	==================
*/

CommunicationSocket::CommunicationSocket()
{}

CommunicationSocket::CommunicationSocket(char* addr, int port) : _addr(addr), _port(port)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (!(proto = getprotobyname("tcp")))
		throw(std::runtime_error("CommunicationSocket(): getprotobyname error"));
	if ((this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		throw(std::runtime_error("CommunicationSocket(): socket error"));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = (std::string(addr) == "localhost") ? inet_addr("127.0.0.1")
								: inet_addr(addr);
	if (connect(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		throw(std::runtime_error("CommunicationSocket(): connect error"));
	this->_connected = true;
}

CommunicationSocket::~CommunicationSocket()
{
	std::cout << "Communication socket destroyed" << std::endl;
}

/*
** ==================		READING	 	==================
*/


std::string			CommunicationSocket::read(void) const
{
	char				buffer[BUFF_SIZE] = {0};
	int					ret;
	Datagram			datagram;

	if ((ret = recv(this->_socket, buffer, BUFF_SIZE - 1, 0)) < 0)
		throw("CommunicationSocket:get_datagram(): recv error\n");
	buffer[ret] = 0;
	return (std::string(buffer));
}

void				CommunicationSocket::get_datagram(void)
{
	Datagram			datagram;
	std::size_t			spliter;
	std::string			raw;

	raw = this->read();
	std::stringstream ss(raw);

	for (std::string line; std::getline(ss, line);)
	{
		std::cout << "raw_message : [" << line << "]" << std::endl;
		if ((spliter = line.find(";;")) == std::string::npos)
			throw(std::runtime_error("CommunicationSocket(): get_datagram line.find error"));
		std::cout << " spliter : " << spliter << std::endl;
		datagram.setHeader(line.substr(0, spliter));
		datagram.setMessage(line.substr(spliter + 2));
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

void				CommunicationSocket::disconnect()
{
	this->_connected = false;
	if (close(this->_socket) < 0)
		throw("CommunicationSocket:disconnect(): close error\n");
}

/*
** ==================		PUBLIC	 	==================
*/

/*	while loop with a select statement to get message from server */
void				CommunicationSocket::listen(void)
{
	this->get_datagram();
	std::cout << " Here is what I just read : ";
	std::cout << this->_datagram_queue.front();
	std::cout << std::endl;
}

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

	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
		throw("CommunicationSocket:send_datagram(): send error\n");
}

Map			CommunicationSocket::get_map()
{
	std::string					header;
	std::string					raw;
	std::vector<std::string>	tokens;
	Map							map;
	bool						done = false;

	this->_events["msz"] = [&map](std::string data)
	{
		int		x;
		int		y;
		std::stringstream		ss(data);

		ss >> x >> y;
		map.resize(x);
		for (auto& m : map)
			m.resize(y);
	};

	this->_events["bct"] = [&map](std::string data)
	{
		int				x;
		int				y;
		std::string		header;
		std::stringstream	ss(data);
		Square			square;


		ss >> header >> x >> y >> square.is_road;
		square.total_cars = 0;
		map[x][y] = square;
	};
	raw = this->read();
	std::stringstream ss0(raw);
	ss0 >> header;
	if (header != "msz")
		std::cout << "CommunicationSocket::get_map size fucked up" << std::endl;
	this->_events["msz"](raw);
	while (!done)
	{
		raw = this->read();
		std::stringstream ss(raw);
		for (std::string line; std::getline(ss, line);)
		{
			std::stringstream ss2(line);
			ss2 >> header;
			if (header == "bct")
				this->_events["bct"](line);
			else
				done = true;
		}
	}
	return (map);
}

Position	CommunicationSocket::get_position(void)
{
	Position		pos;
	std::string		raw;

	this->_events["pos"] = [&pos](std::string data)
	{
		std::string			header;
		std::stringstream	ss(data);

		ss >> header >> pos.x >> pos.y;
	};
	raw = this->read();
	this->_events["pos"](raw);
	return (pos);
}

Position	CommunicationSocket::get_destination(void)
{
	Position		pos;
	std::string		raw;

	this->_events["des"] = [&pos](std::string data)
	{
		std::string		header;
		std::stringstream	ss(data);

		ss >> header >> pos.x >> pos.y;
	};
	raw = this->read();
	this->_events["des"](raw);
	return (pos);
}

void	CommunicationSocket::get_peer(std::string data, Map &map) const
{
	std::string				header;
	int						x;
	int						y;
	std::stringstream		ss(data);

	ss >> header >> x >> y;
	map[x][y].total_cars++;
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
			if (header == "pee")
				this->get_peer(line, map);
			else if (header == "done")
				done = true;
			else
				std::cout << "CommunicationSocket::get_peers() : Wrong header\n";
		}
	}
}

void		CommunicationSocket::get_info(Map &map, Position& start, Position &end)
{
	map = this->get_map();
	start = this->get_position();
	end = this->get_destination();
	this->get_peers(map);
}

void		CommunicationSocket::wait_for_game(void) const
{
	std::string		data;

	while ((data = this->read()) != "start")
		std::cout << "Waiting for game to start but received : " << data << std::endl;
	std::cout << "!! Simulation started !! " << std::endl;
}
