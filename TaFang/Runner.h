#pragma once
#include "Mob.h"
class Runner :
	public Mob
{
public:
	POINT _p[3];
	Runner(int X, int Y);
	~Runner();
	void Draw();
};

