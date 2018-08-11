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

		_traffic.resize(_width * _height);
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
				assert(w < _width && w >= 0 && h < _height && h > 0);
				size_t index = (w + h * _width * 5) * 4;
				unsigned barriercol = 0xff222222;

				if (!road)
					std::memmove(&_grid[index], &barriercol, 4);
			}
		}
	};
	_events["mvd"] = [this](std::string data)
	{
		std::stringstream ss(data);

		MovingCar car;
		double time;
		int id;

		ss >> car.from.x >> car.from.y >> car.to.x >> car.to.y >> car.time >> id;

		assert(car.from.x >= 0 && car.from.x < _width && car.from.y >= 0 && car.from.y < _height);
		assert(car.to.x >= 0 && car.to.x < _width && car.to.y >= 0 && car.to.y < _height);

		_carPositions[id] = car.to;

		car.timeLeft = car.time;
		_staticCars[car.from.x + car.from.y * _width]--;
		_movingCars.push_back(car);
		_traffic[car.from.x + car.from.y * _width]--;
		_traffic[car.to.x + car.to.y * _width]++;
	};
	_events["pnw"] = [this](std::string data)
	{
		std::stringstream ss(data);

		int x, y;
		int id;

		ss >> id  >> x >> y;

		_carPositions[id] = glm::ivec2(x, y);
		_staticCars[x + y * _width]++;
		_traffic[x + y * _width]++;
	};
	_events["pdi"] = [this](std::string data)
	{
		std::stringstream ss(data);

		int x, y;
		int id;

		ss >> x >> y >> id;

		x = _carPositions[id].x;
		y = _carPositions[id].y;
		_staticCars[x + y * _width]--;
		_traffic[x + y * _width]--;
	};
	_events["des"] = [this](std::string data)
	{
		std::stringstream ss(data);

		int x, y;

		ss >> x >> y;

		for (int w = x * 5; w < (x + 1) * 5; w++)
		{
			for (int h = y * 5; h < (y + 1) * 5; h++)
			{
				size_t index = (w + h * _width * 5) * 4;
				unsigned destcol = 0xff77bb88;
				std::memmove(&_grid[index], &destcol, 4);
			}
		}
	};
}

Map::~Map(void)
{
}

void	Map::drawMovingCar(std::vector<unsigned char>& image, const MovingCar& car)
{
	glm::ivec2 dir = (car.to - car.from) * 5;

	dir = dir * (1.0 - (car.timeLeft / car.time));

	glm::ivec2 pos = car.from * 5 + glm::ivec2(2) + dir;
	
	size_t index = pos.x + pos.y * _width * 5;
	unsigned color = 0xff777722;
	std::memmove(&image[index * 4], &color, 4);
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
				unsigned color = 0xff777722;
				std::memmove(&image[index * 4], &color, 4);
			}
		}
	}
}

static unsigned	traffic_color(int traffic, unsigned oldcol)
{
	if (traffic > 10)
		traffic = 10;
	unsigned red = oldcol % 256;
	oldcol /= 256;
	unsigned green = oldcol % 256;
	oldcol /= 256;
	unsigned blue = oldcol % 256;

	red = (red * (10 - traffic) + 255 * traffic) / 10;
	return red + 256 * green + 256 * 256 * blue + 256ul * 256 * 256 * 255;
}

void	Map::drawTraffic(std::vector<unsigned char>& image)
{
	for (int w = 0; w < _width; w++)
	{
		for (int h = 0; h < _height; h++)
		{
			int traffic = _traffic[w + h * _width];
			if (traffic > 0)
			{
				for (int x = w * 5; x < w * 5 + 5; x++)
				{
					for (int y = h * 5; y < h * 5 + 5; y++)
					{
						size_t index = x + y * _width * 5;
						unsigned oldcol;
						std::memmove(&oldcol, &image[index * 4], 4);
						unsigned color = traffic_color(traffic, oldcol);
						std::memmove(&image[index * 4], &color, 4);
					}
				}
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

	drawTraffic(image);
	
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
