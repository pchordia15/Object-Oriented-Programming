CXX = g++

daytimeclient: Client.o main.o
	$(CXX) -o daytimeclient Client.o main.o

main.o: main.cpp Client.h

Client.o: Client.cpp Client.h

clean:
	rm -f *.o daytimeclient
