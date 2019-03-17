#pragma once

#include "COO.h"

namespace Snake
{
	void SetDir(COO Direction);
	void Init(int X, int Y);
	void Move();
	void Grow();
	void Draw();
	bool isDead();
	void Die();
	COO GetAhead();
	bool Inside(COO Posi);
}