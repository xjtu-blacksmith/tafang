#include <graphics.h>
#include <conio.h>
#include "Game.h"

int main()
{
	Game game;
	game.run();
	MessageBox(GetForegroundWindow(),L"���������ˣ�����������������",L"��Ϸ����",MB_OK);
	return 0;
}