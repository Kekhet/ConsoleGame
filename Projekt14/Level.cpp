#include "Level.h"
bool Level::isFinished = false;

string namesRat[5] = { "Remy the Rat", "Ratty", "Splinter", "Squeakers","Wormtail" };
string namesGuard[5] = { "Spearman Robert", "Swordman Roy","Warden Bob", "Sleeping Tom",  "Guard Patrick" };
string namesDog[5] = { "Dogo", "Pongo", "Chita", "Cruella", "Baskervile" };
string namesVillager[5] = { "Django the Servant", "Cleveland the Cook", "Winnfield the Buttler", "Axel the Jester", "Frank the Helper" };
string namesEliteGuard[5] = { "lady Briane from Cake", "sir Roderick de Gulp", "sir Thomas von Fartingbottom", "sir Lanceless", "sir William Wallace" };
string namesKing[5] = { "King Joffrey", "Grand Wizard King ", "King Stannis", "King Mance Rayder", "King Anthony" };
string namesQueen[5] = { "Queen Kenny", "Queen of Hearts ", "Queen Cercei", "Queen Deny", "Queen Margeary" };

Level::Level() {}
Level::~Level() {}


void Level::loadLevel(string fileName, Player &player) {
	//Loading of LEVEL.txt file
	ifstream file;
	file.open(fileName);
	if (file.fail()) { cout << "ERROR: Could not load level.\n"; system("PAUSE"); exit(1); }

	string line;
	while (getline(file, line)) {
		_levelData.push_back(line);
	}
	file.close();

	//Rebuilding game data
	char actualTile;
	numEnemies = 0;
	default_random_engine randomG(unsigned int(time(NULL)));
	uniform_int_distribution<int>tab5(0, 4);

	for (int i = 0; i < (int)(_levelData.size()); i++) {
		for (int j = 0; j < int(_levelData[i].size()); j++) {
			actualTile = _levelData[i][j];


			//	Enemy**r = new Enemy*;
				//Load symbols into elements!
			switch (actualTile) {
			case '@':   //Player
				player.setPosition(j, i);
				break;
			case 'R':  //Rat
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesRat[tab5(randomG)], actualTile, 10, 10, 1, 35, 10, rand()%5+5));
				break;
			case 'G': //Guard
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesGuard[tab5(randomG)], actualTile, 50, 60, 5, 5, 50, rand()%20+50));
				break;
			case 'D': //Dog
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesDog[tab5(randomG)], actualTile, 30, 40, 2, 20, 50, rand()%30+10));
				break;
			case 'V': //Villager
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesVillager[tab5(randomG)], actualTile, 20, 15, 2, 10, 30, rand()%20+40));
				break;
			case 'E': //Elite Guard
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesEliteGuard[tab5(randomG)], actualTile, 70, 75, 8, 5, 100, rand()%50+70));
				break;
			case 'K': //King
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesKing[tab5(randomG)], actualTile, 100, 85, 5, 5, 300, rand()%60+150));
				break;
			case 'Q': //Queen
				numEnemies++;
				_enemies.push_back(Enemy(j, i, namesQueen[tab5(randomG)], actualTile, 100, 5, 5, 5, 300, rand()%70+50));
				break;
			case 'T': //Temple
				_npc.push_back(temple(j,i));
			case 'M': //Merchant
				_npc.push_back(merchant(j,i));
			default:
				break;
			}

		}
	}

}

void Level::printLevel(Player _player) {
	//cout << string(10, '\n');
	system("cls");
	cout << "Truthless v1.0(beta) --- Jakub Wenda\n";
	cout << _player<<endl;

	for (int i = 0; i < int(_levelData.size()); i++) {
		cout << _levelData[i]<<endl;
	}
	cout << endl;
}

//Player turn!
void Level::movePlayer(char intput, Player &player) {
	
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	if (intput == 27) { 
		system("cls");
		cout << "Do you want to exit? (Y/N): ";
		char newintput = _getch();

		if (newintput == 'Y' || newintput == 'y') {
			saveLevel(player);
			exit(0);
		}
		return;
	}

	switch (intput) {
	case'W':
	case'w':
		tileEffect(player, playerX, playerY - 1);
		break;

	case'S':
	case's':
		tileEffect(player, playerX, playerY + 1);
		break;

	case'A':
	case'a':
		tileEffect(player, playerX - 1, playerY);
		break;

	case'D':
	case'd':
		tileEffect(player, playerX + 1, playerY);
		break;

	case 'L':
	case 'l':
		showLevelLegend();
		break;

	case 'H':
	case 'h':
		player.drinkPotion();
		break;
	/*case 'E':
	case 'e':
		cout << "Do you want to exit? (Y/N): ";
		intput = _getch();
		if (intput = 'Y' || 'y') exit(0);
		break;*/

	default:
		cout << "ERROR: Invalid input\n";
		system("PAUSE");
		break;
	}
}

//Enemy turn!
void Level::moveEnemy(Player &player) {
	char aimove;
	int playerX, playerY,enemyX,enemyY;
	player.getPosition(playerX, playerY);

	
		for (int i = 0; i < (int)_enemies.size(); i++) {
			if (_enemies[i].isAlive() == true ) {
				_enemies[i].getPosition(enemyX, enemyY);
			aimove = _enemies[i].getMove(playerX, playerY);

			switch (aimove) {
			case'w':
				processEnemyMove(player, i, enemyX, enemyY - 1);
					break;

			case's':
				processEnemyMove(player, i, enemyX, enemyY + 1);
					break;

			case'a':
				processEnemyMove(player, i, enemyX - 1, enemyY);
					break;

			case'd':
				processEnemyMove(player, i, enemyX + 1, enemyY);
					break;
			default:
				break;

			}
		}
	}
}

char Level::getTile(int x, int y) {
	char tile = _levelData[y][x];
	return tile;
}

void Level::setTile(int x, int y, char Tile) {
	_levelData[y][x] = Tile;
}

//Additional tiles here!!!
void Level::tileEffect(Player &player, int targetX, int targetY) {
	int playerX, playerY;
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, '@');
		break;

		//Sciany
	case 'T':
		temple::talk(player);
		if (temple::ifRegenAvalible() == false) {
			setTile(targetX, targetY, '.');
		}
		break;
	case 'M':
		merchant::talk(player,_enemies);
		break;
	case '#':
		break;
	case '-':
		break;
	case '|':
		break;
	default:
		processBattle(player, targetX, targetY);
		break;
	}
}

void Level::processBattle(Player &player, int targetX, int targetY) {
	int enemyX, enemyY, attackRoll, attackResult, playerX, playerY;
	Reward killRew(0,0);
	player.getPosition(playerX, playerY);

	for (int i = 0; i < int(_enemies.size()); i++) {
		_enemies[i].getPosition(enemyX, enemyY);
		
	
		if (targetX == enemyX && targetY == enemyY) {

		//Player
			attackRoll = player.attack();
			cout << "\nPlayer attacked with a roll of  " << attackRoll<<endl;
			if (_enemies[i].dodge() == false) {
				killRew = _enemies[i].takeDamage(attackRoll);
				if (killRew.getRewardExp() != 0) {
					printLevel(player);
					cout << "Enemy died!\n";
					numEnemies--;
					cout << "You earned " << killRew.getRewardExp() << " experience and " << killRew.getRewardGold() << " gold coins.\n";
					_getch();
					player.addExperience(killRew.getRewardExp());
					player.addGold(killRew.getRewardGold());
					setTile(targetX, targetY, '.');
					if (numEnemies == 0) {
						system("cls");
						cout << "Gratulations. You killed all enemies. You won!\n";
						isFinished = 1;
						_getch();
					}
					return;
				}
			}
			else cout << "Enemy dodged your attack.\n"; system("PAUSE");


		//Enemy
			attackRoll = _enemies[i].attack();
			cout <<endl<< _enemies[i].getName() << " attacked with a roll of  " << attackRoll << endl;
			if (player.dodge() == false) {
				attackResult = player.takeDamage(attackRoll);
				if (attackResult != 0) {
					printLevel(player);
					remove("save1.txt");
					remove("save2.txt");
					setTile(playerX, playerY, '.');
					printLevel(player);
					cout << "You are dead. . .\n";
					remove("save1.txt");
					remove("save2.txt");
					system("PAUSE");

					isFinished = 1;
					return;
				}
			}
			else cout << "You dodged enemy attack.\n";
			system("PAUSE");
			return;
		}
	}
}

void Level::saveLevel(Player &player) {
	remove("save1.txt");
	remove("save2.txt");

	fstream file;

	file.open("save1.txt", ios::out);
	for (int i = 0; i < int(_levelData.size()); i++) {
		file << _levelData[i] << endl;
	}
	file.close();


	file.open("save2.txt", ios::out);
	file << player.getSaveData();

	for (int i = 0; i < _npc.size(); i++) {
		if (_npc[i].getTile() == 'M') {
			file<<merchant::save();
			break;
		}
	}

	for (int i = 0; i < (int)_enemies.size(); i++) {
		file<<_enemies[i].getSaveData();
	}

	file.close();

}

/*
void Level::loadSavedData(string fileName, Player &player) {
	loadLevel(fileName, player);
	fstream file;
	file.open("save2.txt",ios::in);
	string line;
	getline(file, line);
	replace(line.begin(), line.end(), ';', ' ');
	stringstream str(line);
	int buffor[9];
	for (int i = 0; i < 9; i++)
		str >> buffor[i];
	player.initializePlayer(buffor[2], buffor[3], buffor[4], buffor[6], buffor[7], buffor[5]);
	player.addGold(buffor[8]);
}
*/

void Level::loadSavedData(string fileName, Player &player) {
	//Get map
	fstream file;
	file.open(fileName);
	if (file.fail()) { cout << "ERROR: Could not load level.\n"; system("PAUSE"); exit(1); }

	string line;
	while (getline(file, line)) {
		_levelData.push_back(line);
	}
	file.close();

	//Get player
	file.open("save2.txt", ios::in);
	getline(file, line);
	replace(line.begin(), line.end(), ';', ' ');
	stringstream str(line);
	int buffor[11];
	for (int i = 0; i < 11; i++)
		str >> buffor[i];
	player.setPosition(buffor[0], buffor[1]);
	player.initializePlayer(buffor[2], buffor[3], buffor[4], buffor[6], buffor[7], buffor[5], buffor[10]);
	player.addGold(buffor[8]);
	player.addPotion(buffor[9]);

	//Get merchant
	getline(file, line);
	replace(line.begin(), line.end(), ';', ' ');
	stringstream str2(line);
	for (int i = 0; i < 6; i++)
		str2>>buffor[i];
	_npc.push_back(merchant(buffor[0],buffor[1],buffor[2],buffor[3],buffor[4],buffor[5]));

	string name;
	char tile;
	//Get enemies
	while (getline(file, line)) {

		replace(line.begin(), line.end(), ' ', '_');
		replace(line.begin(), line.end(), ';', ' ');
		stringstream str(line);
		str >> buffor[0] >> buffor[1] >> buffor[2] >> buffor[3] >> buffor[4] >> buffor[5] >> name >> tile >> buffor[6] >> buffor[7];
		_enemies.push_back(Enemy(buffor[0], buffor[1], name, tile, buffor[2], buffor[3], buffor[4], buffor[5], buffor[7], buffor[6]));
	}
	numEnemies = 0;
	for (int i = 0; i < (int)_enemies.size(); i++) {
		if (_enemies[i].isAlive() == true) numEnemies++;

		string temp = _enemies[i].getName();
		replace(temp.begin(), temp.end(), '_', ' ');
		_enemies[i].setName(temp);
	}
	//Temple
	for (int i = 0; i < (int)(_levelData.size()); i++) {
		for (int j = 0; j < int(_levelData[i].size()); j++) {
			char actualTile=_levelData[i][j];
			if (actualTile == 'T') {
				_npc.push_back(temple(j, i));
			}
		}
	}
}
void Level::showLevelLegend() {
	system("cls");

	cout << "Friendly:\n";
	cout << "@ - it's you\n";
	cout << "M - merchant\n";
	cout << "T - temple\n\n";

	cout << "Enemies:\n";
	cout << "R - Rat\n";
	cout << "V - Villager\n";
	cout << "D - Dog\n";
	cout << "G - Guard\n";
	cout << "E - Elite Guard\n";
	cout << "Q - Queen\n";
	cout << "K - King\n\n";

	cout << "Walls: # | -\n";



	_getch();
}

void Level::processEnemyMove(Player &player, int index, int targetX, int targetY) {
	int playerX, playerY, enemyX, enemyY;
	player.getPosition(playerX, playerY);
	_enemies[index].getPosition(enemyX, enemyY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		_enemies[index].setPosition(targetX, targetY);
		setTile(enemyX,enemyY, '.');
		setTile(targetX, targetY, _enemies[index].getTile());
		break;

	case '@':
		system("cls");
		printLevel(player);
		cout << "You are beeing attacked!!!\n";
		processBattle(player, enemyX, enemyY);
		break;

	default:
		break;
	}
}