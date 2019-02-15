#include "IceTower.h"


IceTower::IceTower(int row, int col) :Tower(row, col, 80, 35, ICE)
{
	p[0].x = _x + 10;
	p[0].y = _y + 4;
	p[1].x = _x + 6;
	p[1].y = _y + 7;
	p[2].x = _x + 6;
	p[2].y = _y + 13;
	p[3].x = _x + 10;
	p[3].y = _y + 16;
	p[4].x = _x + 14;
	p[4].y = _y + 13;
	p[5].x = _x + 14;
	p[5].y = _y + 7;
}


IceTower::~IceTower()
{
}

void IceTower::Attack(vector<Mob*> &vec, vector<Aura*> &aura){
	_aclock++;
	if (_aclock>_attackclock &&!vec.empty()){
		for (int i = 0; i<vec.size(); i++){
			if (TryAttack(vec[i])){
				//create ice aura
				aura.push_back(new IceAura(_x + GRIDSIZE / 2, _y + GRIDSIZE / 2, _range));
				break;
			}
		}
		_aclock = 0;
	}
}

void IceTower::Draw(){
	setlinecolor(RGB(89,108,238));
	rectangle(_column*GRIDSIZE + 1, _row*GRIDSIZE + 1, (_column + 1)*GRIDSIZE - 1, (_row + 1)*GRIDSIZE - 1);
	setfillcolor(RGB(95, 128, 248));
	fillpolygon(p,6);
}