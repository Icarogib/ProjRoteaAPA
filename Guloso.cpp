#include "ReadaOut.h"

using namespace std;

int main (){	
    ReadaOut infos; 
    int vic, caminhoAtual, atual, custoAtual, menorcusto, caminhoProx, auxdoJ;
    vector<int> passou;
    vector<int> veiculocaminho;
    infos.lerValor();


    atual = custoAtual = 0;


   
    //cout << "Maior Custo: " << menorcusto << endl;
    
    
    //for (vic = 0; vic < infos.veiculos; vic++){
        
    caminhoAtual = 0; // declara q cada veiculo comeca do 0
    
    for(int i = 0; i<2 ; i++){
	
        menorcusto = infos.maiorCusto;  // inicializa que o menor custo eh o maior

        if( i != 0 )
            caminhoAtual = caminhoProx;

        for( int j = 0; j < infos.custoij.size() ; j++ ){

            custoAtual = infos.custoij[caminhoAtual][j];
            
            if( custoAtual && custoAtual < menorcusto ){
                //veiculo[vic].pushback[j]
                //custoDoCaminho veiculo 
                menorcusto = custoAtual;
                caminhoProx = j;
                auxdoJ = j;
            }
        }
        veiculocaminho.push_back(auxdoJ);  
        atual += custoAtual;
        infos.custoij[caminhoAtual][auxdoJ] = 0;
        infos.custoij[auxdoJ][caminhoAtual] = 0;
        cout << "menorcusto: " << menorcusto << "\ncaminhoprox: " << caminhoProx << endl ;

    }

    for (int i = 0; i<infos.custoij.size(); i++){
        for(int j = 0 ; j< infos.custoij.size(); j++){
            cout << " " << infos.custoij[i][j];
        }
        cout  << endl;
    }
    for(auto& k: veiculocaminho){
        cout << k << " ";
    }
    
    return 0;
}
