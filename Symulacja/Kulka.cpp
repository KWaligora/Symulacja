#include "Kulka.h"

Kulka::Kulka()
{
	Rc.left = 600;
	Rc.top = 515;
	Rc.right = 625;
	Rc.bottom = 540;

	SpeedX = 0;
	SpeedY = 0;

	hit = false;
}

void Kulka::Rysuj(HWND hwnd, HDC hdc, RECT rcOkno) {
	FillRect(hdc, &Rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	if (Rc.left <= 0 || Rc.right >= rcOkno.right) SpeedX = 0;
	if (Rc.top <= 0 || Rc.bottom >= rcOkno.bottom) SpeedY = 0;
	OffsetRect(&Rc, SpeedX, SpeedY);
	Ellipse(hdc, Rc.left, Rc.top, Rc.right, Rc.bottom);
}

void Kulka::SetSpeed(float speed) {
	SpeedX = -speed;
	SpeedX = SpeedX;
}

RECT Kulka::GetPosition() {
	return Rc;
}

void Kulka::SetMass(float mass) {
	Mass = mass;
}

float Kulka::GetMass() {
	return Mass;
}

float Kulka::GetSpeed() {
	return -SpeedX;
}

RECT Kulka::GetRect()
{
	return Rc;
}

void Kulka::SetOnhit(float pMass) {
	if (!hit) {
		SpeedX = ((4 * Mass - pMass) / (4 * Mass + pMass))*SpeedX;
		hit = true;
	}
}