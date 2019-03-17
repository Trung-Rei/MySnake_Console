#include "Food.h"
#include <fstream>
#include "Snake.h"
#include "CursorControl.h"
#include <iostream>

namespace Food
{
	COO Position;
	int Char, Color;
	void LoadSkin()
	{
		std::ifstream Input("SelectedSkin_Food.dat");
		Input >> Char;
		Input >> Color;
		Input.close();
	}
	void Init()
	{
		New();
		LoadSkin();
		Draw();
	}
	void New()
	{
		do
		{
			Position.X = rand() % 40;
			Position.Y = rand() % 40;
		} while (Snake::Inside(Position));
	}
	void Draw()
	{
		gotoXY(Position);
		SetColor(Color);
		std::cout << (char) Char;
	}
	COO GetPosition()
	{
		return Position;
	}
}