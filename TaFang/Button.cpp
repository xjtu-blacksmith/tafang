#include "Button.h"


Button::Button(int posX, int posY, IMAGE* upimg, IMAGE* downimg,TOWERTYPE type)
{
	_posx = posX;
	_posy = posY;
	_width = 0;
	_height = 0;
	SetImage(upimg, downimg);
	_isDown = false;
	_ratiox = 1.0;
	_ratioy = 1.0;
	_type = type;
}


Button::~Button()
{
}

//返回是否按钮起作用
bool Button::MouseResponse(MOUSEMSG msg)
{
	if (msg.uMsg == WM_LBUTTONDOWN){
		if (CheckMouseIn(msg.x, msg.y)){
			_isDown = true;
		}
		return false;
	}
	if (msg.uMsg == WM_LBUTTONUP){
		_isDown = false;
		if (CheckMouseIn(msg.x, msg.y)){
			return true;
		}
		return false;
	}
	return false;
}


void Button::SetImage(IMAGE* upimg, IMAGE* downimg)
{
	_bup = *upimg;
	_bdown = *downimg;
	_height = _bup.getheight();
	_width = _bup.getwidth();
}


bool Button::CheckMouseIn(int px, int py)
{
	if (px >= _posx && py >= _posy && px <= (_posx + _width*_ratiox) && py <= (_posy + _height*_ratioy)){
		return true;
	}
	return false;
}


void Button::Draw()
{
	setaspectratio(_ratiox, _ratioy);
	if (_isDown){
		putimage(_posx / _ratiox, _posy / _ratioy, &_bdown);
	}
	else{
		putimage(_posx / _ratiox, _posy / _ratioy, &_bup);
	}
	setaspectratio(1, 1);
}