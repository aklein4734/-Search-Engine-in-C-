# default target
all: ex7

# main executable
ex7: ex7.o Vector.o
	g++ -Wall -g -std=c++17 -o ex7 ex7.o Vector.o

# individual source files
Vector.o: Vector.cc Vector.h
	g++ -Wall -g -std=c++17 -c Vector.cc

ex7.o: ex7.cc
	g++ -Wall -g -std=c++17 -c ex7.cc

# phony target - delete built files (including MacOS debug files)
clean:
	rm -rf ex7 *.o *~ *.dSYM