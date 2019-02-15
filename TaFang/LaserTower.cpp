#include "LaserTower.h"
#include <vector>

using namespace std;

LaserTower::LaserTower(int row,int col):Tower(row,col,80,30,LASER)
{
}

LaserTower::~LaserTower(void)
{
}

void LaserTower::Draw()
{
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID, 2);
	rectangle(_column*GRIDSIZE+2,_row*GRIDSIZE+2,(_column+1)*GRIDSIZE-1,(_row+1)*GRIDSIZE-1);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(RGB(255,255,0));
	line(_column*GRIDSIZE,_row*GRIDSIZE+GRIDSIZE/2,
		(_column+1)*GRIDSIZE,_row*GRIDSIZE+GRIDSIZE/2);
	line(_column*GRIDSIZE+GRIDSIZE/2,_row*GRIDSIZE,
		_column*GRIDSIZE+GRIDSIZE/2,(_row+1)*GRIDSIZE);
}

void LaserTower::Attack(vector<Mob*> &vec)
{
	_aclock++;
	if (_aclock>_attackclock &&!vec.empty()){
		int mindis2 = 10000 * 10000, minnum = -1;
		for (int j = 0; j < vec.size(); j++){
			int dis2 = SquaredDist(vec[j]);
			if (mindis2>dis2){
				mindis2 = dis2;
				minnum = j;
			}
		}
		if(minnum>=0)
		{
			Mob* mob=vec[minnum];
			if(TryAttack(mob))
			{
				mob->_hp-=100;
				setlinestyle(PS_SOLID,3);
				setlinecolor(LIGHTGRAY);
				line(_x+GRIDSIZE/2+1,_y+GRIDSIZE/2+1,mob->_x+1,mob->_y+1);
				setlinecolor(RGB(255,255,0));
				line(_x+GRIDSIZE/2,_y+GRIDSIZE/2,mob->_x,mob->_y);
				setbkmode(TRANSPARENT);
				settextstyle(10,0,L"Consolas");
				outtextxy(mob->_x, mob->_y,L"-100");
				setlinestyle(PS_SOLID,1);
			}
		}
		_aclock = 0;
	}
	
}