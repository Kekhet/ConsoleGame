#pragma once
#include "Reward.h"
#include <string>
#include <time.h>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

class Enemy
{

	//Map properties
	string _Name;
	char _Tile;

	//Coordinates
	int _x, _y;

	//Statistics
	int _Health;
	int _Attack;
	int _Defence;
	int _Dodge;

	//Reward
	Reward killReward;

public:
	Enemy();
	Enemy(int X, int Y, string Name, char Tile, int Health, int Attack, int Defence, int Dodge, int expVal, int goldVal);
	~Enemy();
	string getSaveData();
	void getPosition(int &x, int &y);
	void setPosition(int x, int y);
	string getName();
	char getTile() { return _Tile; }
	void setName(string newName) { _Name = newName; }
	bool isAlive() { if (_Health > 0) return true; return false; }

	int attack();
	bool dodge();
	Reward takeDamage(int dmgTaken);

	char getMove(int playerX, int playerY);
};

