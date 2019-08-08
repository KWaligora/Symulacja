#include "Kulka.h"

Kulka::Kulka()
{
	Rc.left = 700;
	Rc.top = 325;
	Rc.right = 650;
	Rc.bottom = 375;

	SpeedX = 0;
	SpeedY = 0;
}

void Kulka::Rysuj(HWND hwnd, HDC hdc, RECT rcOkno) {
	FillRect(hdc, &Rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	if (Rc.left <= 0 || Rc.right >= rcOkno.right) SpeedX = -SpeedX;
	if (Rc.top <= 0 || Rc.bottom >= rcOkno.bottom) SpeedY = -SpeedY;
	OffsetRect(&Rc, SpeedX, SpeedY);
	Ellipse(hdc, Rc.left, Rc.top, Rc.right, Rc.bottom);
}

void Kulka::SetSpeed(int speed) {
	SpeedX = speed;
	SpeedY = speed;
}
