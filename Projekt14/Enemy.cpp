#include "Enemy.h"

static default_random_engine randomG(time(NULL));


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(int X, int Y, string Name, char Tile, int Health, int Attack, int Defence, int Dodge, int expVal, int goldVal) {
	_Name = Name;
	_Tile = Tile;
	_x = X;
	_y = Y;
	_Health = Health;
	_Attack = Attack;
	_Defence = Defence;
	_Dodge = Dodge;
	killReward.setReward(expVal, goldVal);

}

void Enemy::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}
void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

int Enemy::attack() {
	uniform_int_distribution<int> attackRoll(0, _Attack);
	return attackRoll(randomG);
}

bool Enemy::dodge() {
	uniform_int_distribution<int> dodgeRoll(0, 100);
	if (dodgeRoll(randomG) <= _Dodge)return true;
	else return false;
}
Reward Enemy::takeDamage(int dmgTaken) {
	dmgTaken = dmgTaken - _Defence;
	if (dmgTaken > 0) {
		_Health = _Health - dmgTaken;
		if (_Health <= 0) return killReward;
	}
	return Reward(0,0);
}
string Enemy::getName() {
	return _Name;
}

string Enemy::getSaveData() {
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

	buffer = _Name;
	retVal += _Name;
	retVal += ';';

	retVal += _Tile;
	retVal += ';';

	buffer = to_string(killReward.getRewardGold());
	retVal += buffer;
	retVal += ';';

	buffer = to_string(killReward.getRewardExp());
	retVal += buffer;
	retVal += ';\n\n';

	return retVal;
}

char Enemy::getMove(int playerX, int playerY) {
	static default_random_engine randomG(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 12);

	int dX = playerX - _x;
	int dY= playerY - _y;
	int adX = abs(dX);
	int adY = abs(dY);
	int distance = adX + adY;

	if (distance <= 2) {
		//X axis
		if (adX > adY) {
			if (dX < 0) {
				return 'a';
			}
			else { return 'd'; }
		}
		//Y axis
		else {
			if (dY < 0) {
				return 'w';
			}
			else { return 's'; }

		}
	}
	int randomMove = moveRoll(randomG);
	switch (randomMove) {
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'a';
	case 4:
		return 'd';
	default:
		return '.';
	}
}