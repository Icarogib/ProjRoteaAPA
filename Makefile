#makelist generico
CC = g++
CFLAGS = -Wall -g

main: main.o Produto.o #CRUD.o
	$(CC) $(CFLAGS) -o main main.o Produto.o #CRUD.o

main.o: main.cpp Produto.h #CRUD.h
	$(CC) $(CFLAGS) -c main.cpp
 
Produto.o: Produto.h
 
#CRUD.o: CRUD.h Point.h

clean:
	rm  NomePrograma