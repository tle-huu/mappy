#ifndef DATAGRAM_HPP
# define DATAGRAM_HPP

# include <string>
# include <iostream>

class Datagram
{
	private:
		std::string			_header;
		std::string			_message;

	public:
		Datagram();
		Datagram(std::string header, std::string message);
		~Datagram();

		Datagram(Datagram const & src);
		Datagram &		operator=(Datagram const & rhs);

		std::string			getHeader() const;
		std::string			getMessage() const;
		void				setHeader(std::string header);
		void				setMessage(std::string message);
};

std::ostream &		operator<<( std::ostream & o, Datagram const & rhs);

#endif
