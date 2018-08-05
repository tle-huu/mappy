#include "Car.hpp"

Car::Car()
{
	Map map;
	_communicator.get_info(map, _current_pos, _destination);
	_ai = new AI(map);
	_communicator.wait_for_game();
	_cooldown = 0;
}

Car::~Car()
{
	delete _ai;
}

void	Car::update(double dt)
{
	_ai->update(_communicator.get_updates());
	_cooldown -= dt;
	if (cooldown > 0)
		return;
	_cooldown = 0;

	Position newPos = _ai->where_to(_current_pos, _destination, _cooldown);
	_communicator.change_location(_current_pos, newPos);
	_current_pos = newPos;
}
