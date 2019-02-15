#pragma once
#include "tower.h"
#include <vector>

using namespace std;

class LaserTower :
	public Tower
{
public:
	LaserTower(int row,int col);
	~LaserTower(void);
	void Draw();
	void Attack(vector<Mob*> &vec);
};
