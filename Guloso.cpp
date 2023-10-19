#include "Veiculo.h"

bool debugloso = false;
bool enableTerceirizacao = true;

using namespace std;

//OBS: Ignorar funcoes (DEBUGLOSO**)

//problemas a resolver:

// Organizar e nao deixar passar de 4 camadas.
// Testar a fundo a terceirizacao, ver se ela deixa alguem com demanda no fim.

int main (){	
    ReadaOut infos;
    
    int vic, caminhoAtual, custoAtual, custoTotal, custoTotalCaminho, custoTotalVeiculo, custoTotalTerceirizado,
    menorcusto, caminhoProx, cargaTotal, demandaJ, demandaEntregue, menorDemanda, custoTerceirizar, entregaVeiculo, maiorDemanda;
    
    long unsigned int entregasFeitas;
    vector<int> terceirizados;
    
    // inicializando com 0
    custoTotal = custoTotalVeiculo = custoTotalCaminho = custoTotalTerceirizado = entregasFeitas = entregaVeiculo  = 0 ;
    
    infos.lerValor();                                                    // recupera valores do arquivo

    Veiculo veiculo[infos.veiculos];                                     // cria frota de veiculos

    menorDemanda = infos.menorDemanda;                                   // inicializa menorDemanda, apenas para a primeira vez do while
    maiorDemanda = infos.maiorDemanda;

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
             menorDemanda = maiorDemanda;                                  
             maiorDemanda = 0;
             
                                               
            if( veiculo[vic].carga != cargaTotal )                           // se nao houve entrega, comecar do 0
                caminhoAtual = caminhoProx;                                  // atualiza o fixo quando há entrega
            

                            //DEBUGLOSO**
            if(debugloso)
                cout << "\nVerificando melhor a partir de [" << caminhoAtual << "]:" << endl;

            bool terc1 = false;
            
            // Loop menor custo mais proximo a partir do ponto que foi entregue
            for( long unsigned int j = 1; j < infos.custoij.size() ; j++ ){     // ponto de partida fixo
                                                                                // passamos por todas as possibilidades
                // recupera o custos de ida de um ponto ao outro                 
                custoAtual = infos.custoij[caminhoAtual][j];
                
                // recupera custos de terceirizacao                    
                custoTerceirizar = infos.custoTerc[j-1];
                
                // recupera a demanda dos pontos que estao sendo passados    
                demandaJ = infos.demanda[j-1];                 

                
                if ( demandaJ > maiorDemanda )
                    maiorDemanda = demandaJ;

                if ( demandaJ && demandaJ < menorDemanda )
                    menorDemanda = demandaJ;
                
                            //DEBUGLOSO**
                if(debugloso){
                    cout <<" [" << caminhoAtual << "][" << j << "] ---> " << custoAtual << endl;
                    if (!demandaJ)
                        cout << "^sem demanda" << endl;
                }


                if(enableTerceirizacao){
                    if ( caminhoAtual && demandaJ && entregaVeiculo >= infos.limiteMinEnt && custoTerceirizar < (custoAtual + infos.custoij[j][0]) ){
                        terc1 = true;
                        custoTotalTerceirizado += custoTerceirizar;
                        
                        if (debugloso)
                            cout << "^terceiriza" << endl;
                        
                        terceirizados.push_back(j);
                        infos.demanda[ j - 1 ] = 0;      // com a carga terceirizada e entregue, zeramos a demanda
                        demandaJ = 0;
                        entregasFeitas++;
                    }
                }

                if( custoAtual && demandaJ && custoAtual < menorcusto && demandaJ <= veiculo[vic].carga ){  // se possuir custo e demanda, se
                                                                                                            // for menor que o menor custo 
                    menorcusto = custoAtual;    // atualiza o menor custo com o valor do custo atual        // anterior e se o veiculo puder
                    caminhoProx = j;            // proximo ponto para fixar                                 // entregar a carga naquele ponto
                    demandaEntregue = demandaJ; // a demanda que foi entregue com o menor custo
                }
                
            }
            if(debugloso)
                cout << "Menor demanda: " << menorDemanda << " - maior demanda: " << maiorDemanda << endl;
            

                            //DEBUGLOSO**
            if(debugloso && !terc1 ){
                cout <<"\n\nMenorCusto [" << caminhoAtual << "][" << caminhoProx << "] com custo: " <<
                menorcusto << "\nCusto Atual da Viagem: " << veiculo[vic].custoCaminho + menorcusto <<
                "\nCarga Atual de: " << veiculo[vic].carga << "\nDemanda Entregue: " << demandaEntregue 
                << "\nDeixando a carga restante: " << veiculo[vic].carga - demandaEntregue << endl;
                cout << "\nCARGA ENTREGUE EM: " << caminhoProx << "\nRemovendo demanda...." << endl;
            }

            if(enableTerceirizacao){
                if( !terc1 ){
                    veiculo[vic].custoCaminho += menorcusto;   // colocar veiculo custo do caminho dele
                    veiculo[vic].carga -= demandaEntregue;     // carga entregue, zerar demanda em [caminhoProx]
                    veiculo[vic].rota.push_back(caminhoProx);  // coloca na rota do veiculo
                    veiculo[vic].custoRota.push_back(menorcusto); 
                    infos.demanda[ caminhoProx - 1 ] = 0;      // com a carga entregue, zeramos a demanda
                    entregasFeitas++;                          // soma de entregas no total de todos os veiculos e terceirizacao
                }
            }else{
                    veiculo[vic].custoCaminho += menorcusto;   // colocar veiculo custo do caminho dele
                    veiculo[vic].carga -= demandaEntregue;     // carga entregue, zerar demanda em [caminhoProx]
                    veiculo[vic].rota.push_back(caminhoProx);  // coloca na rota do veiculo
                    veiculo[vic].custoRota.push_back(menorcusto); 
                    infos.demanda[ caminhoProx - 1 ] = 0;      // com a carga entregue, zeramos a demanda
                    entregasFeitas++;                          // soma de entregas no total de todos os veiculos e terceirizacao
            }
            
            if(enableTerceirizacao){
                entregaVeiculo = entregasFeitas - terceirizados.size();
            }
        }
            
            veiculo[vic].custoCaminho += infos.custoij[caminhoProx][0];     //custo caminho para voltar        
            veiculo[vic].custoRota.push_back(infos.custoij[caminhoProx][0]); 
            custoTotalCaminho += veiculo[vic].custoCaminho;
            custoTotalVeiculo += infos.custoVeiculo;

            if(enableTerceirizacao)
                custoTotal = custoTotalCaminho + custoTotalVeiculo + custoTotalTerceirizado;
            else
                custoTotal = custoTotalCaminho + custoTotalVeiculo;

                            //DEBUGLOSO**
        if(debugloso){
            cout << "\n\n==================== RELATORIO FINAL DA VIAGEM ======================\n" 
            << "\n***** Retornando *****" << "\nCusto de volta [" 
            << caminhoProx << "][0]: " << infos.custoij[caminhoProx][0] << "\nCusto Total da Viagem: "
            << veiculo[vic].custoCaminho << "\nCarga de retorno de: "
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

            cout << "\nCusto de rota por caminho: ";
            for( long unsigned int i = 0; i < veiculo[vic].custoRota.size(); i++ ){
                if (i > 0)
                    cout << " " << veiculo[vic].custoRota[i] ;
                else
                    cout << veiculo[vic].custoRota[i] ;
            }
            
            cout << "\nEntregas Efetuadas: " << entregasFeitas <<
                    "\n\n==================== FIM RELATORIO VIAGEM ======================" << endl;
        }

        // Condicao de Saida
        if( entregasFeitas == (infos.demanda.size()) ){ // se a maior demanda for 0 ou terem entregue todas as demandas 
            break;                                                                              // acabam as entregas
        } 
        
    }

    // ========================================= Apresentacao de Resultados ========================================= //
    if(enableTerceirizacao){
        cout << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << "\n" << custoTotalTerceirizado << "\n" << endl;
        for( long unsigned int i = 0; i < terceirizados.size(); i++ ){
            cout <<  terceirizados[i] << " ";
        }
    }else
        cout << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo;
    

    cout << "\n\n" << custoTotalVeiculo / infos.custoVeiculo << endl;   //quantidade de veiculos utilizados
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
            if(debugloso)
                cout << " - custo da rota: " << veiculo[vic].custoCaminho;
            cout << endl;
        }
    }

    // ========================================= Fim Apresentacao de Result ========================================= //

    return 0;
}
