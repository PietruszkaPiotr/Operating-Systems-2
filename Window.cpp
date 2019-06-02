#include "Window.h"
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <time.h>

Window::Window() {
	initWindow();
}

Window::~Window() {
	endwin();
}

void Window::initWindow() {
    initscr();
    noecho();
    curs_set(FALSE);
    clear();
    refresh();
}

void Window::car(int id, int dir, int x, int y, int packs) {
	if(dir) {
	mvprintw(y-2, x-1, "_____");
	mvprintw(y-1, x-2, "/");
	mvprintw(y-1, x+4, "|");
	mvprintw(y, x-3, "|_ __ _|");
	mvprintw(y+1, x-1, "0  0");
	mvprintw(y-1, x-1, "%d", id);
	mvprintw(y-1, x+2, "%d", packs);
	}
	else {
	mvprintw(y-2, x-2, "_____");
	mvprintw(y-1, x+3, "\\");
	mvprintw(y-1, x-3, "|");
	mvprintw(y, x-3, "|_ __ _|");
	mvprintw(y+1, x-1, "0  0");
	mvprintw(y-1, x+2, "%d", id);
	mvprintw(y-1, x-2, "%d", packs);
	}
	
}

void Window::clearCar(int x, int y) {
	for(int i=x-3; i<=x+4; i++)
		for(int j=y-2; j<=y+1; j++)
			mvprintw(j, i, " ");
}

void Window::packMachine(int id) {
	int y=2+5*id, x=10;
	id+=1;
	for(int i=x-2; i<=x+2; i++) {
		for(int j=y-1; j<=y+1; j++){
			if(i==x && j==y) mvprintw(j, i, "%d",id);
			else mvprintw(j, i, "X");
		}
	}
}

void Window::firm() {
	int y=13, x=80;
	mvprintw(y-4, x-5, "___________");
	mvprintw(y-3, x-6, "/           \\");
	mvprintw(y-2, x-6, "XXXXXXXXXXXXX");
	for(int i=1; i>=-1; i--) {
		mvprintw(y-i, x-6, "H");
		mvprintw(y-i, x+6, "H");
	}
	mvprintw(y+2, x-6, "H___________H");
	mvprintw(y, x-4, "fastPacks");
	refresh();
}

void Window::scene(int nPM, int nCar) {
	firm();
	for(int i=0; i<nPM; i++)
		packMachine(i);
	refresh();
}

void Window::update(Shared *shared) {
	int dir;
	//ruch samochodu
	for(int i=0; i<shared->carCounter; i++)
		clearCar(shared->cars[i]->lastX, shared->cars[i]->lastY);
	for(int i=0; i<shared->carCounter; i++) {
		if(shared->cars[i]->destY==13) dir=0;
		else dir=1;
		car(shared->cars[i]->id+1, dir, shared->cars[i]->currX, shared->cars[i]->currY, shared->cars[i]->nPacks);
		//mvprintw(3, 20+i*2, "%d", shared->cars[i]->nPacks);
	}

	//licznik paczek w PM
	for(int i=0; i<shared->nPM; i++) {
		mvprintw(5*i, 8, "     ");
		mvprintw(5*i, 8, "   %d", shared->packs[i]);
	}
	
	//licznik paczek w samochodzie
	for(int i=0; i<shared->carCounter; i++) {
		mvprintw(1, 70+i*3, "  ");
		mvprintw(1, 70+i*3, "%d", i+1);
		mvprintw(2, 70+i*3, "  ");
		mvprintw(2, 70+i*3, "%d", shared->cars[i]->nPacks);
	}

	//ruch klienta
	for(int i=0; i<shared->clientCounter; i++) 
		mvprintw(shared->clients[i]->lastY, shared->clients[i]->lastX, " ");
	for(int i=0; i<shared->clientCounter; i++) 
		mvprintw(shared->clients[i]->currY, shared->clients[i]->currX, "o");

	refresh();
}



















