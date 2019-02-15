#include "Aura.h"


Aura::Aura(int X, int Y, int range, int durTime, AURATYPE type) :Object(X,Y)
{
	_range = range;
	_tclock = 0;
	_durTime = durTime;
	_type = type;
}


Aura::~Aura()
{
}


// 返回是否需要销毁
bool Aura::Work(vector<Mob*> &vec)
{
	_tclock++;
	if (_tclock > _durTime){
		return true;
	}
	this->WorkFunction(vec);
	return false;
}
