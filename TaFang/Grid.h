#pragma once
#include "object.h"

typedef enum _GRID_TYPE_ { EMPTY, WALL, IRON, WATER, MUD }GRID;

class Grid :
	public Object
{
public:
	GRID _type;
	int F,G,H;
	Grid* _father;
	long _distance;
public:
	Grid(void);
	void Draw();
	~Grid(void);
};
