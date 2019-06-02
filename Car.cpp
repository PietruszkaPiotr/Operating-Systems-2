#include "Car.h"

Car::Car(int id, long int speed) {
	this->id = id;
	this->carSpeed = speed;
	this->currX = 60;
	this->currY = 5;
	this->lastX = 59;
	this->lastY = 5;
	this->destX = 69;
	this->destY = 13;
	this->nPacks = 0;
	this->inQ = false;
}

Car::~Car() {

}

int Car::checkDirection() {
    if (currX < destX) {
	if (currY < destY) return 3;
	if (currY > destY) return 1;
	return 6;
    }
    if (currX > destX) {
	if (currY < destY) return 4;
	if (currY > destY) return 2;
	return 7;
    }
    if (currY < destY) return 5;
    return 0;
}

void Car::moveFun() {
    int tmpX = currX;
    int tmpY = currY;
    int direction = checkDirection();
    switch (direction) {
    case 0:
        tmpY--; break;
    case 1:
        tmpX++; tmpY--; break;
    case 2:
        tmpX--; tmpY--; break;
    case 3:
        tmpX++; tmpY++; break;
    case 4:
        tmpX--; tmpY++; break;
    case 5:
        tmpY++; break;
    case 6:
	tmpX++; break;
    case 7:
	tmpX--; break;
    default: break;
    }
    lastX = currX;
    lastY = currY;
    currX = tmpX;
    currY = tmpY;
}
