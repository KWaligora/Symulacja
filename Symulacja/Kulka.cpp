#include "Kulka.h"

Kulka::Kulka()
{
	Rc.left = 500;
	Rc.top = 350;
	Rc.right = 550;
	Rc.bottom = 400;

	SpeedX = 2;
	SpeedY = 2;
}

void Kulka::Rysuj(HWND hwnd) {
	hdc = BeginPaint(hwnd, &ps);
	GetClientRect(hwnd, &rcOkno);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, 700, 700, NULL);
	SetViewportExtEx(hdc, rcOkno.right, rcOkno.bottom, NULL);
	FillRect(hdc, &Rc, (HBRUSH)GetStockObject(HOLLOW_BRUSH));
	if (Rc.left <= 0 || Rc.right >= rcOkno.right) SpeedX = -SpeedX;
	if (Rc.top <= 0 || Rc.bottom >= rcOkno.bottom) SpeedY = -SpeedY;
	OffsetRect(&Rc, SpeedX, SpeedY);
	Ellipse(hdc, Rc.left, Rc.top, Rc.right, Rc.bottom);
	EndPaint(hwnd, &ps);
}