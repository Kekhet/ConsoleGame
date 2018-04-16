#pragma once
#include "Level.h"
#include "Player.h"
#include "EnemyList.h"
#include <string>
#include <conio.h>
using namespace std;

class gameSystem{
	friend class Level;

	Player _player;
	Level _level;

	bool isDone=false;

public:
	gameSystem(string levelFileName);
	gameSystem(string levelFileName, int &LOADER);
	~gameSystem();


	void playGame();
	void getPlayerMove();
	void getEnemyMove();
	void setDone(bool x) { isDone = x; _level.setDeadStatus(0); }



};

