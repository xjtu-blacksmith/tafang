#include "GiantBee.h"


GiantBee::GiantBee(int X, int Y) :Mob(X, Y, 270, 4, GIANTBEE, true, 20)
{
}


GiantBee::~GiantBee()
{
}


void GiantBee::Draw()
{
	setfillcolor(YELLOW);
	setlinecolor(WHITE);
	line(_x, _y, _x - 11, _y - 5);
	line(_x - 8, _y - 7, _x - 11, _y - 5);
	line(_x, _y, _x - 8, _y - 7);
	line(_x, _y, _x + 11, _y - 5);
	line(_x + 8, _y - 7, _x + 11, _y - 5);
	line(_x, _y, _x + 8, _y - 7);
	fillcircle(_x, _y, 6);
	// »­ÑªÌõ
	setlinecolor(RGB(255-int(255.0*_hp/_maxhp),int(255.0*_hp/_maxhp),0));
	line(_x-9,_y-14,_x-9+int(18.0*_hp/_maxhp),_y-14);
}
