#include "Game.h"

int main()
{
	Setup();
	while (!Gameover())
	{
		Input();
		Logic();
		Update();
		Draw();
	}
	return 0;
}