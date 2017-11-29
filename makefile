CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
main: unionFind.o splayTree.o eulerTourTree.o linkCutTree.o fullDynamic.o main.o
	$(CXX) $(CXXFLAGS) $? -o $@

clean:
	rm -f main unionFind.o splayTree.o eulerTourTree.o linkCutTree.o fullDynamic.o main.o
