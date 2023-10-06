#include "ReadaOut.h"

ReadaOut::ReadaOut () {
    //inicializacao
}

void ReadaOut::lerValor () { //retira do arquivo e coloca na memoria (qnd programa abre)
	
    std::fstream fp;
    fp.open("n10k5_B.txt", std::fstream::in);
    

    if (!fp.is_open()) {
        std::cout << "erro ao abrir o arquivo para ler\n";
        return;
    }

    while (!fp.eof()) {
        
        // getline(fp, demanda);
        // fp.ignore(); //caso precise, colocar antes de um getline

        fp >> entregas;
        fp >> veiculos;
		fp >> capacidade;
        fp >> limiteMinEnt;
		fp >> custoVeiculo;

        //for
        // fp >> demanda; //array
        // fp >> custoTerc; //array
        fp.ignore();        
    }
    
    fp.close();

    std::cout << "entregas: " << entregas << "\nVeiculos: " << veiculos << "\nCapacidade: "
    << capacidade << "\nLimiteMinEntregas: " << limiteMinEnt << "\nCustoVeiculo: " << custoVeiculo << "\n";
}