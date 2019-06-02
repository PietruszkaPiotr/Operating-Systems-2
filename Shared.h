#include "Car.h"
#include "Client.h"
#include <vector>
class Shared { 
public:
	std::vector<Car*> cars;
	std::vector<Client*> clients;
	int *packs;
	int nPM;
	int carCounter;
	int clientCounter;
	Shared(int n);
	~Shared();
	void addCar(long int speed);
	void addClient(long int speed);
};
