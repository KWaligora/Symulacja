#pragma once
#include <windows.h>
class Pret
{
private:
	RECT Rc;
	float SpeedX;
	float SpeedY;
	float Mass;
public:
	Pret();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
	RECT GetPosition();
	void SetOnHit(float kMass, float kSpeed);
	void SetMass(float mass);
	float GetMass();
};

