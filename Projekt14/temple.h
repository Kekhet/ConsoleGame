#pragma once
#include "townNpc.h"
using namespace std;
class temple :
	public townNpc
{
	static bool regen;

public:
	temple(int x, int y);
	~temple();
	static void talk(Player &player);
	static bool ifRegenAvalible() { if (regen == false) return true; return false; }
};