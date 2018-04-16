#pragma once
#include <string> 

using namespace std;

class Player
{
	friend class merchant;
	//Coordinates
	int _x, _y;

	//Statistics
	int _maxHealth;
	int _Health;
	int _Attack;
	int _Defence;
	int _Level;
	int _Experience;
	int _Dodge;

	//Inventory
	int _Gold;
	int _healthPotions;

public:

	Player();
	~Player();

	//Player basic properies initializer
	void initializePlayer(int health, int attack, int defence, int level, int experience, int dodge, int maxHealth);
	string getSaveData();

	//Setters
	void setPosition(int x, int y);


	//Getters
	void getPosition(int &x, int &y);
	int getHealth() { return _Health; }
	int getLevel() { return _Level; }
	int getExperience() { return _Experience; }
	int getGold() { return _Gold; }

	int attack();
	bool dodge();

	void addExperience(int expVal);
	void addGold(int goldVal);

	int takeDamage(int dmgTaken);

	friend ostream& operator<<(ostream& str, const Player _player);

	void drinkPotion();
	void addPotion(int x) { _healthPotions+=x; }
	void resetHealth() { _Health = _maxHealth; }
};

