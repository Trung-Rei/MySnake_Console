#include "CursorControl.h"
#include <Windows.h>

void gotoXY(COO Coord)
{
	static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { Coord.X,Coord.Y };
	SetConsoleCursorPosition(out, coord);
}

void SetColor(int Value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Value);
}