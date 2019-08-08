#pragma once
#include <windows.h>
class Pret
{
private:
	RECT Rc;
	int SpeedX;
	int SpeedY;
public:
	Pret();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
};

