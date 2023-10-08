#include "ReadaOut.h"

bool debugRead = false;

ReadaOut::ReadaOut () {
    //inicializacao
}

void ReadaOut::lerValor () {    //retira do arquivo e coloca na memoria (qnd programa abre)
    int i, j;

    maiorCusto = maiorDemanda = 0;
    std::ifstream fp("n10k5_B.txt");    //arquivo para abrir
    

    if (!fp.is_open()) {    // verificacao de erro ao abrir arquivo
        std::cout << "erro ao abrir o arquivo para ler\n";
        return;
    }

    
    while (!fp.eof()) { // vai ate o final do arquivo
        fp >> entregas;
        fp >> veiculos;
		fp >> capacidade;
        fp >> limiteMinEnt;
		fp >> custoVeiculo;

        int tmp; //temporario para pegar o valor do arquivo int
        int mDemanda = 0;
        for ( i = 0 ; i < entregas - 1 ; i++ ){
            fp >> tmp;  // manda do arquivo para temporario
            
            if( tmp > maiorDemanda)
                maiorDemanda = tmp;
            
            demanda.push_back(tmp); // manda para o vector demanda | acessado por demanda[i]
        }
        

        for ( i = 0 ; i < entregas - 1 ; i++ ){
            fp >> tmp;
            custoTerc.push_back(tmp); // manda para o vector custo da Terceirizacao | acessado por custoTerc[i]
        }


        for ( i = 0 ; i < entregas ; i++ ){ // percorre a linha i da matriz
            
            std::vector<int> linhaTemp; // faz um vector temporario para cada linha

            for ( j = 0 ; j < entregas ; j++ ){ // percorre a coluna j da matriz
                fp >> tmp;
                
                if( tmp > maiorCusto ) //maior custo 
                    maiorCusto = tmp;

                linhaTemp.push_back(tmp);   // coloca valor por valor dentro de nossa linha

                //std::cout << "MatrizCustoDentro[" << j << "] = " << linhaTemp[j] << std::endl; //debug linha
            }
            custoij.push_back(linhaTemp); // envia a linha i com colunas j para nossa matriz

        }

        fp.ignore();  
        break;
    }
    
    
    fp.close();

    //debug dados iniciais
    if(debugRead){
        std::cout << "*========================= DebugReadFile =========================*"
        << "\n\nEntregas: " << entregas << "\n\nVeiculos: " << veiculos << "\n\nCapacidade: "
        << capacidade << "\n\nLimiteMinEntregas: " << limiteMinEnt << "\n\nCustoVeiculo: " << custoVeiculo << "\n";
    }

    //deug array (vector) demandas por ponto -1
    if(debugRead){
        std::cout << "\nDemanda: " << std::endl;

        for ( i = 0; i < entregas - 1 ; i++ ){
                std::cout << "    [" << i+1 << "] = " << demanda[i];
        }
    }

    //debug array (vector) custo da tercerizacao
    if(debugRead){
        std::cout << "\nCustoTerc: " << std::endl;

        for ( i = 0; i < entregas - 1 ; i++ ){
                std::cout << "    [" << i+1 << "] = " << custoTerc[i];
        }
    }

    //debug array (vector) custo da tercerizacao
    
    if(debugRead){
        std::cout << "\n\nMatriz:" << std::endl;

        for (int i = 0; i< custoij.size(); i++){
            for(int j = 0 ; j< custoij.size(); j++){
                std::cout << " " << custoij[i][j];
            }
            std::cout  << std::endl;
        }
        std::cout << "\n*========================= END DebugReadFile =========================*" << std::endl;
    }
    
}