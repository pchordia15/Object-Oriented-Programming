CC = g++
#CFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic -D HASH_TABLE_SIZE=10
LDFLAGS = 

c: client.o clientMain.o
	$(CC) $(LDFLAGS) $^ -o $@ 

clientMain.o: clientMain.cpp client.h
	$(CC) $(CFLAGS) -c $<

client.o: client.cpp client.h 
	$(CC) $(CFLAGS) -c $<

#hash_function.o: hash_function.cpp hash.h
#	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o c
