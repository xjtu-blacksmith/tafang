#include "LineTower.h"
#include <vector>

using namespace std;

LineTower::LineTower(int row,int col):Tower(row,col,50,2,LINE)
{
}

LineTower::~LineTower(void)
{
}

void LineTower::Draw()
{
	setlinecolor(RGB(0,255,0));
	setlinestyle(PS_SOLID, 2);
	rectangle(_column*GRIDSIZE+2,_row*GRIDSIZE+2,(_column+1)*GRIDSIZE-1,(_row+1)*GRIDSIZE-1);
	setlinestyle(PS_SOLID, 1);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(GREEN);
	fillcircle(_column*GRIDSIZE+GRIDSIZE/2,_row*GRIDSIZE+GRIDSIZE/2,2);
}

void LineTower::Attack(vector<Mob*> &vec)
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
				mob->_hp-=3;
				setlinestyle(PS_DASHDOT,2);
				setlinecolor(LIGHTGRAY);
				line(_x+GRIDSIZE/2+1,_y+GRIDSIZE/2+1,mob->_x+1,mob->_y+1);
				setlinecolor(RGB(0,255,0));
				line(_x+GRIDSIZE/2,_y+GRIDSIZE/2,mob->_x,mob->_y);
				setbkmode(TRANSPARENT);
				settextstyle(10,0,L"Consolas");
				outtextxy(mob->_x, mob->_y,L"-3");
				setlinestyle(PS_SOLID,1);
			}
		}
		_aclock = 0;
	}

}
