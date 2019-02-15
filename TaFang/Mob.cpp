#include "Mob.h"

float Mob::_MobHpMultiplier = 1;

Mob::Mob(int X, int Y, int MaxHP, int MaxMoveClock, MOBTYPE Type, bool Flying,int DropMoney) :Object(X,Y)
{
	_maxhp = (int)(MaxHP * Mob::_MobHpMultiplier);
	_hp = _maxhp;
	_mclock = 0;
	_maxmoveclock = MaxMoveClock;
	_moveclock = _maxmoveclock;
	_type = Type;
	_isflying = Flying;
	_dir = RIGHT;
	_dropmoney = DropMoney;
}


Mob::~Mob()
{
}



void Mob::Move()
{
	_mclock++;
	if (_mclock >= _moveclock){
		if(!_route.empty())
			if(!setTarget(_route.back()))
				_route.pop_back();
		_mclock = 0;
		switch (_dir)
		{
		case LEFT:
			MoveXY(-5, 0);
			break;
		case RIGHT:
			MoveXY(5, 0);
			break;
		case UP:
			MoveXY(0, -5);
			break;
		case DOWN:
			MoveXY(0, 5);
			break;
		}
		if(_moveclock>_maxmoveclock)
			_moveclock --;
	}
	
	
}

//void Mob::Draw(){
//	putimage(x, y, _img);
//	setfillcolor(RGB(255,0,0));
//	solidrectangle(x,y-2,_imgwidth,y);
//	setfillcolor(RGB(0, 255, 0));
//	solidrectangle(x, y - 2, _imgwidth * _hp / _maxhp, y);
//}

//∑µªÿ «∑ÒÀ¿¡À
bool Mob::TakeDMG(int DMG)
{
	if (_hp - DMG <= 0){
		return true;
	}
	else if (_hp - DMG >= _maxhp){
		_hp = _maxhp;
	}
	else{
		_hp -= DMG;
	}
	return false;
}


bool Mob::IsDead()
{
	if (_hp <= 0){
		return true;
	}
	return false;
}

bool Mob::setTarget(BASEPOINT point)
{
	if(point.row*GRIDSIZE>=_y)
		_dir = DOWN;
	else if(point.row*GRIDSIZE+GRIDSIZE<=_y)
		_dir=UP;
	else if(point.column*GRIDSIZE>=_x)
		_dir=RIGHT;
	else if(point.column*GRIDSIZE+GRIDSIZE<=_x)
		_dir=LEFT;
	else
		return false;
	return true;
}

void Mob::showRoute()
{
	setfillcolor(BLUE);
	for(int i=0;i<_route.size();i++)
		fillrectangle(_route[i].column*GRIDSIZE,_route[i].row*GRIDSIZE,
		(_route[i].column+1)*GRIDSIZE,(_route[i].row+1)*GRIDSIZE);
}