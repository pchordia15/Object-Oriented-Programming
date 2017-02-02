CXX = g++

daytimeserver: DaytimeServer.o DMain.o
	$(CXX) -o daytimeserver DaytimeServer.o DMain.o

DMain.o: DMain.cpp DaytimeServer.h

DaytimeServer.o: DaytimeServer.cpp DaytimeServer.h

clean:
	rm -f *.o daytimeserver
