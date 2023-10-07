#makelist generico
CC = g++
CFLAGS = -Wall -g

Guloso: Guloso.o ReadaOut.o
	$(CC) $(CFLAGS) -o testeguloso Guloso.o ReadaOut.o

Guloso.o: Guloso.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c Guloso.cpp
 
ReadaOut.o: ReadaOut.h

clean:
	rm  testeGuloso