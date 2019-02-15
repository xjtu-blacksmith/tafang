#pragma once
#include "Object.h"
#include <vector>

using namespace std;

typedef enum _MOB_TYPE_ { ZOMBIE, GIANT, RUNNER, BEE, GIANTBEE,HEALER } MOBTYPE;
typedef enum _DIRECTION_ { LEFT,RIGHT,UP,DOWN } DIRECTION;

class Mob :
	public Object
{
protected:
	//IMAGE* _img;
	//int _imgwidth;

public:
	MOBTYPE _type;
	int _maxhp;
	int _hp;
	int _mclock;
	int _moveclock;
	int _maxmoveclock;
	int _dropmoney;
	static float _MobHpMultiplier;

	vector<BASEPOINT> _route;

	DIRECTION _dir;

	bool _isflying;

	Mob(int X,int Y,int MaxHP,int MaxMoveClock,MOBTYPE Type, bool Flying,int DropMoney);
	~Mob();
	void Move();
	bool setTarget(BASEPOINT point);

	//虚函数
	virtual void Draw()=0;
	//返回是否死了
	bool TakeDMG(int DMG);
	bool IsDead();

	void showRoute();
};

