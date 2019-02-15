#pragma once
#include "mob.h"

class Zombie :
	public Mob
{
public:
	Zombie(int X,int Y);
	~Zombie(void);
	void Draw();
};
