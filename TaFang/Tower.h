#pragma once
#include "Object.h"
#include "Mob.h"
#include <vector>
#include "Aura.h"

using namespace std;

typedef enum _TOWER_TYPE_ {LASER,LINE,ROCKET,ELEC,FIRE,ICE} TOWERTYPE;

class Tower :
	public Object
{
public:
	TOWERTYPE _type;
	int _aclock;
	int _attackclock;
	int _maxattackclock;
	int _range;

	int SquaredDist(Object* obj2);

	Tower(int row, int col, int range, int MaxAttackClock, TOWERTYPE Type);
	~Tower();

	//返回是否发动攻击
	bool TryAttack(Mob* mob);
	virtual void Attack(vector<Mob*> &vec)=0;
};

