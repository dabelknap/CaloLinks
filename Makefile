CXX=g++
CXXFLAGS=-Wall -g

tests/test : ./src/*.cc ./include/*.h
	$(CXX) $(CXXFLAGS) -I./include ./src/CaloLinks.cc ./src/CrateLinks.cc ./tests/tests.cc -o tests/test
