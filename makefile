all: mehta_p1

mehta_p1: mehta_p1.o
	g++ mehta_p1.o -o mehta_p1

mehta_p1.o: mehta_p1.cpp
	g++ -c mehta_p1.cpp 

clean:
	rm -f *.o mehta_p1