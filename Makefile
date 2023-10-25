CC = g++
CFLAGS = -Wall -g

# all: main teste01 ThirdParty testeVNDListAdj

# ================     Main     ================

main: main.o ReadaOut.o Veiculo.o Guloso.o VNDtwoopt.o VNDswap.o VNDVSwap.o
	$(CC) $(CFLAGS) -o mainner main.o ReadaOut.o Veiculo.o Guloso.o VNDtwoopt.o VNDswap.o VNDVSwap.o

main.o: main.cpp ReadaOut.h Veiculo.h Guloso.h VNDtwoopt.h VNDswap.h VNDVSwap.h
	$(CC) $(CFLAGS) -c main.cpp

# ================ Terceirizacao ================

# ThirdParty: ThirdParty.o ReadaOut.o Veiculo.o
# 	$(CC) $(CFLAGS) -o testeThirdParty ThirdParty.o ReadaOut.o Veiculo.o

# ThirdParty.o: ThirdParty.cpp ReadaOut.o Veiculo.o
# 	$(CC) $(CFLAGS) -c ThirdParty.cpp

# # ================ PRIM grafo adj ================

# teste01: teste01.o ReadaOut.o 
# 	$(CC) $(CFLAGS) -o teste01 teste01.o ReadaOut.o 

# teste01.o: teste01.cpp ReadaOut.o 
# 	$(CC) $(CFLAGS) -c teste01.cpp

# # ================ PRIM lista adj ================

# testeVNDListAdj: testeVNDListAdj.o ReadaOut.o 
# 	$(CC) $(CFLAGS) -o testeVNDListAdj testeVNDListAdj.o ReadaOut.o 

# testeVNDListAdj.o: testeVNDListAdj.cpp ReadaOut.o 
# 	$(CC) $(CFLAGS) -c testeVNDListAdj.cpp 

ReadaOut.o: ReadaOut.h
Veiculo.o: Veiculo.h
Guloso.o: Guloso.h
VNDtwoopt.o: VNDtwoopt.h
VNDswap.o: VNDswap.h
VNDVSwap.o: VNDVSwap.h