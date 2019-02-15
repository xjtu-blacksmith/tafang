#pragma once
#include "Mob.h"
class Giant :
	public Mob
{
public:
	Giant(int X,int Y);
	~Giant();
	void Draw();
};

