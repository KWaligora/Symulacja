#include "Pret.h"

Pret::Pret()
{
	Rc.left = 200;
	Rc.top = 350;
	Rc.right = 400;
	Rc.bottom = 360;

	SpeedX = 0;
	SpeedY = 0;
}

void Pret::Rysuj(HWND hwnd, HDC hdc, RECT rcOkno) {
	
	FillRect(hdc, &Rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	if (Rc.left <= 0 || Rc.right >= rcOkno.right) SpeedX = -SpeedX;
	if (Rc.top <= 0 || Rc.bottom >= rcOkno.bottom) SpeedY = -SpeedY;
	OffsetRect(&Rc, SpeedX, SpeedY);
	Rectangle(hdc, Rc.left, Rc.top, Rc.right, Rc.bottom);
}

RECT Pret::GetPosition() {
	return Rc;
}