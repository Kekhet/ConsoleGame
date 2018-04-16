#include "temple.h"
bool temple::regen = false;

temple::temple(int x, int y):townNpc(x,y)
{

	setTile('T');
}


temple::~temple()
{
}

void temple::talk(Player &player) {
	system("cls");
	cout << "\n***You see a poor monk in front of you. As you approach, he raises his head and you can see something disturbing in his eyes***.\n ";
	cout << "Welcome stranger. I am honored to greet you in our temple steps. \nBecause of your 'Patrons' i can offer you food and place to sleep for as long as you won't violate our temple rules.\n\n";

	cout << "I will also offer you healing. Our powerfull potions and rituals can bring you back from brink of the death but every person can use it only once so better don't use it on some bruises and rash.\n\n";
	cout << "Do you want to perform ritual now? (Y/N)\n";
	char intput = _getch();
	if (intput == 'Y' || intput == 'y') {
		player.resetHealth();
		regen = true;
	
	}
}