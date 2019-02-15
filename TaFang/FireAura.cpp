#include "FireAura.h"


FireAura::FireAura(int X,int Y,int Range) :Aura(X,Y,Range,16,FIREAURA)
{
}


FireAura::~FireAura()
{
}

void FireAura::WorkFunction(vector<Mob*> &vec){
	if (!vec.empty()){
		int srange = _range*_range;
		for (int i = 0; i<vec.size(); i++){
			if (SquaredDist(vec[i])<srange){
				vec[i]->_hp -= 3;
			}
		}
	}
}

void FireAura::Draw(){
	setfillstyle(BS_HATCHED,HS_FDIAGONAL);
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(255, 80, 30));
	setlinecolor(RGB(255, 140, 30));
	setlinestyle(PS_SOLID, 2);
	fillcircle(_x, _y, _range);
	setlinestyle(PS_SOLID, 1);
	setfillstyle(BS_SOLID);
	setbkmode(OPAQUE);
}