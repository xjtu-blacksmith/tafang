#include "IceAura.h"


IceAura::IceAura(int X,int Y,int Range) :Aura(X,Y,Range,10,ICEAURA)
{
}


IceAura::~IceAura()
{
}

void IceAura::WorkFunction(vector<Mob*> &vec){
	if (!vec.empty()){
		int srange = _range*_range;
		for (int i = 0; i<vec.size(); i++){
			if (SquaredDist(vec[i])<srange){
				vec[i]->_hp -= 1;
				vec[i]->_moveclock = vec[i]->_maxmoveclock * 3.3;
			}
		}
	}
}

void IceAura::Draw(){
	setfillstyle(BS_HATCHED,HS_BDIAGONAL);
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(139,239,248));
	setlinecolor(RGB(139, 239, 248));
	setlinestyle(PS_SOLID, 2);
	fillcircle(_x, _y, _range);
	setlinestyle(PS_SOLID, 1);
	setfillstyle(BS_SOLID);
	setbkmode(OPAQUE);
}