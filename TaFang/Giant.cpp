#include "Giant.h"


Giant::Giant(int X,int Y) :Mob(X, Y, 450, 6, GIANT, false,20)
{
}


Giant::~Giant()
{
}


void Giant::Draw()
{
	setlinecolor(RGB(140, 0, 0));
	setfillcolor(RGB(240,20,0));
	fillcircle(_x, _y, GRIDSIZE / 3);
	// »­ÑªÌõ
	setlinecolor(RGB(255-int(255.0*_hp/_maxhp),int(255.0*_hp/_maxhp),0));
	line(_x-9,_y-10,_x-9+int(18.0*_hp/_maxhp),_y-10);
}
