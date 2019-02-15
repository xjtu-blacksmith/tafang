#include "FireTower.h"


FireTower::FireTower(int row, int col) :Tower(row, col, 80, 22, FIRE)
{
	p[0].x = _x + 10;
	p[0].y = _y + 5;
	p[1].x = _x + 4;
	p[1].y = _y + 15;
	p[2].x = _x + 16;
	p[2].y = _y + 15;
}


FireTower::~FireTower()
{
}

void FireTower::Attack(vector<Mob*> &vec, vector<Aura*> &aura){
	_aclock++;
	if (_aclock>_attackclock &&!vec.empty()){
		for (int i = 0; i<vec.size(); i++){
			if (TryAttack(vec[i])){
				//create Fire aura
				vec[i]->_hp -= 30;
				setlinecolor(RGB(255, 0, 0));
				setlinestyle(PS_DASHDOTDOT, 4);
				line(_x + GRIDSIZE / 2, _y + GRIDSIZE / 2, vec[i]->_x, vec[i]->_y);
				setlinestyle(PS_SOLID, 1);
				aura.push_back(new FireAura(vec[i]->_x, vec[i]->_y, 30));
				break;
			}
		}
		_aclock = 0;
	}
}

void FireTower::Draw(){
	setlinecolor(RGB(255,80,30));
	rectangle(_column*GRIDSIZE + 1, _row*GRIDSIZE + 1, (_column + 1)*GRIDSIZE - 1, (_row + 1)*GRIDSIZE - 1);
	setfillcolor(RGB(255, 80, 30));
	fillpolygon(p,3);
}