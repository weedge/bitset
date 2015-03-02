cc = g++
FLAGS = -std=c++98 -Wall -g

test : test.o BitSet.o
	$(cc) $(FLAGS) -o test test.o BitSet.o

test.o : test.cpp BitSet.hpp
	$(cc) $(FLAGS) -c test.cpp

BitSet.o: BitSet.cpp BitSet.hpp
	$(cc) $(FLAGS) -c BitSet.cpp

clean :
	rm -f test test.o BitSet.o BitSet.lo
	
