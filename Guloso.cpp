#include "ReadaOut.h"

using namespace std;

int main (){	
    ReadaOut infos;
    int vic, i, j, caminhoAtual, atual, custoAtual, menorcusto, caminhoProx;
    vector<int> passou;
    infos.lerValor();

    atual = custoAtual = 0;

    //cout << "Maior Custo: " << menorcusto << endl;

    //for (vic = 0; vic < infos.veiculos; vic++){
        
    i = caminhoAtual = 0; // declara q cada veiculo comeca do 0
    do{
	
        menorcusto = infos.maiorCusto;  // inicializa que o menor custo eh o maior

        if( i != 0 )
            caminhoAtual = caminhoProx;

        for( j = 0; j < infos.entregas; j++ ){

            custoAtual = infos.custoij[caminhoAtual][j];
            
            if( custoAtual && custoAtual < menorcusto ){
                menorcusto = custoAtual;
                caminhoProx = j;
            }
        }
        cout << "menorcusto: " << menorcusto << "\ncaminhoprox: " << caminhoProx << endl ;
    
    }while(i++ != 20);

    
    return 0;
}
