#include "VNDtwoopt.h"
#include "Veiculo.h"

VNDtwoopt::VNDtwoopt() {
    //inicializacao
}

void VNDtwoopt::callVNDTO ( ReadaOut info, Veiculo *caminhao ){

    int i, j;
    caminhao[0].rota.insert(caminhao[0].rota.begin(), 0);
    caminhao[0].rota.insert(caminhao[0].rota.end(), 0);

    if ( caminhao[0].rota.size() < 4 ){
        std::cout << "rota nao pode ser utilizada, pois eh menor que 4!" << std::endl;
        return;
    }

    // OBS TA TODO CAGADO, NINGUEM MEXE, DEPOIS VOU AJEITAR!!


    for (i = 0; i < caminhao[0].rota.size(); i++){ // menos 2 pq: +2 por possuir 2 0s a mais, 
                                                        // e - 4 por utilizarmos cortes de tamanho 4, logo: 2 - 4 = -2

        for (j = i + 4; j < caminhao[0].rota.size() - 2; j++){
            //pensar depois em como fazer certo
            std::cout << "[" << i << "][" << j << "] ---- ARCO: " << caminhao[0].rota[i] << " - " << caminhao[0].rota[j] << std::endl;
        }
    }
    

}