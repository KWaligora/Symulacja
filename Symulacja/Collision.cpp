#include "Collision.h"

Collision::Collision(RECT pretR, RECT kulkaR)
{
	this->pretR = pretR;
	this->kulkaR = kulkaR;
}

bool Collision::CheckCollsion() {
	if ((kulkaR.left <= pretR.right && kulkaR.left >= pretR.left) 
		&& (kulkaR.top >= pretR.top && kulkaR.bottom <= pretR.bottom)) { //left
		return true;
	}
	return false;
}
