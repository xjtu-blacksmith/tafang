#include "Grid.h"

Grid::Grid(void)
{
	_type=EMPTY;
	_distance=100;
}

void Grid::Draw()
{
	setlinecolor(BLACK);
	//rectangle(_column*GRIDSIZE,_row*GRIDSIZE,(_column+1)*GRIDSIZE,(_row+1)*GRIDSIZE);
	switch(_type)
	{
	case EMPTY:
		setfillcolor(RGB(10,10,10)); 
		break; 
	case WALL:
	case IRON:
		setfillcolor(RGB(100,100,100)); 
		break; 
	case WATER:
		setfillcolor(RGB(0,0,200)); 
		break; 
	case MUD:
		setfillcolor(RGB(30,11,0));
		break;
	}
	fillrectangle(_column*GRIDSIZE,_row*GRIDSIZE,(_column+1)*GRIDSIZE,(_row+1)*GRIDSIZE);
	
	// ÒÔÏÂ»­³Äµ×
	switch(_type)
	{
	case EMPTY:
		setlinecolor(RGB(30,30,30));
		break;
	case WALL:
		setlinecolor(WHITE);
		break;
	case IRON:
		setlinecolor(RGB(50,50,50));
		break;
	case WATER:
		setlinecolor(RGB(0,0,100));
		break;
	case MUD:
		setlinecolor(RGB(40,15,0));
		break;
	}
	setlinestyle(PS_SOLID|PS_ENDCAP_SQUARE,2);
	rectangle(_column*GRIDSIZE+2,_row*GRIDSIZE+2,(_column+1)*GRIDSIZE-1,(_row+1)*GRIDSIZE-1);
	setlinestyle(PS_SOLID,1);
}

Grid::~Grid(void)
{
}
