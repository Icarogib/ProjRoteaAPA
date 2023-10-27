#include "VNDtwoopt.h"

bool debugTO = false;

VNDtwoopt::VNDtwoopt() {
    //inicializacao
}

bool VNDtwoopt::getTeveMelhora(){
    return melhora;
}
void VNDtwoopt::setTeveMelhora(bool m){
    melhora = m;
}

void funcTrocaRota ( Veiculo *caminhao, int auxI, int auxJ ) {
    int j = auxJ;

    for (int i = auxI; i < j ; i++){
        int aux = caminhao->rota[i];
        caminhao->rota[i] = caminhao->rota[j];
        caminhao->rota[j--] = aux;           
    }
}

// funcao que substitui o menor custo, se for menor realmente, e sua posicao.
void funcMenorCusto ( int *menorCusto, int custoSolucaoMod, int *auxI, int *auxJ, int i, int j ){
        
    // o valor da troca eh menor que o menor custo ate agora? se sim, troque para ser o novo menorcusto
    if( *menorCusto > custoSolucaoMod ){
        
        if ( debugTO )
            std::cout << "\nAlterando, pois o custo: " << *menorCusto << " > " << custoSolucaoMod << std::endl;

        *menorCusto = custoSolucaoMod;
        *auxI = i + 1;
        *auxJ = j;
        
    }else if ( debugTO )
        std::cout << "\nTroca nao possui valor menor que o anterior" << std::endl;
}

// funcao que recebe, e altera se necessario a rota de um veiculo especifico
void funcLoopJanela ( ReadaOut info, Veiculo caminhao, int *menorCusto, int *auxI, int *auxJ ) {
    int custoSolucaoMod;

    for ( long unsigned int i = 0; i < caminhao.rota.size() - 5 ; i++){ // menos 5 pq esse algoritmo nao pode passar do limite da rota,
                                                                        // ja que sempre vai existir uma diferenca de 5 (numeros entre o zero(primeiro) e o quinto)
                                                                        // 5 - 1 = 4; comecamos com 4 e expandimos a janela
        if(debugTO)
            std::cout << "\n\nPosicao Janela: [" << i << "]" << std::endl;

        for ( long unsigned int j = i + 4; j < caminhao.rota.size() - 1; j++){

            if ( debugTO )
                std::cout << "\n =========== " << std::endl;

            int custoTroca1, custoTroca2;

            custoTroca1 = info.custoij[caminhao.rota[i]][caminhao.rota[j]];
            custoTroca2 = info.custoij[caminhao.rota[i+1]][caminhao.rota[j+1]];

            custoSolucaoMod = caminhao.custoCaminho - caminhao.custoRota[i] - caminhao.custoRota[j] + custoTroca1 + custoTroca2;
            
            funcMenorCusto ( menorCusto, custoSolucaoMod, auxI, auxJ, i, j );

            if (debugTO){
                std::cout << "\nInicio: ";
                std::cout << "[" << i << "][" << i+1 << "] ---- ARCO: " << caminhao.rota[i] << " - " << caminhao.rota[i+1] << " -> Custo: " << caminhao.custoRota[i] << std::endl;
                std::cout << "\t[" << j << "][" << j+1 << "] ---- ARCO: " << caminhao.rota[j] << " - " << caminhao.rota[j+1] << " -> Custo: " << caminhao.custoRota[j] << std::endl;

                std::cout << "\nTrocando arcos:\n";
                std::cout << "\t[" << i << "][" << j << "] ---- ARCO: " << caminhao.rota[i] << " - " << caminhao.rota[j] << " -> Custo: " << info.custoij[caminhao.rota[i]][caminhao.rota[j]] << std::endl;
                std::cout << "\t[" << i+1 << "][" << j+1 << "] ---- ARCO: " << caminhao.rota[i+1] << " - " << caminhao.rota[j+1] << " -> Custo: " << info.custoij[caminhao.rota[i+1]][caminhao.rota[j+1]] << std::endl;

                std::cout << "\nCalculos: " << caminhao.custoCaminho << " - " << caminhao.custoRota[i] << " - "
                << caminhao.custoRota[j] << " + " << custoTroca1 << " + " << custoTroca2  << " = " << custoSolucaoMod << std::endl;
            }
        }
    }
    if (debugTO)
        std::cout << "\n===========================================\n" << std::endl;
}

// funcao rodara o algoritmo para a quantidade n de  veiculos.
bool funcLoopVeiculo ( ReadaOut info, Veiculo *caminhao ) {
    bool melhorou = false;
    int menorCusto, auxI, auxJ;

    for (int vic = 0; vic < info.veiculos; vic++){
        
        // se nao possuir uma rota maior que o minimo necessario, encerrara
        if ( caminhao[vic].rota.size() < 6 ){
            std::cout << "\nRota do caminhao [" << vic+1 <<  "] nao pode ser utilizada, pois eh menor que o numero minimo!" << 
            "\nLogo, outros caminhoes nao serao capazes de rodar tambem" << std::endl;
            
            if( !caminhao[vic].rota.size() )
                break;

            continue;
        }

        if (debugTO){

            std::cout << "\n ========== INICIO VNDTWOOPT! ========== \n\nElementos rota: ";
            for (const auto& element : caminhao[vic].rota) {
                std::cout << element << " ";
            }

            std::cout << "\nElementos custos rota: ";
            for (const auto& element : caminhao[vic].custoRota) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }

        // o nosso menor custo, eh o custo total da rota do caminhao, se houver um menor, ele sera trocado.
        menorCusto = caminhao[vic].custoCaminho;
        
        // funcao que anda e aumenta a janela, a partir de 4 posicoes para aquele veiculo
        funcLoopJanela ( info, caminhao[vic], &menorCusto, &auxI, &auxJ );
        

        if ( caminhao[vic].custoCaminho == menorCusto ){
            std::cout << "\nNao houve alteracao para o veiculo [" << vic + 1 << "]\n" << "\n===============================" << std::endl;
            //melhorou = false;
        }else{
            std::cout << "\nO custo para o caminhao [" << vic+1 << "] era: " << caminhao[vic].custoCaminho << "\nE agora o custo passou a ser: " << menorCusto 
            << "\n\nTrocando as rotas: [" << auxI << "]=" << caminhao[vic].rota[auxI] << " e [" << auxJ << "]=" << caminhao[vic].rota[auxJ] << " de lugar.\n" 
            << "\n=======================================" << std::endl;
            
            if(debugTO){
                std::cout << "\nantiga rota: ";
                for (const auto& element : caminhao[vic].rota) {
                    std::cout << element << " ";
                }
                std::cout << " - Custo: " << caminhao[vic].custoCaminho << std::endl;
            }
            
            funcTrocaRota ( &caminhao[vic], auxI, auxJ );
            caminhao[vic].custoCaminho = menorCusto;

            if(debugTO){
                std::cout << "\nnova rota:   ";
                for (const auto& element : caminhao[vic].rota) {
                    std::cout << element << " ";
                }
                std::cout << " - Custo: " << caminhao[vic].custoCaminho << std::endl;
            }
                std::cout << "\n========= Fim 2-opt para veiculo [" << vic+1 << "] =========" << std::endl;

            melhorou = true;

        }
    }
    return melhorou;
}

// VND 2-opt
void VNDtwoopt::callVNDTO ( ReadaOut info, Veiculo *caminhao ){

    std::cout << "\n========= Algoritmo VND 2-opt =========" << std::endl;
    
    std::cout << "Melhorou antes: " << getTeveMelhora() << std::endl;

    setTeveMelhora(funcLoopVeiculo ( info, caminhao ));
    
    std::cout << "\nMelhorou depois: " << getTeveMelhora() << std::endl;
}