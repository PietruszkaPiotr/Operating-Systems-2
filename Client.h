class Client {
public:
	int id;
	int clientSpeed;
	int currX, currY;
	int lastX, lastY;
	int destX;
	Client(int id, long int speed);
	~Client();
	void moveFun();
};
