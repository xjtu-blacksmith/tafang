#pragma once
#include<graphics.h>
#include"AllThingsDefine.h"
#define GRIDSIZE 20

struct BASEPOINT{int row; int column;/* bool operator == (BASEPOINT& ref)const{return ref.row==this->row && ref.column == this->column;}*/};

class Object
{
public:
	Object(int X=0,int Y=0);
	~Object();

	int _x;
	int _y;
	int _row;
	int _column;
	

	// ¥ø–È  ªÊ÷∆µ±«∞obj
	virtual void Draw() = 0;

	void SetXY(int newX, int newY);
	int SquaredDist(Object* obj2);
	void MoveXY(int rX, int rY);
};

