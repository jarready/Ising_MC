ising_MC: main.o  ising.o metropolis.o swendsen_wang.o wolff.o worm.o output_methods.o
	g++ -o ising_MC main.o ising.o metropolis.o swendsen_wang.o wolff.o worm.o output_methods.o -g
main.o: main.cpp ising.h
	g++ -o main.o -c main.cpp
ising.o: ising.cpp ising.h
	g++ -o ising.o -c ising.cpp
metropolis.o: metropolis.cpp ising.h
	g++ -o metropolis.o -c metropolis.cpp
swendsen_wang.o: swendsen_wang.cpp ising.h
	g++ -o swendsen_wang.o -c swendsen_wang.cpp
wolff.o: wolff.cpp ising.h
	g++ -o wolff.o -c wolff.cpp
worm.o: worm.cpp ising.h
	g++ -o worm.o -c worm.cpp
output_methods.o: output_methods.cpp ising.h
	g++ -o output_methods.o -c output_methods.cpp
clean:
	clean main.o ising.o metropolis.o swendsen_wang.o wolff.o worm.o