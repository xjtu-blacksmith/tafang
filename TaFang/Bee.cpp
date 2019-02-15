#include "Bee.h"


Bee::Bee(int X,int Y) :Mob(X, Y, 120, 3, BEE, true, 10)
{
}


Bee::~Bee()
{
}


void Bee::Draw()
{
	setfillcolor(YELLOW);
	setlinecolor(WHITE);
	line(_x, _y, _x - 9,_y - 3);
	line(_x - 7, _y - 6, _x - 9, _y - 3);
	line(_x, _y, _x - 7, _y - 6);
	line(_x, _y, _x + 9, _y - 3);
	line(_x + 7, _y - 6, _x + 9, _y - 3);
	line(_x, _y, _x + 7, _y - 6);
	fillcircle(_x,_y,4);
	// »­ÑªÌõ
	setlinecolor(RGB(255-int(255.0*_hp/_maxhp),int(255.0*_hp/_maxhp),0));
	line(_x-9,_y-10,_x-9+int(18.0*_hp/_maxhp),_y-10);
}
