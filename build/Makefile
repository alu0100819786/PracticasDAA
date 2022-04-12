OBJECTS = main.o
CFLAGS = -c -std=c++17

default: $(OBJECTS)
	g++  $(OBJECTS) -o vrp -g
	mv *.o ../objects
	mv vrp ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp

#algorithm.o: ../src/algorithm.cpp ../includes/algorithm.h
#	g++ $(CFLAGS) ../src/algorithm.cpp

.PHONY: clean
clean:
	rm -rf ../objects/*.o
	rm -rf ../bin/*
	clear