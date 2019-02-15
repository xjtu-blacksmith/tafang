#pragma once
#include "Tower.h"

class Rocket :
	public Tower
{
public:
	Rocket(int,int);
	~Rocket(void);
	int _bulletNum;
	void Draw();
	void Attack(vector<Mob*> &vec);
};
