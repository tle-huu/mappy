#pragma once

#include <vector>
#include <map>
#include <unordered_map>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct	Position
{
	int x;
	int y;
};

struct	Square
{
	bool is_road;
	int total_cars;
};

typedef std::vector<std::vector<Square> > Map;

template<class T>
using graph = std::vector<std::unordered_map<size_t, T>>;
