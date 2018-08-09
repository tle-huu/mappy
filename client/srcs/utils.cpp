#include "utils.hpp"
#include <iostream>
#include <string>

int			coord_to_index(int x, int y, int width, int height)
{
	if (x > width || y > height)
	{
		std::cout << KRED << "COOR TO INDEX POSITION OUT OF MAP SIZE" << KNRM << std::endl;
		exit(1);
	}

	return (x % width + height * y);
}

void		index_to_coor(int n, int & x, int &y , int width)
{
	x = n % width;
	y = n / width;
}

void		print_map(Map const & map)
{
	int width = map.size();
	int height = map[0].size();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j].is_road)
				std::cout << KGRN << std::to_string(coord_to_index(i, j, width, height)) << KNRM;
			else
				std::cout << KRED << std::to_string(coord_to_index(i, j, width, height)) << KNRM;
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
}
