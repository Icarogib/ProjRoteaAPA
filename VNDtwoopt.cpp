#include "VNDtwoopt.h"
#include "Veiculo.h"

bool debugTO = true;

VNDtwoopt::VNDtwoopt() {
    //inicializacao
}

void VNDtwoopt::callVNDTO ( ReadaOut info, Veiculo *caminhao ){

    long unsigned int i, j;
    int menorCusto, custoSolucaoMod, auxI, auxJ;
    
    if ( caminhao[0].rota.size() < 4 ){
        std::cout << "\nrota nao pode ser utilizada, pois eh menor que 4!" << std::endl;
        return;
    }

    // OBS TA TODO CAGADO, NINGUEM MEXE, DEPOIS VOU AJEITAR!!
    if (debugTO){

        std::cout << "\n ========== INICIO VNDTWOOPT! ========== \n\nElementos rota: ";
        for (const auto& element : caminhao[0].rota) {
            std::cout << element << " ";
        }

        std::cout << "\nElementos custos rota: ";
        for (const auto& element : caminhao[0].custoRota) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    menorCusto = caminhao[0].custoCaminho;
    
    for (i = 0; i < caminhao[0].rota.size() - 5 ; i++){ // menos 5 pq: esse algoritmo nao pode passar do limite da rota,
                                                        // ja que tem sempre uma diferenca de 5 (numeros entre o primeiro e o quinto)
                                                        // 5 - 1 = 4; comecamos com 4 e expandimos
        for (j = i + 4; j < caminhao[0].rota.size() - 1; j++){
            std::cout << "\n =====> Troca numero: " << j - 3 << std::endl;
            //pensar depois em como fazer certo

            int custoTroca1, custoTroca2;

            custoTroca1 = info.custoij[caminhao[0].rota[i]][caminhao[0].rota[j]];
            custoTroca2 = info.custoij[caminhao[0].rota[i+1]][caminhao[0].rota[j+1]];

            custoSolucaoMod = caminhao[0].custoCaminho - caminhao[0].custoRota[i] - caminhao[0].custoRota[j] + custoTroca1 + custoTroca2;
            
            if( menorCusto > custoSolucaoMod ){
                menorCusto = custoSolucaoMod;
                auxI = i + 1;
                auxJ = j;
            }

            if (debugTO){
                std::cout << "\nInicio: ";
                std::cout << "[" << i << "][" << i+1 << "] ---- ARCO: " << caminhao[0].rota[i] << " - " << caminhao[0].rota[i+1] << " -> Custo: " << caminhao[0].custoRota[i] << std::endl;
                std::cout << "\t[" << j << "][" << j+1 << "] ---- ARCO: " << caminhao[0].rota[j] << " - " << caminhao[0].rota[j+1] << " -> Custo: " << caminhao[0].custoRota[j] << std::endl;

                std::cout << "\nTrocando arcos:\n";
                std::cout << "\t[" << i << "][" << j << "] ---- ARCO: " << caminhao[0].rota[i] << " - " << caminhao[0].rota[j] << " -> Custo: " << info.custoij[caminhao[0].rota[i]][caminhao[0].rota[j]] << std::endl;
                std::cout << "\t[" << i+1 << "][" << j+1 << "] ---- ARCO: " << caminhao[0].rota[i+1] << " - " << caminhao[0].rota[j+1] << " -> Custo: " << info.custoij[caminhao[0].rota[i+1]][caminhao[0].rota[j+1]] << std::endl;

                std::cout << "\nCalculos: " << caminhao[0].custoCaminho << " - " << caminhao[0].custoRota[i] << " - "
                << caminhao[0].custoRota[j] << " + " << custoTroca1 << " + " << custoTroca2  << " = " << custoSolucaoMod << std::endl;
            }

        }
        if (debugTO)
            std::cout << "\n===========================================" << std::endl;
    }
    if (debugTO){
        std::cout << "\n\nFINAL!!!\n\nO custo era: " << caminhao[0].custoCaminho << "\nPassou a ser: " << menorCusto 
        << "\nTrocando as rotas: " << caminhao[0].rota[auxI] << " e " << caminhao[0].rota[auxJ] << " de lugar." << std::endl;

    }
}