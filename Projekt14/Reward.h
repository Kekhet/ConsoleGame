#pragma once
class Reward
{
	int _experience;
	int _gold;
public:
	Reward(int E, int G);
	Reward();
	void setReward(int E, int G);
	int getRewardExp();
	int getRewardGold();
};

