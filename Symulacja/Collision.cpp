#include "Collision.h"

Collision::Collision(Kulka *kulka, Pret *pret)
{
	this->kulka = kulka;
	this->pret = pret;
}

int Collision::CheckCollision() {
	if ((kulka->Rc.left <= pret->Rc.right && kulka->Rc.left >= pret->Rc.left) &&
		(kulka->Rc.top >= pret->Rc.top && kulka->Rc.bottom <= pret->Rc.bottom)) { //left
		return 1;
	}
	return 0;
}
