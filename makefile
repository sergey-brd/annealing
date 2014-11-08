annealing: neighborhood.o swap.o smartSwap.o move.o main.o data.o annealing.o location.o smartMove.o assignment.o back.o
	c++ -oannealing neighborhood.o swap.o smartSwap.o move.o main.o data.o annealing.o location.o assignment.o smartMove.o back.o -std=c++11

neighborhood.o: neighborhood.cpp
	c++ -c neighborhood.cpp -std=c++11
swap.o: swap.cpp
	c++ -c swap.cpp -std=c++11
smartSwap.o: smartSwap.cpp
	c++ -c smartSwap.cpp -std=c++11
smartMove.o: smartMove.cpp
	c++ -c smartMove.cpp -std=c++11
move.o: move.cpp
	c++ -c move.cpp -std=c++11
main.o: main.cpp
	c++ -c main.cpp -std=c++11
data.o: data.cpp
	c++ -c data.cpp -std=c++11
annealing.o: annealing.cpp
	c++ -c annealing.cpp -std=c++11
location.o: location.cpp
	c++ -c location.cpp -std=c++11
assignment.o: assignment.cpp
	c++ -c assignment.cpp -std=c++11
back.o: back.cpp
	c++ -c back.cpp -std=c++11
clean:
	rm *.o

