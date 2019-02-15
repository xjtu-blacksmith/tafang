#include "Elec.h"

Elec::Elec(int row,int col):Tower(row,col,100,50,ELEC)
{
	_bulletNum = 3;
}

Elec::~Elec(void)
{
}

void Elec::Attack(vector<Mob*> &vec)
{
	_aclock++;
	if (_aclock>_attackclock && !vec.empty()){
		setlinestyle(PS_DASHDOTDOT, 3);
		
		for (int i = 0; i<vec.size(); i++){
			_aclock = _attackclock + 1;
			if (TryAttack(vec[i]) && _bulletNum>0){
				vec[i]->_hp -= 15;
				vec[i]->_moveclock = vec[i]->_maxmoveclock + 8;
				// ´Ë´¦»­ÒõÓ°
				setlinecolor(LIGHTGRAY);
				line(_column*GRIDSIZE + GRIDSIZE / 2+1, _row*GRIDSIZE + GRIDSIZE / 2+1,
					vec[i]->_x+1, vec[i]->_y+1);
				setlinecolor(RGB(0, 255, 255));
				line(_column*GRIDSIZE + GRIDSIZE / 2, _row*GRIDSIZE + GRIDSIZE / 2,
					vec[i]->_x, vec[i]->_y);
				setbkmode(TRANSPARENT);
				settextstyle(10,0,L"Consolas");
				outtextxy(vec[i]->_x, vec[i]->_y,L"-15");
				outtextxy(vec[i]->_x, vec[i]->_y+10,L"FREEZE!");
				_bulletNum--;
			}
		}	
	_bulletNum = 3;
	setlinestyle(PS_SOLID, 1);
	_aclock = 0;
	}
}

void Elec::Draw()
{
	setlinecolor(RGB(0,255,255));
	setlinestyle(PS_SOLID, 2);
	rectangle(_column*GRIDSIZE+2,_row*GRIDSIZE+2,(_column+1)*GRIDSIZE-1,(_row+1)*GRIDSIZE-1);
	setlinestyle(PS_SOLID,1);
	setfillcolor(RGB(0,200,200));
	fillcircle(_column*GRIDSIZE+GRIDSIZE/2,_row*GRIDSIZE+GRIDSIZE/2,GRIDSIZE*2/5);
}
