CC = g++
CFLAGS = -Wall -g

all: main teste01 ThirdParty testeVNDListAdj 

main: main.o ReadaOut.o Veiculo.o Guloso.o
	$(CC) $(CFLAGS) -o testemain main.o ReadaOut.o Veiculo.o Guloso.o

main.o: main.cpp ReadaOut.h Veiculo.h Guloso.h
	$(CC) $(CFLAGS) -c main.cpp

ThirdParty: ThirdParty.o ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -o testeThirdParty ThirdParty.o ReadaOut.o Veiculo.o

ThirdParty.o: ThirdParty.cpp ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -c ThirdParty.cpp

teste01: teste01.o ReadaOut.o 
	$(CC) $(CFLAGS) -o teste01 teste01.o ReadaOut.o 

teste01.o: teste01.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c teste01.cpp

testeVNDListAdj: testeVNDListAdj.o ReadaOut.o 
	$(CC) $(CFLAGS) -o testeVNDListAdj testeVNDListAdj.o ReadaOut.o 

testeVNDListAdj.o: testeVNDListAdj.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c testeVNDListAdj.cpp 

ReadaOut.o: ReadaOut.h
Veiculo.o: Veiculo.h
Guloso.o: Guloso.h

