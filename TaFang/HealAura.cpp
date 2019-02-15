#include "HealAura.h"


HealAura::HealAura(int X, int Y, int Range) :Aura(X, Y, Range, 20, HEALAURA)
{
}


HealAura::~HealAura()
{
}

void HealAura::WorkFunction(vector<Mob*> &vec){
	if (!vec.empty()){
		int srange = _range*_range;
		for (int i = 0; i<vec.size(); i++){
			if (SquaredDist(vec[i])<srange){
				vec[i]->_hp += 2;
			}
		}
	}
}

void HealAura::Draw(){
	setfillstyle(BS_HATCHED,HS_VERTICAL);
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(167, 239, 16));
	setlinecolor(RGB(40, 210, 12));
	setlinestyle(PS_SOLID, 2);
	fillcircle(_x, _y, _range);
	setlinestyle(PS_SOLID, 1);
	setfillstyle(BS_SOLID);
	setbkmode(OPAQUE);
}