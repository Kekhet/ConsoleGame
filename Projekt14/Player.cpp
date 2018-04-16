#include "Player.h"
#include <random>
#include <ctime>
#include <iostream>



static default_random_engine randomG(time(NULL));

Player::Player(){
	_x = 0;
	_y = 0;
}

Player::~Player() {}


void Player::initializePlayer(int health, int attack, int defence, int level, int experience, int dodge, int maxhealth) {
	_Health = health;
	_maxHealth = maxhealth;
	_Attack = attack;
	_Defence = defence;
	_Level = level;
	_Experience = experience;
	_Dodge = dodge;
	_Gold = 0;
	_healthPotions = 0;
}

void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

int Player::attack() {
	uniform_int_distribution<int> attackRoll(0, _Attack);
	return attackRoll(randomG);
}

bool Player::dodge() {
	uniform_int_distribution<int> dodgeRoll(0, 100);
	if (dodgeRoll(randomG) <= _Dodge)return true;
	else return false;
}

void Player::addExperience(int expVal) {
	_Experience += expVal;
	while (_Experience > 50) {
		cout << "LEVEL UP! You grow stronger.\n";
		_Experience -= 50;
		_Attack += 5;
		_Defence += 2;
		_Level ++;
		_maxHealth += 10;
		_Health += 10;
		_Dodge += 3;
		system("PAUSE");
	}
}
int Player::takeDamage(int dmgTaken) {
	dmgTaken = dmgTaken - _Defence;
	if (dmgTaken > 0) {
		_Health = _Health - dmgTaken;
		if (_Health <= 0) {
			return 1;
		};
	}
	return 0;
}

void Player::addGold(int goldVal) {
	_Gold += goldVal;
}

string Player::getSaveData() {
	string buffer;

	string retVal = to_string(_x);
	retVal += ';';

	buffer = to_string(_y);
	retVal += buffer;
	retVal += ';';


	buffer = to_string(_Health);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_Attack);
	retVal += buffer;
	retVal += ';';
	
	buffer = to_string(_Defence);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_Dodge);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_Level);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_Experience);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_Gold);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_healthPotions);
	retVal += buffer;
	retVal += ';';

	buffer = to_string(_maxHealth);
	retVal += buffer;
	retVal += ';\n\n';

	return retVal;
}

void Player::drinkPotion() {
	_Health += 30;
	_healthPotions--;
	if (_Health > _maxHealth) _Health = _maxHealth;
}

ostream& operator<<(ostream& str, const Player _player) {
	str<< "Player Health: " << _player._Health << " Level: " << _player._Level << " Experience: " << _player._Experience << " Gold: " << _player._Gold<<" Health potions: "<<_player._healthPotions;
	return str;
}