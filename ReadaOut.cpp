#include "ReadaOut.h"


ReadaOut::ReadaOut () {
    //inicializacao
}

void ReadaOut::lerValor () {    //retira do arquivo e coloca na memoria (qnd programa abre)
	
    int i, j;
    maiorCusto = 0;
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
        
        for ( i = 0 ; i < entregas - 1 ; i++ ){
            fp >> tmp;  // manda do arquivo para temporario
            
            demanda.push_back(tmp); // manda para o vector demanda | acessado por demanda[i]
        }
        

        for ( i = 0 ; i < entregas - 1 ; i++ ){
            fp >> tmp;
            custoTerc.push_back(tmp); // manda para o vector custo da Terceirizacao | acessado por demanda[i]
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

    // //debug dados iniciais
    
    // std::cout << "entregas: " << entregas << "\nVeiculos: " << veiculos << "\nCapacidade: "
    // << capacidade << "\nLimiteMinEntregas: " << limiteMinEnt << "\nCustoVeiculo: " << custoVeiculo << "\n";
    

    // //deug array (vector) demandas por ponto -1
    
    // for ( i = 0; i < entregas - 1 ; i++ ){
    //         std::cout << "demanda [" << i << "] = " << demanda[i] << std::endl;
    // }
    

    // //debug array (vector) custo da tercerizacao
    
    // for ( i = 0; i < entregas - 1 ; i++ ){
    //         std::cout << "custoTerc [" << i << "] = " << custoTerc[i] << std::endl;
    // }
    

    // //debug array (vector) custo da tercerizacao
    
    // for ( i = 0; i < custoij.size() ; i++ ){
    //     for ( j = 0; j < custoij.size(); j++ ){
    //         std::cout << "MatrizCusto [" << i << "] [" << j << "] = " << custoij[i][j] << std::endl;
    //     }
    // }
    
}