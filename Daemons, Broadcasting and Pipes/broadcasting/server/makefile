CXX = g++

udpechoserver: udpserver.o Dmain.o
	$(CXX) -o udpechoserver udpserver.o Dmain.o

Dmain.o: Dmain.cpp udpserver.h

udpserver.o: udpserver.cpp udpserver.h

clean:
	rm -f *.o udpechoserver
