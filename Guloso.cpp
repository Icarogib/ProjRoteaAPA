#include "Veiculo.h"

bool debugloso = true;

using namespace std;

//problemas a resolver:

// MOSTRAR E SOMAR CALCULOS DE CUSTOS E ROTAS
// FALTA TERCEIRIZACAO

//custo do cabo branco pro farol, do farol pro deposito
//compara com a terceirizacao

int main (){	
    ReadaOut infos;
    
    int vic, caminhoAtual, custoAtual, custoTotal, custoTotalCaminho, custoTotalVeiculo, custoTotalTerceirizado,
    menorcusto, caminhoProx, cargaTotal, demandaJ, demandaEntregue, maiorDemanda, entregasFeitas, custoTerceirizar;

    vector<int> terceirizados;

    // inicializando com 0
    custoTotal = custoTotalTerceirizado = custoTotalVeiculo = custoTotalCaminho = entregasFeitas = 0 ;
    
    infos.lerValor();                                                    // recupera valores do arquivo

    Veiculo veiculo[infos.veiculos];                                     // cria frota de veiculos

    maiorDemanda = infos.maiorDemanda;                                   // inicializa maiorDemanda, apenas para a primeira vez do for

    // Loop para veiculos
    for (vic = 0; vic < infos.veiculos; vic++){                          // percorre enquanto houver veículos disponiveis

        veiculo[vic].carga = cargaTotal = infos.capacidade;              // declara a carga do veiculo, e a capacidade total dele
        veiculo[vic].custoCaminho = caminhoAtual = 0;                    // declara que seu custo esta 0 e cada veiculo comeca do 0
        
        //DEBUG
        if(debugloso)
            cout << "\n\n====================== Veiculo [" << vic+1 << "] ======================" << endl;
    
        // Loop rota do veiculo selecionado
        while( veiculo[vic].carga > 0 && maiorDemanda < veiculo[vic].carga ){ // se o veiculo ainda tiver carga,
            maiorDemanda = 0;                                                 // e for maior do que eh demandado,
            menorcusto = infos.maiorCusto;      // inicializa que o menor custo eh o maior   // enquanto ha demanda

            if( veiculo[vic].carga != cargaTotal )                           // apenas para primeira iteracao
                caminhoAtual = caminhoProx;                                  // atualiza o fixo
            
            //DEBUG
            if(debugloso)
                cout << "\nVerificando melhor a partir de [" << caminhoAtual << "]" << endl;
            
            // Loop menor custo mais proximo
            for( long unsigned int j = 0; j < infos.custoij.size() ; j++ ){     // com o ponto de partida fixo
                                                                                // passamos por todas as possibilidades
                //DEBUG
                if(debugloso)
                    cout <<" [" << caminhoAtual << "][" << j << "] --->";

                custoAtual = infos.custoij[caminhoAtual][j];                   // recupera o custo de ida de um ponto ao outro
                
                if (j){ // nao ha demanda para 0
                    //custoTerceirizar = infos.custoTerc[j-1];                         // recupera o custo de terceirizacao
                    demandaJ = infos.demanda[j-1];                                 // recupera a demanda dos pontos que estao sendo passados 
                }else{
                    //custoTerceirizar = 0;
                    demandaJ = 0;
                }

                if( demandaJ > maiorDemanda )                                  // ve o maior valor de demanda
                    maiorDemanda = demandaJ;

                if( custoAtual && custoAtual < menorcusto && demandaJ <= veiculo[vic].carga && demandaJ != 0){  // se possuir custo e demanda, se
                                                                                                                // for menor que o menor custo 
                    menorcusto = custoAtual;    // atualiza o menor custo com o valor do custo atual            // anterior e se o veiculo puder
                    caminhoProx = j;            // proximo ponto para fixar                                     // entregar a carga naquele ponto
                    demandaEntregue = demandaJ; // a demanda que foi entregue com o menor custo
                }
            }

            //DEBUGLOSO
            if(debugloso){
                cout <<"\n\nMenorCusto [" << caminhoAtual << "][" << caminhoProx << "] com custo: " <<
                menorcusto << "\nCusto Atual da Viagem: " << veiculo[vic].custoCaminho + menorcusto <<
                "\nCarga Atual de: " << veiculo[vic].carga << "\nDemanda Entregue: " << demandaEntregue 
                << "\nDeixando a carga restante: " << veiculo[vic].carga - demandaEntregue << endl;
                cout << "\nCARGA ENTREGUE EM: " << caminhoProx << "\nRemovendo demanda...." << endl;
            }

            veiculo[vic].custoCaminho += menorcusto;   // colocar veiculo custo do caminho dele
            veiculo[vic].carga -= demandaEntregue;     // carga entregue, zerar demanda em [caminhoProx]
            infos.demanda[ caminhoProx - 1 ] = 0;      // com a carga entregue, zeramos a demanda
            veiculo[vic].rota.push_back(caminhoProx);  // coloca na rota do veiculo
            entregasFeitas++;                          // soma de entregas no total de todos os veiculos
        }

        //DEBUGLOSO
        if(debugloso){
            cout << "\n\n==================== RELATORIO FINAL DA VIAGEM ======================\n" 
            << "\n***** Retornando *****" << "\nCusto de volta [" 
            << caminhoProx << "][0]: " << infos.custoij[caminhoProx][0] << "\nCusto Total da Viagem: "
            << veiculo[vic].custoCaminho + infos.custoij[caminhoProx][0] << "\nCarga de retorno de: "
            << veiculo[vic].carga << endl;
        }
        
        veiculo[vic].custoCaminho += infos.custoij[caminhoProx][0]; //custo caminho para voltar
        //veiculo[vic].rota.push_back(0);                             //caminho do veiculo para voltar //comentardps
  
        //DEBUGLOSO
        if(debugloso){
            cout << "\nRota do veiculo: ";
            for( long unsigned int i = 0; i < veiculo[vic].rota.size(); i++ ){
                if (i > 0)
                    cout << " ----->  " << veiculo[vic].rota[i] ;
                else
                    cout << veiculo[vic].rota[i] ;
            }
            cout << "\n\nDemanda passa a ser: " << endl;
            for ( long unsigned int i = 0; i < infos.demanda.size(); i++ ){
                    cout << "    [" << i+1 << "] = " << infos.demanda[i];
            }cout << endl;
            cout << "Valor da maior demanda: " << maiorDemanda << endl;
            cout << "Entregas Efetuadas: " << entregasFeitas << endl;
            cout << "\n==================== FIM RELATORIO VIAGEM ======================" << endl;
        }
        
        custoTotalCaminho += veiculo[vic].custoCaminho;
        custoTotalVeiculo += infos.custoVeiculo;
        //custoTotalTerceirizado += custoTotal;                     // IMPLEMENTAR
        custoTotal = custoTotalCaminho + custoTotalVeiculo;// + custoTotalTerceirizado;


        if(!maiorDemanda || entregasFeitas == (infos.entregas - 1)){ // se a maior demanda for 0 ou terem entregue todas as demandas // acaba as entregas
            break;
        } 
    }

    cout << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << endl; // << custoTotalTerceirizado << //implementar listaterc
    
    for (vic = 0; vic < infos.veiculos; vic++){

        if( veiculo[vic].rota.size() ){
            cout << "\nVeiculo [" << vic+1 << "]: ";
        
            for( long unsigned int i = 0; i < veiculo[vic].rota.size(); i++ ){
                if (i > 0)
                    cout << " " << veiculo[vic].rota[i] ;
                else
                    cout << veiculo[vic].rota[i] ;
            }
            cout << endl;
        }
    }

    return 0;
}
