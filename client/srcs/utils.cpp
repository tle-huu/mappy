#include "utils.hpp"
#include <iostream>


int			coord_to_index(int x, int y, int width, int height)
{
	return (x % width + height * y);
}

void		index_to_coor(int n, int & x, int &y , int width)
{
	x = n % width;
	y = n / width;
}

void		print_map(Map const & map)
{
	for (auto& x : map)
	{
		for (auto& s : x)
		{
			if (s.is_road)
				std::cout << KGRN << "Road" << KNRM;
			else
				std::cout << KRED << "Wall" << KNRM;
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
}
