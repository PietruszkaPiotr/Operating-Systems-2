#include "Client.h"

Client::Client(int id, long int speed) {
	this->id=id;
	this->clientSpeed=speed;
	this->currX=0;
	this->currY=2+5*id;
	this->lastX=0;
	this->lastY=2+5*id;
	this->destX=7;
}

Client::~Client() {

}

void Client::moveFun() {
	int tmpX = currX;
	if(destX==7) tmpX++;
	else tmpX--;
	lastX=currX;
	currX=tmpX;
}
