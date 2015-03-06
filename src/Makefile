CXX = g++
FLAGS = -std=c++98 -Wall -g

test : test.o BitSet.o
	$(CXX) $(FLAGS) -o test test.o BitSet.o

test.o : test.cpp BitSet.hpp
	$(CXX) $(FLAGS) -c test.cpp

BitSet.o: BitSet.cpp BitSet.hpp
	$(CXX) $(FLAGS) -c BitSet.cpp

clean :
	rm -f test test.o BitSet.o BitSet.lo
	
