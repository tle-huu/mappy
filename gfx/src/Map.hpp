#pragma once

#include "CoreInclude.hpp"
#include "ServerMonitor.hpp"
#include <unordered_map>
#include <list>
#include "Image2D.hpp"
#include "Window.hpp"

struct	MovingCar
{
	glm::ivec2 from;
	glm::ivec2 to;
	double time;
	double timeLeft;
};

class	Map
{
	std::unordered_map<std::string, std::function<void(std::string)>> _events;
	ServerMonitor _serverMonitor;
	Image2D _imageRenderer;
	std::vector<unsigned char> _grid;
	int _width;
	int _height;

	std::unordered_map<int, glm::ivec2> _carPositions;
	std::list<MovingCar> _movingCars;
	std::vector<int> _staticCars;
	std::vector<int> _traffic;

	void	drawMovingCar(std::vector<unsigned char>&, const MovingCar&);
	void	drawStaticCars(std::vector<unsigned char>&);
	void	drawTraffic(std::vector<unsigned char>&);
	void	render(Window&, const std::vector<unsigned char>&);
	
public:
	Map(int fd);
	~Map(void);

	void	Update(double dt, Window&);
};
