#include "gameSystem.h"


gameSystem::gameSystem(string levelFileName){
	_player.initializePlayer(100, 10, 5, 1, 0, 5, 100);
	_level.loadLevel(levelFileName, _player);


}
gameSystem::~gameSystem() {}

gameSystem::gameSystem(string levelFileName, int &LOADER) {
	_level.loadSavedData(levelFileName, _player);
}
	
void gameSystem::playGame() {
//	isDone = false;
	while (isDone != true) {
		_level.printLevel(_player);
		//cout << numEnemies << endl;
		getPlayerMove();
		if (Level::isFinished == 1) { isDone = true; return; }
		getEnemyMove();

		
	}
}

void gameSystem::getPlayerMove() {
	char intput;
	cout << "Enter move command (W/S/A/D), drink health potion (H), show legend (L) or save and exit program (Esc): ";
	intput = _getch();
	
	_level.movePlayer(intput, _player);
}

void gameSystem::getEnemyMove() {
	_level.moveEnemy(_player);
}