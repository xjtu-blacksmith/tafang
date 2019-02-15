#include"DrawAid.h"

void DrawTextAid(int posX, int posY, LPCTSTR str, bool drawshad, int shadbias, COLORREF shadcol){
	COLORREF prevcol = gettextcolor();
	RECT r;

	int xx = textwidth(str)/2 + 2;
	int yy = textheight(str) /2 +2;

	if (drawshad){
		settextcolor(shadcol);
		r.left = posX - xx + shadbias;
		r.right = posX + xx + shadbias;
		r.top = posY - yy + shadbias;
		r.bottom = posY + yy + shadbias;
		drawtext(str, &r, DT_CENTER | DT_BOTTOM | DT_VCENTER);
	}

	settextcolor(prevcol);
	r.left = posX - xx;
	r.right = posX + xx;
	r.top = posY - yy;
	r.bottom = posY + yy;
	drawtext(str, &r, DT_CENTER | DT_BOTTOM | DT_VCENTER);
}