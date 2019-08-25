#pragma once
#include <windows.h>
class Collision
{
	RECT pretR;
	RECT kulkaR;
public:
	Collision(RECT pretR, RECT kulkaR);
	bool CheckCollsion();
};

