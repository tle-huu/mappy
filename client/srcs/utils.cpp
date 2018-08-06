#include "utils.hpp"


int			coord_to_index(int x, int y, int width, int height)
{
	return (x % width + height * y);
}

void		index_to_coor(int n, int & x, int y , int width)
{
	x = n % width;
	y = n / width;
}
