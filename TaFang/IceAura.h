#pragma once
#include "Aura.h"
class IceAura :
	public Aura
{
public:
	IceAura(int X,int Y,int Range=80);
	~IceAura();

	void WorkFunction(vector<Mob*> &vec);
	void Draw();
};

