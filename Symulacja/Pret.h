#pragma once
#include <windows.h>
#include <math.h>
class Pret
{
	friend class Collision;
private:
	RECT Rc;
	XFORM xfm;
	float SpeedX;
	float SpeedY;
	float Mass;
	float Omega;
	float Omega0;
	float PrevOmega;
	bool hit;
	HPEN penW;
	HPEN penB;
public:
	Pret();
	void Rysuj(HWND hwnd, HDC hdc, RECT rcOkno);
	RECT GetPosition();
	void SetOnHit(float kMass, float kSpeed);
	void SetMass(float mass);
	float GetMass();
	void Clear(HDC hdc);
};

