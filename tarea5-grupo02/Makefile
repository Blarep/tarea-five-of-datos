all: tarea5

tarea5: main.o funciones.o
	g++ -Wall -o tarea5 main.o funciones.o

main.o: main.cpp funciones.h
	g++ -Wall -c main.cpp

funciones.o: funciones.cpp
	g++ -Wall -c funciones.cpp

clean:
	rm *.o tarea5