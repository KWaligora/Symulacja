#include "Pret.h"

Pret::Pret()
{
	Rc.left = 290;
	Rc.top = 140;
	Rc.right = 300;
	Rc.bottom = 540;

	SpeedX = 0;
	SpeedY = 0;

	Omega = 0;
	Omega0 = 0;

	hit = false;

	penW = CreatePen(PS_SOLID, 5, 0xFFFFFF);
	penB = CreatePen(PS_SOLID, 1, 0x000000);
}

void Pret::Rysuj(HWND hwnd, HDC hdc, RECT rcOkno) {
	Clear(hdc);
	float factor = (2.0f * 3.1416f) / 360.0f;
	float rot = Omega * factor;
	PrevOmega = Omega;
	Omega += Omega0;
	float x0 = (Rc.left + Rc.right) / 2;
	float y0 = (Rc.top + Rc.bottom) / 2;

	SetGraphicsMode(hdc, GM_ADVANCED);

	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);
	float x = (float)(x0 - cos(rot)*x0 + sin(rot)*y0);
	float y = (float)(y0 - cos(rot)*y0 - sin(rot)*x0);
	xfm.eDx = (float)x;
	xfm.eDy = (float)y;


	SetWorldTransform(hdc, &xfm);
	//FillRect(hdc, &Rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	if (Rc.left <= 0 || Rc.right >= rcOkno.right) {
		SpeedX = 0;
		Omega -= Omega0;
	}
	if (Rc.top <= 0 || Rc.bottom >= rcOkno.bottom) {
		SpeedY = 0;
		Omega -= Omega0;
	}
	OffsetRect(&Rc, SpeedX, SpeedY);
	SelectObject(hdc, penB);
	Rectangle(hdc, Rc.left, Rc.top, Rc.right, Rc.bottom);
	SetGraphicsMode(hdc, GM_COMPATIBLE);
}

RECT Pret::GetPosition() {
	return Rc;
}

void Pret::SetOnHit(float kSpeed, float kMass) {
	if (!hit) {
		SpeedX = ((2.0 * kMass) / (4.0 * kMass + Mass))*kSpeed;
		SpeedX = -SpeedX;
		Omega0 = (6 / 1)*(2 * kMass / (4 * kMass + Mass));
		float d = Omega0 * (180 / 3.14);
		Omega = d;
		Omega = Omega0;
		hit = true;
	}
}

void Pret::SetMass(float mass) {
	Mass = mass;
}

float Pret::GetMass() {
	return Mass;
}

void Pret::Clear(HDC hdc) {
	float factor = (2.0f * 3.1416f) / 360.0f;
	float rot = PrevOmega * factor;
	float x0 = (Rc.left + Rc.right) / 2;
	float y0 = (Rc.top + Rc.bottom) / 2;

	SetGraphicsMode(hdc, GM_ADVANCED);

	xfm.eM11 = (float)cos(rot);
	xfm.eM12 = (float)sin(rot);
	xfm.eM21 = (float)-sin(rot);
	xfm.eM22 = (float)cos(rot);
	float x = (float)(x0 - cos(rot)*x0 + sin(rot)*y0);
	float y = (float)(y0 - cos(rot)*y0 - sin(rot)*x0);
	xfm.eDx = (float)x;
	xfm.eDy = (float)y;

	SetWorldTransform(hdc, &xfm);

	OffsetRect(&Rc, SpeedX, SpeedY);
	SelectObject(hdc, penW);
	Rectangle(hdc, Rc.left, Rc.top, Rc.right, Rc.bottom);
	SetGraphicsMode(hdc, GM_COMPATIBLE);
}