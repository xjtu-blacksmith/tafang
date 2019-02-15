#pragma once
#include "Aura.h"
class HealAura :
	public Aura
{
public:
	HealAura(int X, int Y, int Range = 30);
	~HealAura();

	void WorkFunction(vector<Mob*> &vec);
	void Draw();
};

