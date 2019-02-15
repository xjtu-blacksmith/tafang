#pragma once
#include "mob.h"
#include"HealAura.h"
#include<vector>
using namespace std;

class Healer :
	public Mob
{
public:
	int _healclock;
	static int _healdur;

	Healer(int X, int Y);
	~Healer(void);
	void TryHeal(vector<Aura*> &aura);
	void Draw();
};
