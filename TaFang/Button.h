#pragma once
#include<graphics.h>
#include "Tower.h"

class Button
{
private:
	IMAGE _bdown;
	IMAGE _bup;

	bool CheckMouseIn(int px, int py);
	bool _isDown;

public:
	int _posx;
	int _posy;
	int _width;
	int _height;
	double _ratiox;
	double _ratioy;

	TOWERTYPE _type;

	Button(int posX, int posY, IMAGE* upimg, IMAGE* downimg, TOWERTYPE type);
	~Button();

	//返回是否按钮起作用
	bool MouseResponse(MOUSEMSG msg);

	void Draw();
	void SetImage(IMAGE* upimg, IMAGE* downimg);

};
