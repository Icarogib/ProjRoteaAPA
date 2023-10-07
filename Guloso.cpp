#include "ReadaOut.h"

using namespace std;

int main (){	
    ReadaOut infos;
    int vic, i, j, caminhoAtual, atual, custoAtual, menorcusto;
    infos.lerValor();

    //cout << "MatrizCusto [" << i << "] [" << j << "] = " << infos.custoij[i][j] << endl;
    atual = custoAtual = 0;
	menorcusto = infos.maiorCusto;

    cout << "Maior Custo: " << menorcusto << endl;

    for (vic = 0; vic < infos.veiculos; vic++){
        
        caminhoAtual = 0; // declara q cada veiculo comeca do 0

        for( j = 0; j < infos.entregas; j++ ){

            custoAtual = infos.custoij[caminhoAtual][j];
            
            if( custoAtual && custoAtual < menorcusto ){
                menorcusto = custoAtual;
                caminhoAtual = j;
            }
        }
    }
    
    return 0;
}
