#include "Map.hpp"

Map::Map(int fd) : _serverMonitor(fd)
{
	_width = 0;
	_height = 0;
	
	_events["msz"] = [this](std::string data)
	{
		std::stringstream ss(data);

		ss >> _width >> _height;

		std::cout << _width << " " <<  _height << std::endl;

		_staticCars.resize(_width * _height);
		_grid.resize(_width * _height * 4 * 25); // 25 pixels per grid square
		for (int w = 0; w < _width * 5; w++)
		{
			for (int h = 0; h < _height * 5; h++)
			{
				size_t index = (w + h * _width * 5) * 4;
				unsigned roadcol = 0xff778888;

				std::memmove(&_grid[index], &roadcol, 4);
			}
		}
	};
	_events["bct"] = [this](std::string data)
	{
		std::stringstream ss(data);

		int x, y, road;
		
		ss >> x >> y >> road;

		for (int w = x * 5; w < (x + 1) * 5; w++)
		{
			for (int h = y * 5; h < (y + 1) * 5; h++)
			{
				size_t index = (w + h * _width * 5) * 4;
				unsigned barriercol = 0xff222222;

				if (road)
					std::memmove(&_grid[index], &barriercol, 4);
			}
		}
	};
	_events["mvd"] = [this](std::string data)
	{
		std::stringstream ss(data);

		MovingCar car;
		double time;

		ss >> car.from.x >> car.from.y >> car.to.x >> car.to.y >> car.time;

		car.timeLeft = car.time;
		_staticCars[car.from.x + car.from.y * _width]--;
		_movingCars.push_back(car);		
	};
	_events["pnw"] = [this](std::string data)
	{
		std::stringstream ss(data);

		int x, y;

		ss >> x >> x >> y;

		std::cout << x << " " << y << std::endl;
		_staticCars[x + y * _width]++;
	};
	_events["pdi"] = [this](std::string data)
	{
		std::stringstream ss(data);

		int x, y;

		ss >> x >> y;

		_staticCars[x + y * _width]--;		
	};
}

Map::~Map(void)
{
}

void	Map::drawMovingCar(std::vector<unsigned char>& image, const MovingCar& car)
{
	glm::ivec2 dir = (car.from - car.to) * 5;

	dir *= car.timeLeft / car.time;

	glm::ivec2 pos = car.from * 5 + dir;
	
	size_t index = pos.x + pos.y * _width * 5;
	unsigned color = 0xff223377;
	std::memmove(&image[index * 4], &color, 4);
}

static unsigned	density_color(int density)
{
	if (density <= 1)
		return 0xff223377;
	if (density == 2)
		return 0xff223388;
	if (density <= 3)
		return 0xff223399;
	if (density <= 5)
		return 0xff2233bb;
	if (density <= 8)
		return 0xff3355dd;
	if (density <= 13)
		return 0xff4466ff;
	return 0xff6688ff;
}

void	Map::drawStaticCars(std::vector<unsigned char>& image)
{
	for (int w = 0; w < _width; w++)
	{
		for (int h = 0; h < _height; h++)
		{
			int totalCars = _staticCars[w + h * _width];
			if (totalCars)
			{
				size_t index = (w * 5 + 2) + (h * 5 + 2) * (_width * 5);
				unsigned color = density_color(totalCars);
				
				std::memmove(&image[index * 4], &color, 4);
			}
		}
	}
}

void	Map::render(Window& window, const std::vector<unsigned char>& image)
{
	float screenAspect = window.GetAspect();
	float imageAspect = (float)_width / (float)_height;
	if (screenAspect / imageAspect > 1)
	{
		float offset = imageAspect / screenAspect;
		window.SetRenderMask((1 - offset) / 2.0f, 0, offset, 1);
	}
	else if (screenAspect / imageAspect < 1)
	{
		float offset = screenAspect / imageAspect;
		window.SetRenderMask(0, (1 - offset) / 2.0f, 1, offset);
	}
	_imageRenderer.Render(image, _width * 5, _height * 5);
	window.RemoveRenderMask();
}

void	Map::Update(double dt, Window& window)
{
	_serverMonitor.Update();
	const std::vector<const std::string>& commands = _serverMonitor.Commands();
	const std::vector<const std::string>& data = _serverMonitor.Data();
	
	for (size_t i = 0; i < commands.size(); i++)
	{
		if (_events.count(commands[i]) != 0)
			_events[commands[i]](data[i]);
	}

	std::vector<unsigned char> image = _grid;

	auto it = _movingCars.begin();
	while (it != _movingCars.end())
	{
		it->timeLeft -= dt;
		if (it->timeLeft < 0)
		{
			_staticCars[it->to.x + it->to.y * _width]++;
			_movingCars.erase(it++);
			continue;
		}
		drawMovingCar(image, *it);
		++it;
	}
	drawStaticCars(image);
	
	render(window, image);
}
