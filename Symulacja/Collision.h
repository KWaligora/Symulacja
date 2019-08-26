#pragma once
#include <windows.h>
#include "Pret.h"
#include "Kulka.h"
class Collision
{
	Kulka *kulka;
	Pret *pret;
public:
	Collision(Kulka *kulka, Pret *pret);
	int CheckCollision();
};

