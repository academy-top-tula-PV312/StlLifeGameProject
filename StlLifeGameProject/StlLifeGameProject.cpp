#include <iostream>
#include "LifeGameViewConsole.h"

int main()
{
	LifeGameViewConsole game;

	if (game.Setup())
		game.Play();
}
