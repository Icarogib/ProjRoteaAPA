#makelist generico
CC = g++
CFLAGS = #-Wall -g

main: main.o ReadaOut.o 
	$(CC) $(CFLAGS) -o main main.o ReadaOut.o #CRUD.o

main.o: main.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c main.cpp
 
Produto.o: Produto.h
ReadaOut.o: ReadaOut.h
 
#CRUD.o: CRUD.h Point.h

clean:
	rm  NomePrograma