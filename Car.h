class Car {
	int checkDirection();
public:
	int id;
	int currX, currY;
	int lastX, lastY;
	int carSpeed;
	int nPacks;
	int destX;
	int destY;
	bool inQ;
	void moveFun();
	Car(int id, long int speed);
	~Car();
};
