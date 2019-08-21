#include "Pret.h"

Pret::Pret()
{
	Rc.left = 295;
	Rc.top = 150;
	Rc.right = 305;
	Rc.bottom = 350;

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

void Pret::SetOnHit(float kSpeed, float kMass) {
	SpeedX = ((2 * kMass) / (4 * kMass + Mass))*kSpeed;
	SpeedX = -SpeedX;
}

void Pret::SetMass(float mass) {
	Mass = mass;
}

float Pret::GetMass() {
	return Mass;
}