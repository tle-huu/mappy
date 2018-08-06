#include "Car.hpp"

Car::Car() : _ai(_map)
{

	_events["mvd"] = [this](std::string data)
	 {
		 std::stringstream ss(data);
		 Position from, to;
		 ss >> from.x >> from.y >> to.x >> to.y;
		 _map[from.x][from.y] -= 1;
		 _map[to.x][to.y] += 1;
	 };
	_communicator.get_first_info(_map, _current_pos, _destination);
	_communicator.wait_for_game();	
}

Car::~Car()
{
}

static Datagram	generate_move_data(Position from, Position to, double time)
{
	Datagram out;
	out.header = "mvd";

	std::stringstream ss;
	ss << from.x << " " << from.y << " " << to.x << " " << to.y << " " << time;
	out.message = ss.str();

	return out;
}

void	Car::move()
{	
	for (Datagram d; _communicator.get_datagram(d);)
		_events[d.header](d.message);
	
	double time;
	Position newPos = _ai.where_to(_current_pos, _destination, &time);
	Datagram moveData = generate_move_data(_current_pos, newPos, time);
	_communicator.send_datagram(moveData);
	_communicator.wait_for_move();
}
