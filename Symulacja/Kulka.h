#pragma once
#include "windows.h"
class Kulka
{
private:
	RECT Rc;
	SHORT SpeedX;
	SHORT SpeedY;
	RECT rcOkno;
	PAINTSTRUCT ps;
	HDC hdc;
public:
	Kulka();
	void Rysuj(HWND hwnd);
};

