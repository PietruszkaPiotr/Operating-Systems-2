#include "Window.h"
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <vector>

bool working = true;
Window *window;
Shared *shared;
const int nCar = 5; //ile samochodów
const int nPM = 5; //ile paczkomatów (PM - Pack Machine)
int dest = 69;
int destPM[nPM];
std::queue <Car*> qToPM[nPM]; //kolejka do paczkomaru
std::queue <Car*> qToFirm; //kolejka do firmy
std::mutex car_mtx;
std::mutex car_q_mtx;
std::mutex PM_mtx;
std::mutex client_mtx;
std::mutex firm_mtx;
std::condition_variable car_cv;
std::condition_variable PM_cv;
std::condition_variable client_cv;
std::condition_variable firm_cv;

void stop() {
    while (working) {
        char c = getchar();
        if(c == ' ')
            working = false;
    }
}

void carMoving(int id) {
    while(working) {
	usleep(shared->cars[id]->carSpeed);

	if(shared->cars[id]->currX != shared->cars[id]->destX || shared->cars[id]->currY != shared->cars[id]->destY) {
	    shared->cars[id]->moveFun();
	    continue;
  	}
	else {
	    if(shared->cars[id]->currX == dest && shared->cars[id]->destX == dest) {
		car_q_mtx.lock();
		if(!shared->cars[id]->inQ){
		    qToFirm.push(shared->cars[id]);
		    shared->cars[id]->inQ=true;
		    dest-=7;
		    for(int i=0; i<nCar; i++)
			if(shared->cars[i]->destY==13 && !shared->cars[i]->inQ)
			    shared->cars[i]->destX=dest;

		    firm_cv.notify_one();
		}
		car_q_mtx.unlock();
	    }
	    else {
		for(int i=0; i<nPM; i++){
		    if(shared->cars[id]->currY == 2+5*i) {
			car_q_mtx.lock();
			if(!shared->cars[id]->inQ){
			    qToPM[i].push(shared->cars[id]);
			    shared->cars[id]->inQ=true;
			    destPM[i]+=7;
			    for(int j=0; j<nCar; j++)
				if(shared->cars[j]->destY==2+i*5 && !shared->cars[j]->inQ)
			    	    shared->cars[j]->destX=destPM[i];
			    PM_cv.notify_all();
			}
			car_q_mtx.unlock();
		    }
		}
	    }
	    std::unique_lock<std::mutex> wait_car(car_mtx);
	    	car_cv.wait(wait_car);
	    wait_car.unlock();
	}
    }
    car_cv.notify_all();
    PM_cv.notify_all();
    client_cv.notify_all();
    firm_cv.notify_one();
}

void updateWindow() {
    window->scene(nPM, nCar);
    while(working) {
	window->update(shared);
	usleep(5000);
    }
}

void clientMoving(int id) {
    int take;
    while(working) {
	usleep(shared->clients[id]->clientSpeed);
	if(shared->clients[id]->currX != shared->clients[id]->destX) {
	    shared->clients[id]->moveFun();
	    continue;
	}
	else {
	    if(shared->clients[id]->currX==0) {
		shared->clients[id]->destX=7;
		take = rand()% 10 + 1;
		continue;
	    }
	    if(shared->packs[id]==0 || shared->packs[id]<take) {
		std::unique_lock<std::mutex> wait_client(client_mtx);
		client_cv.wait(wait_client);
	    	wait_client.unlock();
            	continue;
	    }
	    shared->packs[id]-=take;
	    shared->clients[id]->destX=0;
	    PM_cv.notify_all();	
	}
    }
}

void givePacks() {
    while(working) {
	usleep(200000);
	if(!qToFirm.empty()) {
	    if(qToFirm.front()->nPacks >= 65) {
		qToFirm.front()->destX = destPM[0];
		qToFirm.front()->destY = 2;
		qToFirm.front()->inQ=false;
		qToFirm.pop();
		dest+=7;
		for(int i=0; i<nCar; i++)
		    if(shared->cars[i]->destY==13)
			shared->cars[i]->destX+=7;
		car_cv.notify_all();
		continue;
	    }
	    if(qToFirm.front()->currX!=69) continue;
	    qToFirm.front()->nPacks+=5;
	}
	else {
	    std::unique_lock<std::mutex> wait_firm(firm_mtx);
		firm_cv.wait(wait_firm);
	    wait_firm.unlock();
	}
    }
}

void takePacks(int id) {
    shared->packs[id]=0;
    while(working) {
	usleep(40000);
	if(qToPM[id].empty()) {
	    std::unique_lock<std::mutex> wait_pm(PM_mtx);
	    	PM_cv.wait(wait_pm);
	    wait_pm.unlock();
	}
	else {
	    if(qToPM[id].front()->nPacks==0) {
		qToPM[id].front()->destX=dest;
		qToPM[id].front()->destY=13;
		qToPM[id].front()->inQ=false;
		qToPM[id].pop();
		destPM[id]-=7;
		for(int j=0; j<nCar; j++)
		    if(shared->cars[j]->destY==2+5*id)
			shared->cars[j]->destX-=7;
		car_cv.notify_all();
		continue;
	    }
	    if(shared->packs[id]>=75) {
		if(id==nPM-1) {
		    std::unique_lock<std::mutex> wait_pm(PM_mtx);
	    		PM_cv.wait(wait_pm);
	    	    wait_pm.unlock();
		    continue;
		}
		else {
		    qToPM[id].front()->destX=destPM[id+1];
		    qToPM[id].front()->destY=2+5*(id+1);
		    qToPM[id].front()->inQ=false;
		    qToPM[id].pop();
		    destPM[id]-=7;
		    for(int j=0; j<nCar; j++)
		    	if(shared->cars[j]->destY==2+5*id)
			    shared->cars[j]->destX-=7;
		    car_cv.notify_all();
		    continue;
		}
	    }
	    client_cv.notify_all();
	    if(qToPM[id].front()->currX!=16) continue;
	    PM_mtx.lock();
	    shared->packs[id]+=1;
	    qToPM[id].front()->nPacks-=1;
	    PM_mtx.unlock();
	}
    }
    car_cv.notify_all();
    PM_cv.notify_all();
    client_cv.notify_all();
    firm_cv.notify_one();
}

int main() {
    srand(time(NULL));
    window = new Window();
    shared = new Shared(nPM);

    for(int i=0; i<nPM; i++) 
		destPM[i]=16;

    std::vector<std::thread> cars;
    std::vector<std::thread> clients;
    std::vector<std::thread> PMs;

    std::thread winThread(updateWindow);
    std::thread exitThread(stop);
    std::thread firmThread(givePacks);
    for(int i=0; i<nCar; i++) {
		shared->addCar(rand()% 20000 + 50000);
		cars.push_back(std::thread(carMoving, i));
    }
    for(int i=0; i<nPM; i++) {
		shared->addClient(rand()% 25000 + 75000);
		clients.push_back(std::thread(clientMoving, i));
    }
    for(int i=0; i<nPM; i++)
		PMs.push_back(std::thread(takePacks, i));


    for(int i=0; i<nCar; i++) cars[i].join();
    for(int i=0; i<nPM; i++) PMs[i].join();
    for(int i=0; i<nPM; i++) clients[i].join();
    firmThread.join();
    winThread.join();
    exitThread.join();
    delete window;
    delete shared;
    return 0;
}






















