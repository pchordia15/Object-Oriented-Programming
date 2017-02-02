CC = g++
#CFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

s: server.o mainServer.o
	$(CC) $(LDFLAGS) $^ -o $@ 

mainServer.o: mainServer.cpp server.h
	$(CC) $(CFLAGS) -c $<

server.o: server.cpp server.h 
	$(CC) $(CFLAGS) -c $<

#hash_function.o: hash_function.cpp hash.h
#	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o s
