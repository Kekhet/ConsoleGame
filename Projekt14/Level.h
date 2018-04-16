#pragma once
#include "Player.h"
#include "EnemyList.h"
#include "Reward.h"
#include "temple.h"
#include "merchant.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <algorithm>


using namespace std;
class Level
{
	friend class gameSystem;
	vector <string> _levelData;
	vector <Enemy> _enemies;
	vector <townNpc> _npc;
	 static bool isFinished;
	 int numEnemies;
	
public:
	Level();
	~Level();

	void loadLevel(string fileName, Player &player);
	void saveLevel(Player &player);
	void printLevel(Player _player);
	void loadSavedData(string fileName, Player &player);

	void movePlayer(char intput, Player &player);
	void moveEnemy(Player &player);
	char getTile(int x, int y);
	void setTile(int x, int y, char Tile);
	void setDeadStatus(bool newStatus) { isFinished = newStatus; }
	static bool getDeadStatus() {return isFinished; }
	void showLevelLegend();

	private:
	void tileEffect(Player &player, int targetX, int targetY);
	void processBattle(Player &player, int targetX, int targetY);
	void processEnemyMove(Player &player, int index, int targetX, int targetY);

};

