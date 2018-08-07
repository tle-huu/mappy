#include "Car.hpp"

Car::Car(const char* addr, int port) : _communicator(addr, port)
{
	_events["mvd"] = [this](std::string data)
	 {
		 std::stringstream ss(data);
		 Position from, to;
		 ss >> from.x >> from.y >> to.x >> to.y;
		 _map[from.x][from.y].total_cars -= 1;
		 _map[to.x][to.y].total_cars += 1;
	 };
	_communicator.get_first_info(_map, _current_pos, _destination);
	_ai = new Ai(_map);
	_communicator.wait_for_game();
}

Car::~Car()
{
	delete _ai;
}

static Datagram	generate_move_data(Position from, Position to, double time)
{
	Datagram out;
	out.setHeader("mvd ");

	std::stringstream ss;
	ss << from.x << " " << from.y << " " << to.x << " " << to.y << " " << time;
	out.setMessage(ss.str());

	return out;
}

void	Car::move()
{
	for (Datagram d; _communicator.get_datagram(d);)
		_events[d.getHeader()](d.getMessage());

	double time = 1;
	Position newPos = _ai->where_to(_current_pos, _destination, time);
	Datagram moveData = generate_move_data(_current_pos, newPos, time);
	_current_pos = newPos;
	_communicator.send_datagram(moveData);
	_communicator.wait_for_move();
}
