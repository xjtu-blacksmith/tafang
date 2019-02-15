#pragma once
#include "Tower.h"
#include"IceAura.h"
class IceTower :
	public Tower
{
private:
	POINT p[6];
public:
	IceTower(int row, int col);
	~IceTower();

	void Draw();
	void Attack(vector<Mob*> &vec, vector<Aura*> &aura);
};

