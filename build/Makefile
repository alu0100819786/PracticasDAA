OBJECTS = main.o Algoritmo.o Busquedas.o Problema.o
CFLAGS = -c -std=c++17

default: $(OBJECTS)
	g++  $(OBJECTS) -o vrp -g
	mv *.o ../objects
	mv vrp ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp

Algoritmo.o: ../src/Algoritmo.cpp ../includes/Algoritmo.h
	g++ $(CFLAGS) ../src/Algoritmo.cpp

Busquedas.o: ../src/Busquedas.cpp ../includes/Busquedas.h
	g++ $(CFLAGS) ../src/Busquedas.cpp

Problema.o: ../src/Problema.cpp ../includes/Problema.h
	g++ $(CFLAGS) ../src/Problema.cpp



.PHONY: clean
clean:
	rm -rf ../objects/*.o
	rm -rf ../bin/*
	clear