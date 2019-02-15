#include "Healer.h"

int Healer::_healdur = 185;

Healer::Healer(int X, int Y) :Mob(X, Y, 240, 4, HEALER, false, 50)
{
	_healclock = 0;
}

Healer::~Healer(void)
{
}

void Healer::Draw()
{
	setlinecolor(RGB(140, 0, 0));
	setfillcolor(RED);
	fillcircle(_x,_y,GRIDSIZE/5);
	setlinecolor(RGB(247,235,9));
	setlinestyle(PS_SOLID, 3);
	line(_x-6,_y,_x+6,_y);
	line(_x, _y-6, _x, _y+6);
	setlinestyle(PS_SOLID, 1);
}

void Healer::TryHeal(vector<Aura*> &aura)
{
	_healclock++;
	if (_healclock >= _healdur){
		aura.push_back(new HealAura(_x, _y, 28));
		_healclock = 0;
	}
}