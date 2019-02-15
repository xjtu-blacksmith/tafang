#include "Zombie.h"

Zombie::Zombie(int X,int Y):Mob(X,Y,150,3,ZOMBIE,false,10)
{
}

Zombie::~Zombie(void)
{
}

void Zombie::Draw()
{
	setlinecolor(RGB(140, 0, 0));
	setfillcolor(RED);
	fillcircle(_x,_y,GRIDSIZE/5);
	// »­ÑªÌõ
	setlinecolor(RGB(255-int(255.0*_hp/_maxhp),int(255.0*_hp/_maxhp),0));
	line(_x-9,_y-10,_x-9+int(18.0*_hp/_maxhp),_y-10);
}