#include "VNDVSwap.h"

bool debugVSp = false;
bool debugMin = false;

VNDVSwap::VNDVSwap() {
    //inicializacao
}

bool funcLoopVSwap ( ReadaOut info, Veiculo *caminhao1, Veiculo *caminhao2 ){

    int custoTrocaCaminhao1, custoTrocaCaminhao2;
    int menor1, menor2, melhori, melhorj;
    melhori = melhorj = 0;

    menor1 = caminhao1->custoCaminho;
    menor2 = caminhao2->custoCaminho;

    for (int i = 1; i < caminhao1->rota.size() - 1; i++){
        
        int rota1i = caminhao1->rota[ i-1 ];             // rota i - 1
        int rotai = caminhao1->rota[ i ];                // rota i
        int rotai1 = caminhao1->rota[ i+1 ];             // rota i + 1  (foi feito para evitar segmentation fault)

        int custoRota1i = info.custoij[ rota1i ][ rotai ];    // custo do anterior ao que estamos vendo (i-1 e i)
        int custoRotai1 = info.custoij[ rotai ][ rotai1];     // custo do atual ao proximo  (i e i+1)

        if ( debugVSp ){
            std::cout << "\nCusto i: (i-1) - i [" << rota1i << "][" << rotai << "] = " << custoRota1i << std::endl;
            std::cout << "Custo i: i - (i+1) [" << rotai << "][" << rotai1 << "] = " << custoRotai1 << std::endl;
            std::cout << "\nRota1 [" << i << "]: ";
            std::cout << rotai << std::endl;
        }

        for (int j = 1; j < caminhao2->rota.size() - 1; j++){
            
            int rota1j = caminhao2->rota[ j-1 ];
            int rotaj = caminhao2->rota[ j ];
            int rotaj1 = caminhao2->rota[ j + 1 ];

            int custoRota1j = info.custoij[ rota1j ][ rotaj ];
            int custoRotaj1 = info.custoij[ rotaj ][ rotaj1];

            // calcula o custo se trocar aqueles dois pontos
            custoTrocaCaminhao1 = caminhao1->custoCaminho - custoRota1i - custoRotai1  
                                + info.custoij[rota1i][rotaj] + info.custoij[ rotaj ][ rotai1 ];

            custoTrocaCaminhao2 = caminhao2->custoCaminho - custoRota1j - custoRotaj1 + info.custoij[rota1j][rotai] 
                                + info.custoij[ rotai ][ rotaj1 ];

            if ( debugVSp ){
                std::cout << "\nRota2 [" << j << "]: " << rotaj << std::endl;
                std::cout << "\nCusto j: (j-1) - j [" << rota1j << "][" << rotaj << "] = " << custoRota1j << std::endl;
                std::cout << "Custo j: j - (j+1) [" << rotaj << "][" << rotaj1 << "] = " << custoRotaj1 << std::endl;

                std::cout << "\n1 - Trocando [" << rotai << "] com [" << rotaj << "] - Nova aresta veiculo 1: "
                        << rota1i << " -> " << rotaj << " -> " << rotai1 << "\nCusto: "
                        << rota1i << " -> " << rotaj << " = " << info.custoij[rota1i][rotaj] 
                        << "\t e Custo: " << rotaj << " -> " << rotai1 << " = " << info.custoij[ rotaj ][ rotai1 ] 
                        << std::endl;

                std::cout << "\n2 - Trocando [" << rotaj << "] com [" << rotai << "] - Nova aresta veiculo 2: "
                        << rota1j << " -> " << rotai << " -> " << rotaj1 << "\nCusto: "
                        << rota1j << " -> " << rotai << " = " << info.custoij[rota1j][rotai] 
                        << "\t e Custo: " << rotai << " -> " << rotaj1 << " = " << info.custoij[ rotai ][ rotaj1 ] 
                        << std::endl;

                        std::cout << "\nCalculos Caminhao 1: " << caminhao1->custoCaminho << 
                        " - " << custoRota1i << " - " << custoRotai1 << 
                        " + " << info.custoij[rota1i][rotaj]  << 
                        " + " << info.custoij[ rotaj ][ rotai1 ] << " = " << custoTrocaCaminhao1
                              << std::endl;

                        std::cout << "\nCalculos Caminhao 2: " << caminhao2->custoCaminho << 
                        " - " << custoRota1j << " - " << custoRotaj1 << 
                        " + " << info.custoij[rota1j][rotai]  <<
                        " + " << info.custoij[ rotai ][ rotaj1 ] << " = " << custoTrocaCaminhao2 <<
                        "\n====================================" << std::endl;
            }
        
            //IMPLEMENTAR LOGICA PRA GUARDAR OS MENORES.
            
            if ( caminhao1->custoCaminho > custoTrocaCaminhao1 && caminhao2->custoCaminho > custoTrocaCaminhao2 ){
                
                melhori = i; // melhor i da rota
                melhorj = j;
                
                menor1 = custoTrocaCaminhao1;
                menor2 = custoTrocaCaminhao2;

                if (debugVSp){
                    std::cout << "\nAchei um melhor: [" << i << "][" << j << "]" << "\nCusto anterior V1: "<< caminhao1->custoCaminho
                              << " e V2: " << caminhao2->custoCaminho << "\nCusto novo V1: " 
                              << custoTrocaCaminhao1 << " e V2: " << custoTrocaCaminhao2 
                              << std::endl;
                }
            }

        }
    }
    
    if ( melhori && melhorj ){
        if(debugMin){
            std::cout << "\n=============== melhor =====================" << "\nAchei um melhor: [" << melhori << "][" << melhorj 
                << "]" << "\nCusto anterior V1: "<< caminhao1->custoCaminho
                << " e V2: " << caminhao2->custoCaminho << "\nCusto novo V1: " 
                << menor1 << " e V2: " << menor2 
                << std::endl;
            std::cout << "\nRota antes: \nV1: ";
            for (const auto& element : caminhao1->rota) {
                std::cout << element << " ";
            }
            std::cout << "\nV2: ";
            for (const auto& element : caminhao2->rota) {
                std::cout << element << " ";
            }
        }

        int aux = caminhao1->rota[melhori];

        caminhao1->custoCaminho = menor1;
        caminhao2->custoCaminho = menor2;
        caminhao1->rota[melhori] = caminhao2->rota[melhorj];
        caminhao2->rota[melhorj] = aux;

        if(debugMin){
            std::cout << "\nRota nova: \nV1: ";
            for (const auto& element : caminhao1->rota) {
                std::cout << element << " ";
            }
            std::cout << "\nV2: ";
            for (const auto& element : caminhao2->rota) {
                std::cout << element << " ";
            }
            std::cout << "\n==================== Fimmelhor =================\n";
        }
        return true;
    }
        
    return false;
}

void funcLoopVeiculos ( ReadaOut info, Veiculo *veiculo ) {
    bool melhorou = false;
    //recursividade? eh possivel?
    for ( int vic1 = 0; vic1 < info.veiculos; vic1++ ){
        
        if(debugMin)
            std::cout << "\n";

        if(!veiculo[vic1].rota.size())
            break;

        for ( int vic2 = vic1 + 1; vic2 < info.veiculos; vic2++ ){

            if( !veiculo[vic2].rota.size() )
                break;

            if(debugMin){
                std::cout << "\n\nCaminhoes: [" << vic1+1 << "][" << vic2+1 << "]";
            }

            melhorou = funcLoopVSwap ( info, &veiculo[vic1], &veiculo[vic2] );

            if (melhorou){
                std::cout << "\nTrocando rotas entre veiculos [" << vic1 << "] e [" << vic2 << "]" << std::endl;
            }
        }
    }
}

void VNDVSwap::callVNDVswap ( ReadaOut info, Veiculo *veiculos ){
    int pior, menospior;

    funcLoopVeiculos ( info, veiculos );
    
}