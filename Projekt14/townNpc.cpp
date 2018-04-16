#include "townNpc.h"

int townNpc::_x = 0;
int townNpc::_y = 0;

townNpc::townNpc(int x, int y)
{
	_x = x;
	_y = y;
}


townNpc::~townNpc()
{
}


void townNpc::talk(Player &player) {
	std::cout << "...\n";
}