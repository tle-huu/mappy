#include "CommunicationSocket.hpp"


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

void				CommunicationSocket::disconnect()
{
	this->_connected = false;
	if (close(this->_socket) < 0)
		throw("CommunicationSocket:disconnect(): close error\n");
}

void				CommunicationSocket::send_datagram(std::string header, std::string message) const
{
	std::string			data(header + message);

	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
		throw("CommunicationSocket:send_datagram(): send error\n");
}
//
// bool				CommunicationSocket::send_datagram(Datagram datagram)
// {
// 	std::string			data(datagram.header + datagram.message);
//
// 	if (send(this->_socket, data.c_str(), data.length(), 0) < 0)
// 		throw("CommunicationSocket:send_datagram(): send error\n");
// }
