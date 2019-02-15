#include "Tower.h"


Tower::Tower(int row, int col, int range, int MaxAttackClock, TOWERTYPE Type) :Object(col*GRIDSIZE,row*GRIDSIZE)
{
	_row = row;
	_column = col;
	_range = range;
	_aclock = 0;
	_maxattackclock = MaxAttackClock;
	_attackclock = _maxattackclock;
	_type = Type;
}


Tower::~Tower()
{
}

//返回是否发动攻击
bool Tower::TryAttack(Mob* pMobVec){
		if (SquaredDist(pMobVec)<_range*_range && _aclock>=_attackclock){
			_aclock = 0;
			return true;
		}
	return false;
}

int Tower::SquaredDist(Object* obj2)
{
	return (_x+GRIDSIZE/2 - obj2->_x) * (_x+GRIDSIZE/2 - obj2->_x) + (_y+GRIDSIZE/2 - obj2->_y) * (_y+GRIDSIZE/2 - obj2->_y);
}