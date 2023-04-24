# default target
all: ex6

# main executable
ex6: ex6.o Vector.o
	g++ -Wall -g -std=c++17 -o ex6 ex6.o Vector.o

# individual source files
Vector.o: Vector.cc Vector.h
	g++ -Wall -g -std=c++17 -c Vector.cc

ex6.o: ex6.cc
	g++ -Wall -g -std=c++17 -c ex6.cc

# phony target - delete built files (including MacOS debug files)
clean:
	rm -rf ex6 *.o *~ *.dSYM