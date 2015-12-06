ising_MC: main.o  ising.o metropolis.o output_methods.o
	g++ -o ising_MC main.o ising.o metropolis.o output_methods.o
main.o: main.cpp ising.h
	g++ -o main.o -c main.cpp
ising.o: ising.cpp ising.h
	g++ -o ising.o -c ising.cpp
metropolis.o: metropolis.cpp ising.h
	g++ -o metropolis.o -c metropolis.cpp
output_methods.o: output_methods.cpp ising.h
	g++ -o output_methods.o -c output_methods.cpp
clean:
	rm main.o ising.o metropolis.o output_methods.o