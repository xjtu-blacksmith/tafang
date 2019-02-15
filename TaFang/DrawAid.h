#pragma once
#include<graphics.h>
#define _DRAWAID_SHADCOLOR_ RGB(100,100,100)

void DrawTextAid(int posX, int posY, LPCTSTR str, bool drawshad = true,int shadbias = 2,COLORREF shadcol = _DRAWAID_SHADCOLOR_);
