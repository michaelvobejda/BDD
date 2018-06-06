CXXFLAGS = -std=c++14 -Wall -Werror -Wpedantic -Ofast -g
CXX = g++

OBJECTS = BDD.o

default: run-tests

run-tests: RunTests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

RunTests.o: RunTests.cpp BDD.hpp

BDD.o: BDD.cpp BDD.hpp

clean:
	rm -f run-tests explore *.o *~


