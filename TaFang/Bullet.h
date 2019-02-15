#pragma once
#include "Object.h"
#include "Mob.h"

typedef enum _BULLET_TYPE_ {PEA} BULLETTYPE;

class Bullet :
	public Object
{

public:
	int _tclock;
	int _durTime;
	int _dmg;
	Mob* _target;
	BULLETTYPE _type;

	Bullet(int X, int Y, Mob* Target, int DMG, int DurTime, BULLETTYPE Type);
	~Bullet();

	//返回是否需要销毁
	bool Work();
};

