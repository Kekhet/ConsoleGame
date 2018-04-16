#pragma once
#include <iostream>
#include <conio.h>
#include "Player.h"

class townNpc
{
	static int _x;
	static int _y;
	char _tile;
public:
	townNpc(int x, int y);
	~townNpc();

	virtual void talk(Player &player);
	char getTile() { return _tile; }
	void setTile(char tile) { _tile = tile; }
	static void getCoord(int &x, int &y) { x = _x; y = _y; }

};