#pragma once
#include <windows.h>
#include <math.h>
#include "RPoint.h"
class Pret
{
private:
	RECT Rc;
	XFORM xfm;
	float SpeedX;
	float SpeedY;
	float Mass;
	float Omega;
	float Omega0;
public:
	Pret();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
	RECT GetPosition();
	void SetOnHit(float kMass, float kSpeed);
	void SetMass(float mass);
	float GetMass();
};

