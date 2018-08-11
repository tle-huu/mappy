#include <iostream>
#include <stdio_filebuf.h>

using __gnu_cxx::stdio_filebuf;
using std::istream;
using std::ostream;

inline stdio_filebuf<char> * fileBufFromFD (int fd, std::_Ios_Openmode mode)
{
	return (new stdio_filebuf<char> (fd, mode));
}

istream * createInStreamFromFD (int fd)
{
	stdio_filebuf<char> * fileBuf = fileBufFromFD (fd, std::ios::in);
	return (new istream (fileBuf));
}

ostream * createOutStreamFromFD (int fd)
{
  stdio_filebuf<char> * fileBuf = fileBufFromFD (fd, std::ios::out);
  return  (new ostream (fileBuf));
}
