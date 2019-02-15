#include "Bullet.h"


Bullet::Bullet(int X, int Y, Mob* Target, int DMG, int DurTime, BULLETTYPE Type) :Object(X, Y)
{
	_target = Target;
	_dmg = DMG;
	_tclock = 0;
	_durTime = DurTime;
	_type = Type;
}


Bullet::~Bullet()
{
}

//返回是否需要销毁
bool Bullet::Work()
{
	_tclock++;
	if (_tclock < _durTime){
		_x = (_x + _target->_x) / 2;
		_y = (_y + _target->_y) / 2;
		return false;
	}
	else{
		_target->TakeDMG(_dmg);
		return true;
	}
}
