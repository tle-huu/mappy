#pragma once

#include <vector>
#include <map>

struct	Position
{
	int x;
	int y;
};

struct	Square
{
	bool is_road;
	int total_cars;
    // 
	// Square() = default;
	// Square(Square const & src)
	// {
	// 	*this = src;
	// }
    //
	// Square	&	operator=(Square const &rhs)
	// {
	// 	this->is_road = rhs.is_road;
	// 	this->total_cars = rhs.total_cars;
	// 	return (*this);
	// }
};


typedef std::vector<std::vector<Square> > Map;
