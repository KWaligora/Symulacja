#pragma once
#include "windows.h"
class Kulka
{
private:
	RECT Rc;
	int SpeedX;
	int SpeedY;
public:
	Kulka();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
	void SetSpeed(int speed);
	RECT GetPosition();
	void Collision(RECT p, HWND hwnd);
};

