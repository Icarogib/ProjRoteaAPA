#include "Veiculo.h"

bool debugloso = false;

using namespace std;

//problemas a resolver:

// FALTA TERCEIRIZACAO

//obs:
//custo do atual para o proximo, do proximo para o deposito
//compara com a terceirizacao

int main (){	
    ReadaOut infos;
    
    int vic, caminhoAtual, custoAtual, custoTotal, custoTotalCaminho, custoTotalVeiculo,
    menorcusto, caminhoProx, cargaTotal, demandaJ, demandaEntregue, menorDemanda;
    
    long unsigned int entregasFeitas;
    vector<int> terceirizados;
    
    // inicializando com 0
    custoTotal = custoTotalVeiculo = custoTotalCaminho = entregasFeitas = 0 ;
    
    infos.lerValor();                                                    // recupera valores do arquivo

    Veiculo veiculo[infos.veiculos];                                     // cria frota de veiculos

    menorDemanda = infos.menorDemanda;                                   // inicializa menorDemanda, apenas para a primeira vez do while

    // Loop para veiculos
    for (vic = 0; vic < infos.veiculos; vic++){                          // percorre enquanto houver veículos disponiveis

                            //DEBUGLOSO**
        if(debugloso)
            cout << "\n\n====================== Veiculo [" << vic+1 << "] ======================" << endl;


        veiculo[vic].carga = cargaTotal = infos.capacidade;              // declara a carga do veiculo, e a capacidade total dele
        veiculo[vic].custoCaminho = caminhoAtual = 0;                    // declara que seu custo esta 0 e cada veiculo comeca do 0


        // Loop rota do veiculo selecionado
        while( menorDemanda && menorDemanda <= veiculo[vic].carga && entregasFeitas != ( infos.demanda.size() )){
                                                                             // se houver demanda, o veiculo estar carregado
             // inicializa que o menor custo eh o maior                      // com uma carga maior do que eh demandado.
             menorcusto = infos.maiorCusto;                                  
                                               
            if( veiculo[vic].carga != cargaTotal )                           // se nao houve entrega, comecar do 0
                caminhoAtual = caminhoProx;                                  // atualiza o fixo quando há entrega
            

                            //DEBUGLOSO**
            if(debugloso)
                cout << "\nVerificando melhor a partir de [" << caminhoAtual << "]:" << endl;


            // Loop menor custo mais proximo a partir do ponto que foi entregue
            for( long unsigned int j = 0; j < infos.custoij.size() ; j++ ){     // ponto de partida fixo
                                                                                // passamos por todas as possibilidades

                            //DEBUGLOSO**
                if(debugloso)
                    cout <<" [" << caminhoAtual << "][" << j << "] --->";


                custoAtual = infos.custoij[caminhoAtual][j];                    // recupera o custo de ida de um ponto ao outro
                
                if (!j) // nao ha demanda para 0
                    demandaJ = 0;                           
                else
                    demandaJ = infos.demanda[j-1];                             // recupera a demanda dos pontos que estao sendo passados    
                

                if( custoAtual && demandaJ && custoAtual < menorcusto && demandaJ <= veiculo[vic].carga ){  // se possuir custo e demanda, se
                                                                                                            // for menor que o menor custo 
                    menorcusto = custoAtual;    // atualiza o menor custo com o valor do custo atual        // anterior e se o veiculo puder
                    caminhoProx = j;            // proximo ponto para fixar                                 // entregar a carga naquele ponto
                    demandaEntregue = demandaJ; // a demanda que foi entregue com o menor custo
                }
            }
            
                            //DEBUGLOSO**
            if(debugloso){
                cout <<"\n\nMenorCusto [" << caminhoAtual << "][" << caminhoProx << "] com custo: " <<
                menorcusto << "\nCusto Atual da Viagem: " << veiculo[vic].custoCaminho + menorcusto <<
                "\nCarga Atual de: " << veiculo[vic].carga << "\nDemanda Entregue: " << demandaEntregue 
                << "\nDeixando a carga restante: " << veiculo[vic].carga - demandaEntregue << endl;
                cout << "\nCARGA ENTREGUE EM: " << caminhoProx << "\nRemovendo demanda...." << endl;
            }

            veiculo[vic].custoCaminho += menorcusto;   // colocar veiculo custo do caminho dele
            veiculo[vic].carga -= demandaEntregue;     // carga entregue, zerar demanda em [caminhoProx]
            veiculo[vic].rota.push_back(caminhoProx);  // coloca na rota do veiculo
            infos.demanda[ caminhoProx - 1 ] = 0;      // com a carga entregue, zeramos a demanda
            infos.custoTerc[ caminhoProx - 1 ] = 0;    // e tambem a terceirizacao, ja que nao eh necessaria
            entregasFeitas++;                          // soma de entregas no total de todos os veiculos

        }

                            //DEBUGLOSO**
        if(debugloso){
            cout << "\n\n==================== RELATORIO FINAL DA VIAGEM ======================\n" 
            << "\n***** Retornando *****" << "\nCusto de volta [" 
            << caminhoProx << "][0]: " << infos.custoij[caminhoProx][0] << "\nCusto Total da Viagem: "
            << veiculo[vic].custoCaminho + infos.custoij[caminhoProx][0] << "\nCarga de retorno de: "
            << veiculo[vic].carga << endl;

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
            }
            cout << "\nEntregas Efetuadas: " << entregasFeitas <<
                    "\n\n==================== FIM RELATORIO VIAGEM ======================" << endl;
        }
        
        veiculo[vic].custoCaminho += infos.custoij[caminhoProx][0];     //custo caminho para voltar
        
        custoTotalCaminho += veiculo[vic].custoCaminho;
        custoTotalVeiculo += infos.custoVeiculo;
        //custoTotalTerceirizado += custoTotal;                     // IMPLEMENTAR
        custoTotal = custoTotalCaminho + custoTotalVeiculo;// + custoTotalTerceirizado;

        if( entregasFeitas == (infos.demanda.size()) ){ // se a maior demanda for 0 ou terem entregue todas as demandas 
            break;                                                                              // acabam as entregas
        } 

    }

    // ========================================= Apresentacao de Resultados ========================================= //

    cout << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << endl; // << custoTotalTerceirizado << //implementar listaterc
    cout << "\n" << custoTotalVeiculo / infos.custoVeiculo << endl;
    for (vic = 0; vic < infos.veiculos; vic++){

        if( veiculo[vic].rota.size() ){
            
            if(debugloso)
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

    // ========================================= Fim Apresentacao de Result ========================================= //

    return 0;
}

 //terceirizacao para implementar depois!!

/*
                if ( custoTerceirizar && entregasFeitas >= infos.limiteMinEnt && custoTerceirizar < (custoAtual + infos.custoij[j][0]) && caminhoAtual ){
                    cout << "terceiriza [" << caminhoAtual << "][" << j << "]" << endl;
                    terceirizados.push_back(j);
                    infos.demanda[ j - 1 ] = 0;      // com a carga terceirizada e entregue, zeramos a demanda
                    infos.custoTerc[ j - 1 ] = 0;    // e tambem a terceirizacao, ja que nao eh mais necessaria
                    custoTerceirizar = 0;
                    demandaJ = 0;
                }

                //terceirizados.size()
           // if ( !terc2 ){ //alterar

           //custoTerceirizar = infos.custoTerc[j-1];                         // recupera o custo de terceirizacao
           //custoTerceirizar = 0;
           //bool terc1 = false; //custoTotalTerceirizado, custoTerceirizar 
*/
