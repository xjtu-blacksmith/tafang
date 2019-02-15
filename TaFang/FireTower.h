#pragma once
#include "Tower.h"
#include"FireAura.h"
class FireTower :
	public Tower
{
private:
	POINT p[3];
public:
	FireTower(int row, int col);
	~FireTower();

	void Draw();
	void Attack(vector<Mob*> &vec, vector<Aura*> &aura);
};

