#include "Runner.h"


Runner::Runner(int X, int Y) :Mob(X, Y, 100, 2, RUNNER, false, 5)
{
	_p[0].x = _x;
	_p[0].y = _y-3;
	_p[1].x = _x - 2;
	_p[1].y = _y + 1;
	_p[2].x = _x + 2;
	_p[2].y = _y + 1;
}


Runner::~Runner()
{
}


void Runner::Draw()
{
	setlinecolor(RGB(255,70,0));
	setfillcolor(RED);
	_p[0].x = _x;
	_p[0].y = _y - 3;
	_p[1].x = _x - 2;
	_p[1].y = _y + 1;
	_p[2].x = _x + 2;
	_p[2].y = _y + 1;
	fillpolygon(_p,3);
	// »­ÑªÌõ
	setlinecolor(RGB(255-int(255.0*_hp/_maxhp),int(255.0*_hp/_maxhp),0));
	line(_x-9,_y-6,_x-9+int(18.0*_hp/_maxhp),_y-6);
}
