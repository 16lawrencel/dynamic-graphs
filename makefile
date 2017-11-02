CXX = g++
CFLAGS = -std=c++0x -Wall
main: unionFind.o splayTree.o eulerTourTree.o linkCutTree.o fullDynamic.o main.o
	$(CXX) $(CFLAGS) $? -o $@

clean:
	rm -f main unionFind.o splayTree.o eulerTourTree.o linkCutTree.o fullDynamic.o main.o

