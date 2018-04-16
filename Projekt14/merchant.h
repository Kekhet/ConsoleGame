#pragma once
#include "townNpc.h"
#include "EnemyList.h"
class merchant :
	public townNpc
{

	static bool ratsKilled;
	static bool isBought[4];

public:
	merchant(int x, int y);
	merchant(int x, int y, int b0,int b1,int b2, int b3);
	~merchant();
	static void talk(Player &player, vector <Enemy> _enemies);
	static void shop(Player &player);

	static string save() {
		string buffer;
		int x, y;
		getCoord(x, y);

		string retVal = to_string(x);
		retVal += buffer;
		retVal += ';';

		buffer = to_string(y);
		retVal += buffer;
		retVal += ';';

		buffer = to_string(isBought[0]);
		retVal += buffer;
		retVal += ';';

		buffer = to_string(isBought[1]);
		retVal += buffer;
		retVal += ';';

		buffer = to_string(isBought[2]);
		retVal += buffer;
		retVal += ';';

		buffer = to_string(isBought[3]);
		retVal += buffer;
		retVal += ';\n\n';

		return retVal;
	}
};

