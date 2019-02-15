#include "Rocket.h"

Rocket::Rocket(int row,int col):Tower(row,col,150,15,ROCKET)
{
	_bulletNum = 6;
}

Rocket::~Rocket(void)
{
}

void Rocket::Attack(vector<Mob*> &vec)
{
	_aclock++;
	if (_aclock>_attackclock && !vec.empty()){
		setlinestyle(PS_DOT, 5);
		
		for (int i = 0; i<vec.size(); i++){
			_aclock = _attackclock + 1;
			if (TryAttack(vec[i]) && _bulletNum>0){
				vec[i]->_hp -= 30;
				// ´Ë´¦»­ÒõÓ°
				setlinecolor(LIGHTGRAY);
				line(_column*GRIDSIZE + GRIDSIZE / 2+1, _row*GRIDSIZE + GRIDSIZE / 2+1,
					vec[i]->_x+1, vec[i]->_y+1);
				setlinecolor(RGB(255,0,0));
				line(_column*GRIDSIZE + GRIDSIZE / 2, _row*GRIDSIZE + GRIDSIZE / 2,
					vec[i]->_x, vec[i]->_y);
				setbkmode(TRANSPARENT);
				settextstyle(10,0,L"Consolas");
				outtextxy(vec[i]->_x, vec[i]->_y,L"-30");
				_bulletNum--;
			}
		}	
		_bulletNum = 6;
		setlinestyle(PS_SOLID, 1);
		_aclock = 0;
	}
}

void Rocket::Draw()
{
	setlinecolor(RGB(255,0,0));
	setlinestyle(PS_SOLID, 2);
	rectangle(_column*GRIDSIZE+2,_row*GRIDSIZE+2,(_column+1)*GRIDSIZE-1,(_row+1)*GRIDSIZE-1);
	setlinestyle(PS_SOLID, 1);
	setfillcolor(LIGHTRED);
	fillcircle(_column*GRIDSIZE+GRIDSIZE/4,_row*GRIDSIZE+GRIDSIZE/4,2);
	fillcircle(_column*GRIDSIZE+GRIDSIZE*3/4,_row*GRIDSIZE+GRIDSIZE/4,2);
	fillcircle(_column*GRIDSIZE+GRIDSIZE/4,_row*GRIDSIZE+GRIDSIZE*3/4,2);
	fillcircle(_column*GRIDSIZE+GRIDSIZE*3/4,_row*GRIDSIZE+GRIDSIZE*3/4,2);
}