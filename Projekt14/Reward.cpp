#include "Reward.h"



Reward::Reward(int E, int G){
	_experience = E;
	_gold = G;
}


Reward::Reward()
{
}

void Reward::setReward(int E, int G) {
	_experience = E;
	_gold = G;
}

int Reward::getRewardExp() {
	return _experience;
}
int Reward::getRewardGold() {
	return _gold;
}