#include "Shared.h"

Shared::Shared(int n) {
	this->carCounter = 0;
	this->packs = new int[n];
	this->nPM = n;
}

Shared::~Shared() {
	delete packs;
}

void Shared::addCar(long int speed) {
	Car *car = new Car(carCounter++, speed);
	this->cars.push_back(car);
}

void Shared::addClient(long int speed) {
	Client *client = new Client(clientCounter++, speed);
	this->clients.push_back(client);
}
