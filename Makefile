#makelist generico
CC = g++
CFLAGS = -Wall -g

Guloso: Guloso.o ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -o testeGuloso Guloso.o ReadaOut.o Veiculo.o

Guloso.o: Guloso.cpp ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -c Guloso.cpp
 
ReadaOut.o: ReadaOut.h
Veiculo.o: Veiculo.h

clean:
	rm  testeGuloso