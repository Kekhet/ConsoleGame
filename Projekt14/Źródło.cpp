#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include "gameSystem.h"


using namespace std;

void setUpNewGame();
void setUpLoadedGame();
void showLegend();


int main() {
	while (true) {
		system("cls");

		cout << "Truthless RogueLike by Jakub Wenda\n\n";
		cout << "Menu:\n";
		cout << "1. New game\n";
		cout << "2. Load game\n";
		cout << "3. Legend\n";
		cout << "4. Exit\n";
		cout << endl;

		fstream file;


		char intput=_getch();
		switch (intput) {
		case '1':
			setUpNewGame();
			break;
		case '2':
			file.open("save1.txt");
			if (Level::getDeadStatus()==true){
				cout << "\nNo saved data.\n";
				_getch();
				break;
			}
			setUpLoadedGame();
			break;
		case '3':
			showLegend();
			break;
		case '4':
			exit(0);
		default:
			break;
		}
	}
}

void setUpNewGame() {
	string lvlTab[2] = { "level1.txt", "level2.txt" };
	default_random_engine randomG((int)time(NULL));
	uniform_int_distribution<int> rollLevel(0, 1);
	gameSystem Roguelike(lvlTab[rollLevel(randomG)]);
	Roguelike.setDone(0);
	Roguelike.playGame();
}


void setUpLoadedGame() {

	static int loader = 0;
	gameSystem RoguelikeLoaded("save1.txt", loader);
	remove("save1.txt");
	remove("save2.txt");
	loader++;
	RoguelikeLoaded.playGame();
}

void showLegend() {
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