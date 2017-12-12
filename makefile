CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
main:
	$(CXX) $(CXXFLAGS) -o main *.cpp
clean:
	rm *.o main
