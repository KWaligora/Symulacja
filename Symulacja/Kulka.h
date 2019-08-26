#pragma once
#include "windows.h"
class Kulka
{
	friend class Collision;
private:
	RECT Rc;
	float SpeedX;
	float SpeedY;
	float Mass;
	bool hit;
public:
	Kulka();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
	void SetSpeed(float speed);
	RECT GetPosition();
	void SetMass(float mass);
	float GetMass();
	float GetSpeed();
	RECT GetRect();
	void SetOnhit(float pMass);
};

