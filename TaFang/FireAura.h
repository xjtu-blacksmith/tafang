#pragma once
#include "Aura.h"
class FireAura :
	public Aura
{
public:
	FireAura(int X,int Y,int Range=30);
	~FireAura();

	void WorkFunction(vector<Mob*> &vec);
	void Draw();
};

