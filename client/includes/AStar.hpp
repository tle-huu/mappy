#pragma once

#include <unordered_map>
#include <queue>
#include <vector>
#include "mappy_client.hpp"

std::vector<int>        a_star(graph<double*> graph,
			       int start,
			       int goal,
			       std::function<double(int, int)> heuristic);
