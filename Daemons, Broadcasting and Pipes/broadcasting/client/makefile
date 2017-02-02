CXX = g++

udpclient: udpclient.o main.o
	$(CXX) -o udpclient udpclient.o main.o

main.o: main.cpp udpclient.h

udpclient.o: udpclient.cpp udpclient.h

clean:
	rm -f *.o udpclient
