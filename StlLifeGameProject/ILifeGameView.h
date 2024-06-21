#pragma once
#include "LifeGame.h"

class ILifeGameView
{
protected:
	LifeGame* lifeGame;
	int speed;

public:
	ILifeGameView()
		: lifeGame{ new LifeGame() } {}

	int& Speed() { return speed; }

	virtual bool Setup() = 0;
	virtual void Paly() = 0;
};

