#include "Shared.h"
class Window {
public:
	Window();
	~Window();
	void initWindow();
	void scene(int nPM, int nCar);
	void car(int id, int dir, int x, int y, int packs);
	void clearCar(int x, int y);
	void packMachine(int id);
	void firm();
	void update(Shared *shared);
};
