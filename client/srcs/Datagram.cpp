#include "Datagram.hpp"


/*
** ==================		CONSTRUCTORS DESTRUCTORS	 	==================
*/
Datagram::Datagram() : _header("NULL"), _message("NULL") {}

Datagram::Datagram(std::string header, std::string message) :	_header(header),
																_message(message)
{}

Datagram::~Datagram() {}

Datagram::Datagram(Datagram const &src)
{
	this->_header = src._header;
	this->_message = src._message;
}

Datagram & Datagram::operator=(Datagram const & src)
{
	this->_header = src._header;
	this->_message = src._message;
	return (*this);
}

/*
** ==================		PUBLIC	 	==================
*/

std::string			Datagram::getHeader() const
{
	return (this->_header);
}

std::string			Datagram::getMessage() const
{
	return (this->_message);
}

void				Datagram::setHeader(std::string header)
{
	this->_header = header;
}

void				Datagram::setMessage(std::string message)
{
	this->_message = message;
}

/*
** ==================		OVERLOAD OUTSIDE CLASS OPERATORS	 	==================
*/

std::ostream &		operator<<( std::ostream & o, Datagram const & rhs)
{
	o << "<header> [" << rhs.getHeader() << "];; <message> [" << rhs.getMessage() << "]"<< std::endl;
	return (o);
}
