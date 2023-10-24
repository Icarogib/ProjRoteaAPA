CC = g++
CFLAGS = -Wall -g

all: main teste01 ThirdParty testeVNDListAdj

# ================     Main     ================

main: main.o ReadaOut.o Veiculo.o Guloso.o VNDtwoopt.o VNDswap.o
	$(CC) $(CFLAGS) -o testemain main.o ReadaOut.o Veiculo.o Guloso.o VNDtwoopt.o VNDswap.o

main.o: main.cpp ReadaOut.h Veiculo.h Guloso.h VNDtwoopt.h VNDswap.h
	$(CC) $(CFLAGS) -c main.cpp

# ================ Terceirizacao ================

ThirdParty: ThirdParty.o ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -o testeThirdParty ThirdParty.o ReadaOut.o Veiculo.o

ThirdParty.o: ThirdParty.cpp ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -c ThirdParty.cpp

# ================ PRIM grafo adj ================

teste01: teste01.o ReadaOut.o 
	$(CC) $(CFLAGS) -o teste01 teste01.o ReadaOut.o 

teste01.o: teste01.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c teste01.cpp

# ================ PRIM lista adj ================

testeVNDListAdj: testeVNDListAdj.o ReadaOut.o 
	$(CC) $(CFLAGS) -o testeVNDListAdj testeVNDListAdj.o ReadaOut.o 

testeVNDListAdj.o: testeVNDListAdj.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c testeVNDListAdj.cpp 

# ================ VND Two Opt ================

VNDtwoopt: VNDtwoopt.o ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -o testeVNDtwoopt VNDtwoopt.o ReadaOut.o Veiculo.o

VNDtwoopt.o: VNDtwoopt.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c VNDtwoopt.cpp 

# ================ VND Swap ================

VNDswap: VNDswap.o ReadaOut.o Veiculo.o
	$(CC) $(CFLAGS) -o testeVNDswap VNDswap.o ReadaOut.o Veiculo.o

VNDswap.o: VNDswap.cpp ReadaOut.o 
	$(CC) $(CFLAGS) -c VNDswap.cpp 


ReadaOut.o: ReadaOut.h
Veiculo.o: Veiculo.h
Guloso.o: Guloso.h
VNDtwoopt.o: VNDtwoopt.h
VNDswap.o: VNDswap.h

