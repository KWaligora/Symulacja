#pragma once
#include "windows.h"
class Kulka
{
private:
	RECT Rc;
	float SpeedX;
	float SpeedY;
	float Mass;
public:
	Kulka();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
	void SetSpeed(float speed);
	RECT GetPosition();
	bool Collision(RECT p, HWND hwnd);
	void SetMass(float mass);
	float GetMass();
	float GetSpeed();
	void SetOnhit(float pMass);
};

