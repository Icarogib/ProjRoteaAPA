//logica: se os dois menores custos somados do vertice for menor que o de terceirização, é melhor terceirizar kkkkkkkkkkkk n sei se faz sentido-
#include "ThirdParty.h"
using namespace std;

ThirdParty::ThirdParty(){
    
}

void ThirdParty::thirdParty(){
    ReadaOut infos;
    int menor1, menor2 = INT_MAX;
    int soma = 0;
    vector<int> somas;
    infos.lerValor( "n31k5_A.txt" );

    cout << "Custos de Terceirizacao: ";
    for(auto& i : infos.custoTerc){ // custo terc
        cout << i << " ";
    }
    cout << endl;

    for(int i = 1; i < infos.custoij.size(); i++){
        for(int j = 0; j < infos.custoij.size(); j++){
            if (i == j)
                continue;

            if(infos.custoij[i][j] < menor1){
                menor2 = menor1;
                menor1 = infos.custoij[i][j];
            } else if (infos.custoij[i][j] < menor2){
                menor2 = infos.custoij[i][j];
            }
            //soma += infos.custoij[i][j];
        }
        soma = menor1 + menor2;
        //cout << "menor1 " << menor1 << " menor2 " << menor2 << endl;
        somas.push_back(soma);
        soma = 0;
        menor1 = menor2 = INT_MAX;
    }

    cout << "\nSoma dos dois menores: ";
    for(auto& i : somas){ //soma dos dois menores
        cout << i << " ";
    }
    cout << "\n" << endl;

    for(int i = 0 ; i < infos.custoTerc.size(); i++){
        if (somas[i] > infos.custoTerc[i]){
            cout << "local [" << i+1 << "] " << "tem o custo de entrada e saida maior que o de terceirizar, portanto pode ser melhor terceiriza-lo" << endl;
        }
    }  
}