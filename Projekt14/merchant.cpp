#include "merchant.h"

bool merchant::ratsKilled = false;
bool merchant::isBought[4] = { 0,0,0,0 };

merchant::merchant(int x, int y) :townNpc(x, y)
{
	setTile('M');
}
merchant::merchant(int x, int y, int b0, int b1, int b2, int b3) : townNpc(x, y) {
	setTile('M');
	isBought[0] = b0;
	isBought[1] = b1;
	isBought[2] = b2;
	isBought[3] = b3;
}

merchant::~merchant()
{
}

void merchant::talk(Player &player, vector <Enemy> _enemies) {
	cout << "\n***In his dusty old shop sits local merchant.***\n\n";
	
	bool ratsFound = false;
	for (int i = 0; i < _enemies.size(); i++) {
		if (_enemies[i].getTile() == 'R' && _enemies[i].isAlive()==true) ratsFound = true;
	}

		if (ratsFound == true) {
			cout << "\nWhat do you want stranger? Are you lost? I won't trade with you until you do something for me. Kill these filthy rats hiding in back of my shop. This damned creatures won't leave my supplies be.\n\n";
			system("PAUSE");
		}
		else {
			cout << "\nWelcome to my shop. Unfortunately i don't have much to offer but feel free to browse if you want.\n";
			system("PAUSE");
			shop(player);
		}
	}

	void merchant::shop(Player &player) {
		system("cls");
		cout << "I can offer you:                                                  (Type X ty exit shop)\n";
		if (isBought[0] == false) cout << "Better sword to boost your attack. (150G    type S)\n";
		if (isBought[1] == false) cout << "Steel gauntlet to block your enemies attacks. (150G    type G)\n";
		if (isBought[2] == false) cout << "Soft leather boots for better dodge chance. (150G    type B)\n";
		if (isBought[3] == false) cout << "Dose of exotic potion to boost your body resistance. (150G    type P)\n";
		cout << "Health potions. Typical. (50G    type H)\n\n";
		cout << "Your gold: " << player._Gold << endl;


		char intput = _getch();
		int bigItemPrize = 150;
		switch (intput) {

		case 'S':
		case 's':
			if (player.getGold() <bigItemPrize) {
				cout << "\nYou want to fool me? You don't have money!\n\n";
				system("PAUSE");
			}
			else {
				cout << "You raised your attack.\n";
				player._Attack += 10;
				player._Gold -= bigItemPrize;
				isBought[0] = 1;
				system("PAUSE");
			}
			break;

		case 'G':
		case 'g':
			if (player.getGold() < bigItemPrize) {
				cout << "\nYou want to fool me? You don't have money!\n\n";
				system("PAUSE");
			}
			else {
				cout << "You raised your defence.\n";
				player._Defence += 5;
				player._Gold -= bigItemPrize;
				isBought[1] = 1;
				system("PAUSE");
			}
			break;

		case 'B':
		case 'b':
			if (player.getGold() < bigItemPrize) {
				cout << "\nYou want to fool me? You don't have money!\n\n";
				system("PAUSE");
			}
			else {
				cout << "You raised your dodge rate.\n";
				player._Dodge += 7;
				player._Gold -= bigItemPrize;
				isBought[2] = 1;
				system("PAUSE");
			}
			break;

		case 'P':
		case 'p':
			if (player.getGold() < bigItemPrize) {
				cout << "\nYou want to fool me? You don't have money!\n\n";
				system("PAUSE");
			}
			else {
				cout << "You raised your maximum health.\n";
				player._Health += 10;
				player._maxHealth += 10;
				player._Gold -= bigItemPrize;
				isBought[3] = 1;
				system("PAUSE");
			}
			break;

		case 'H':
		case 'h':
			if (player.getGold() < 50) {
				cout << "\nYou want to fool me? You don't have money!\n\n";
				system("PAUSE");
			}
			else {
				cout << "You bought health potion.\n";
				player._healthPotions ++;
				player._Gold -= 50;
				system("PAUSE");
			}
			break;

		default:
			break;
		}

	}

