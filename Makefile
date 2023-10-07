#makelist generico
CC = g++
CFLAGS = -Wall -g

main: main.o ReadaOut.o 
	$(CC) $(CFLAGS) -o testeLer main.o ReadaOut.o 

main.o: main.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c main.cpp
 
ReadaOut.o: ReadaOut.h

clean:
	rm  testeLer