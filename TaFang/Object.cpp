#include "Object.h"


Object::Object(int X,int Y)
{
	SetXY(X, Y);
}


Object::~Object()
{
}


void Object::SetXY(int newX, int newY)
{
	_x = newX;
	_y = newY;
	_row = _y / GRIDSIZE;
	_column = _x / GRIDSIZE;
}


int Object::SquaredDist(Object* obj2)
{
	return (_x + GRIDSIZE/2 - obj2->_x) * (_x + GRIDSIZE/2 - obj2->_x) + (_y + GRIDSIZE/2 - obj2->_y) * (_y + GRIDSIZE/2 - obj2->_y);
}


void Object::MoveXY(int rX, int rY)
{
	SetXY(_x+rX,_y+rY);
}
