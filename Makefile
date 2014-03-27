CXX=g++
CXXFLAGS=-Wall -g

tests/test :
	$(CXX) $(CXXFLAGS) -I./include ./src/CaloLinks.cc ./src/CrateLinks.cc ./tests/tests.cc -o tests/test
