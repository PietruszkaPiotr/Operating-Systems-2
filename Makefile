run: Car.o Client.o main.o Shared.o Window.o
	g++ Car.o Client.o main.o Shared.o Window.o -o run -lncurses -pthread

Car.o: Car.cpp
	g++ -c Car.cpp
	
Client.o: Client.cpp
	g++ -c Client.cpp

Shared.o: Shared.cpp
	g++ -c Shared.cpp
	
Window.o: Window.cpp
	g++ -c Window.cpp

main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm *.o main
