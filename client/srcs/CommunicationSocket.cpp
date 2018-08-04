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
** ==================		PRIVATE	 	==================
*/



void				CommunicationSocket::get_datagram(void)
{
	char				buffer[4096] = {0};
	int					ret;
	std::string			raw_message;
	Datagram			datagram;
	std::size_t			spliter;

	if ((ret = recv(this->_socket, buffer, 4095, 0)) < 0)
		throw("CommunicationSocket:get_datagram(): recv error\n");
	buffer[ret] = 0;
	raw_message = buffer;
	std::cout << "raw_message : [" << raw_message << "]" << std::endl;
	if ((spliter = raw_message.find(";;")) == std::string::npos)
		throw(std::runtime_error("CommunicationSocket(): get_datagram raw_message.find error"));
	std::cout << " spliter : " << spliter << std::endl;
	datagram.setHeader(raw_message.substr(0, spliter));
	datagram.setMessage(raw_message.substr(spliter + 2));
	try
	{
		this->_datagram_queue.push(datagram);
	}
	catch (std::exception &e)
	{
		std::cout << "CommunicationSocket::getDatagram(): " << e.what() << std::endl;
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
void				CommunicationSocket::send_datagram(std::string header, std::string message) const
{
	std::string			data(header + message);

	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
		throw("CommunicationSocket:send_datagram(): send error\n");
}

void				CommunicationSocket::send_datagram(Datagram const & datagram) const
{
	std::string			data(datagram.getHeader() + datagram.getMessage());

	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
		throw("CommunicationSocket:send_datagram(): send error\n");
}
