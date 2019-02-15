#pragma once
#include "tower.h"

class Elec :
	public Tower
{
public:
	Elec(int,int);
	~Elec(void);
	int _bulletNum;
	void Draw();
	void Attack(vector<Mob*> &vec);
};
