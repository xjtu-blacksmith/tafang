#pragma once
#include "tower.h"

class LineTower :
	public Tower
{
public:
	LineTower(int row,int col);
	~LineTower(void);
	void Draw();
	void Attack(vector<Mob*> &vec);
};
