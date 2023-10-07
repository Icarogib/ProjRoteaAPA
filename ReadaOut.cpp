#include "ReadaOut.h"

ReadaOut::ReadaOut () {
        int entregas = 0;   // numero de entregas
        int veiculos = 0;   // n de veiculos disponiveis
        int capacidade = 0; // capacidade de cada veiculo
        int limiteMinEnt = 0; // limite minimo de entregas antes de tercerizar
        int custoVeiculo = 0; // preco por usar um veiculo
        
}

void ReadaOut::lerValor () { //retira do arquivo e coloca na memoria (qnd programa abre)
	
    int i, j, tmpEntregas, tmpVeiculos, tmpCapacidade, tmpLimiteMinEnt, tmpCustoVeiculo;
    //std::vector<int> demanda, custoTerc;
    std::ifstream fp("n10k5_B.txt");
    

    if (!fp.is_open()) {
        std::cout << "erro ao abrir o arquivo para ler\n";
        return;
    }

    while (!fp.eof()) {
        
        // getline(fp, demanda);
        // fp.ignore(); //caso precise, colocar antes de um getline

        fp >> tmpEntregas;
        fp >> tmpVeiculos;
		fp >> tmpCapacidade;
        fp >> tmpLimiteMinEnt;
		fp >> tmpCustoVeiculo;

        int tmp;
        for ( i = 0; i < tmpEntregas-1; i++ ){
            fp >> tmp;
            demanda.push_back(tmp);
        }
        
        for ( i = 0; i < tmpEntregas-1; i++ ){
            fp >> tmp;
            custoTerc.push_back(tmp);
        }

        std::vector<int> matrizTemp;
    
        int coluna, linha, arraytemp[tmpEntregas][tmpEntregas];
        coluna = tmpEntregas;
        linha = tmpEntregas;
        std::cout << "ent: " << tmpEntregas << std::endl << "\nlinha: " << linha << "\nent: " << coluna << std::endl;
        // for ( i = 0; i < tmpEntregas; i++ ){
        //     for ( j = 0; i < tmpEntregas; j++ ){
        //         fp >> tmp;
        //         arraytemp[i][j] = tmp;
        //         //matrizTemp.push_back(tmp);
        //     }
        //     //custoij.push_back(matrizTemp);
        // }
    // for ( i = 0; i < tmpEntregas; i++ ){
    //     for ( j = 0; i < tmpEntregas; j++ ){
    //         std::cout << "MatrizCusto [" << i << "] [ " << j << " = " << arraytemp[i][j] << std::endl;
    //     }
    // }
        fp.ignore();  
        std::cout << "tmpEntregas: " << tmpEntregas << "\nVeiculos: " << tmpVeiculos << "\nCapacidade: "
        << tmpCapacidade << "\nLimiteMinEntregas: " << tmpLimiteMinEnt << "\nCustoVeiculo: " << tmpCustoVeiculo << "\n";

        break;
    }
    
    
    fp.close();

    //debug dados iniciais
    std::cout << "Entregas: " << entregas << "\nVeiculos: " << veiculos << "\nCapacidade: "
    << capacidade << "\nLimiteMinEntregas: " << limiteMinEnt << "\nCustoVeiculo: " << custoVeiculo << "\n";

    //debug array (vector) demandas por ponto -1
    for ( i = 0; i < tmpEntregas - 1 ; i++ ){
            std::cout << "demanda [" << i << "] = " << demanda[i] << std::endl;
    }
    //debug array (vector) custo da tercerizacao
    for ( i = 0; i < tmpEntregas - 1 ; i++ ){
            std::cout << "custoTerc [" << i << "] = " << custoTerc[i] << std::endl;
    }
    //debug array (vector) custo da tercerizacao
    // for ( i = 0; i < tmpEntregas-1; i++ ){
    //     for ( j = 0; i < tmpEntregas-1; j++ ){
    //         std::cout << "MatrizCusto [" << i << "] [ " << j << " = " << custoij[i][j] << std::endl;
    //     }
    // }
}