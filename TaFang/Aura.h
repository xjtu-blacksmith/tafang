#pragma once
#include "Object.h"
#include<vector>
#include"Mob.h"
using namespace std;

typedef enum _AURA_TYPE_ {FIREAURA,ICEAURA,HEALAURA} AURATYPE;

class Aura :
	public Object
{
public:
	int _range;
	int _tclock;
	int _durTime;
	AURATYPE _type;

	Aura(int X,int Y,int range,int durTime,AURATYPE type);
	~Aura();
	// �����Ƿ���Ҫ����
	bool Work(vector<Mob*> &vec);
	// ����
	virtual void WorkFunction(vector<Mob*> &vec) = 0;
};

