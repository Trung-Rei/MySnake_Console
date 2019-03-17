#include "Snake.h"
#include <fstream>
#include "CursorControl.h"
#include <iostream>

namespace Snake
{
	int Char, Color;
	const int MaxLength = 10000;
	COO Snake[MaxLength];
	bool SnakeMap[40][40];
	int HeadIndex;
	int TailIndex;
	COO SnakeTail;
	COO Dir;
	bool Death;
	//
	void LoadSkin()
	{
		std::ifstream Input("SelectedSkin_Snake.dat");
		Input >> Char;
		Input >> Color;
		Input.close();
	}
	void SetDir(COO Direction)
	{
		if (Dir.X == -Direction.X && Dir.Y == -Direction.Y) return;
		Dir = Direction;
	}
	bool isDead()
	{
		return Death;
	}
	void Die()
	{
		Death = true;
	}
	void Init(int X, int Y)
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++) SnakeMap[i][j] = false;
		Snake[0] = { X, Y };
		SnakeMap[X][Y] = true;
		HeadIndex = 0;
		TailIndex = 0;
		SnakeTail = { X,Y + 1 };
		SetDir({ 0,-1 });
		Death = false;
		LoadSkin();
		Draw();
	}
	void Move()
	{
		SnakeTail = Snake[TailIndex];
		SnakeMap[Snake[TailIndex].X][Snake[TailIndex].Y] = false;
		TailIndex = (TailIndex + 1) % MaxLength;
		Snake[(HeadIndex + 1) % MaxLength].X = Snake[HeadIndex].X + Dir.X;
		Snake[(HeadIndex + 1) % MaxLength].Y = Snake[HeadIndex].Y + Dir.Y;
		HeadIndex = (HeadIndex + 1) % MaxLength;
		SnakeMap[Snake[HeadIndex].X][Snake[HeadIndex].Y] = true;
	}
	void Draw()
	{
		gotoXY(SnakeTail);
		std::cout << (char)32;
		gotoXY(Snake[HeadIndex]);
		SetColor(Color);
		std::cout << (char)Char;
	}
	void Grow()
	{
		Snake[(HeadIndex + 1) % MaxLength].X = Snake[HeadIndex].X + Dir.X;
		Snake[(HeadIndex + 1) % MaxLength].Y = Snake[HeadIndex].Y + Dir.Y;
		HeadIndex = (HeadIndex + 1) % MaxLength;
		SnakeMap[Snake[HeadIndex].X][Snake[HeadIndex].Y] = true;
	}
	COO GetAhead()
	{
		return { Snake[HeadIndex].X + Dir.X, Snake[HeadIndex].Y + Dir.Y };
	}
	bool Inside(COO Posi)
	{
		return SnakeMap[Posi.X][Posi.Y];
	}
}