#ifndef UTILS_HPP
# define UTILS_HPP
# include "mappy_client.hpp"


int			coord_to_index(int x, int y, int width, int length);
void		index_to_coor(int n, int & x, int &y , int width);

void		print_map(Map const & map);

#endif
