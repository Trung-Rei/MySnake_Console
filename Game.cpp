#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <conio.h>
#include <chrono>

const char KEY_UP = 72;
const char KEY_DOWN = 80;
const char KEY_LEFT = 75;
const char KEY_RIGHT = 77;

float Space, Speed;
std::chrono::time_point<std::chrono::system_clock> PreTime, NextTime;
bool Moved, Grew, GOver, KeyPermission;


void Setup()
{
	PreTime = std::chrono::system_clock::now();
	Space = 0.0;
	Speed = 10.0;
	GOver = false;
	KeyPermission = true;
	Snake::Init(20, 20);
	Food::Init();
	Snake::Draw();
	Food::Draw();
}

void Input()
{
	if (!KeyPermission) return;
	if (_kbhit())
	{
		char Key = _getch();
		//if (!KeyPermission) return;
		switch (Key)
		{
		case KEY_UP:
			Snake::SetDir({ 0,-1 });
			KeyPermission = false;
			break;
		case KEY_DOWN:
			Snake::SetDir({ 0,1 });
			KeyPermission = false;
			break;
		case KEY_LEFT:
			Snake::SetDir({ -1,0 });
			KeyPermission = false;
			break;
		case KEY_RIGHT:
			Snake::SetDir({ 1,0 });
			KeyPermission = false;
			break;
		}
	}
}

void Logic()
{
	NextTime = std::chrono::system_clock::now();
	std::chrono::duration<float> ElapsedTime_Temp = NextTime - PreTime;
	float ElapsedTime = ElapsedTime_Temp.count();
	PreTime = NextTime;
	Space += Speed * ElapsedTime;
	if ((int)Space == 1)
	{
		if ((Snake::GetAhead().X < 0) || (Snake::GetAhead().X >= 40) || (Snake::GetAhead().Y < 0) || (Snake::GetAhead().Y >= 40))
		{
			Snake::Die();
			return;
		}
		else
			if (Snake::Inside(Snake::GetAhead()))
			{
				Snake::Die();
				return;
			}
		if (Snake::GetAhead().X == Food::GetPosition().X && Snake::GetAhead().Y == Food::GetPosition().Y)
		{
			Grew = true;
			Space -= (float)1;
			KeyPermission = true;
			return;
		}
		Moved = true;
		Space -= (float)1;
		KeyPermission = true;
	}
	else
	{
		Moved = false;
		Grew = false;
	}
}

void Update()
{
	if (Snake::isDead())
	{
		GOver = true;
		return;
	}
	if (Moved)
	{
		Snake::Move();
	}
	if (Grew)
	{
		Snake::Grow();
		Food::New();
	}
}

void Draw()
{
	if (GOver) return;
	if (Moved) Snake::Draw();
	if (Grew)
	{
		Snake::Draw();
		Food::Draw();
	}
}

bool Gameover()
{
	return GOver;
}