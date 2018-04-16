#pragma once
#include "Enemy.h"




class Rat : public Enemy{
public:
	string namesRat[5] = { "Remy the Rat", "Ratty", "Splinter", "Squeakers","Wormtail" };
	Rat(int X, int Y):Enemy(X,Y,namesRat[rand()%5],'R',10,3,1,20,20,6){

	};
	~Rat() {};
};

