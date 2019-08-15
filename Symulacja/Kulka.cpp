#include "Kulka.h"

Kulka::Kulka()
{
	Rc.left = 600;
	Rc.top = 375;
	Rc.right = 650;
	Rc.bottom = 325;

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

void Kulka::SetSpeed(float speed) {
	SpeedX = -speed;
}

RECT Kulka::GetPosition() {
	return Rc;
}

bool Kulka::Collision(RECT p, HWND hwnd) {
	
	if ((Rc.left <= p.right && Rc.left >= p.left) && (Rc.top >= p.top && Rc.bottom <= p.bottom)) { //left
		SpeedX = -SpeedX;
		return true;
	}
	return false;	
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

void Kulka::SetOnhit(float pMass) {
	SpeedX = ((4 * Mass - pMass) / (4 * Mass + pMass))*SpeedX;
}

