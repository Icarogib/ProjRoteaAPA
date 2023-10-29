#include "Guloso.h"
#include "VNDtwoopt.h"
#include "VNDswap.h"
#include "VNDVSwap.h"
#include <windows.h>

using namespace std;


/*
int VND(int r, int productTime, Lines lines, int maxTime){
  int k = 1;
  int s = maxTime;
  
  while(k <= r){
    switch(k){
      case 1:
        maxTime = swapHorizontal(lines, maxTime);
        break;
      
      case 2:
        maxTime = reinsertion(productTime, lines, maxTime);
        break;

      case 3:
        maxTime = swapVertical(productTime, lines, maxTime);
        break;
    }
    
    

    if(maxTime < s){
      s = maxTime;
      k = 1;
    }else{
      k++;
      maxTime = s;
    }
    
  }

  return s;
}*/

void Vnd(int r,Guloso gulo, ReadaOut infos, int TempoMinimo, Veiculo *cami, bool ehUmCaminhao, int index ){

  int k = 1;
  int maxTime = TempoMinimo;

  VNDswap swap;
  VNDtwoopt opt;
  VNDVSwap vertical;

  while (k <= r)
  {
    switch (k)
    {
    case 1:
      cout << "SWAP: custo antes " << cami[index].custoCaminho << endl; 
      swap.realizarVND(cami[index].rota,infos.custoij,cami[index],infos.demanda);
      maxTime = cami[index].custoCaminho;
      cout << "SWAP [" << index << "] Max time: " << maxTime << endl;
      break;

    case 2:
      cout << "\n2opt: custo antes " << cami[index].custoCaminho << endl; 
      opt.callVNDTO( infos, cami, ehUmCaminhao, index );
      maxTime = cami[index].custoCaminho;
      cout << "2OPT [" << index << "] Max time: " << maxTime << endl;
    break;  
    
    case 3:
      cout << "\nVSWAPt: custo antes " << cami[index].custoCaminho << endl; 
      vertical.callVNDVswap( infos, cami, ehUmCaminhao, index );
      maxTime = cami[index].custoCaminho;
      cout << "VNDVertical [" << index << "] Max time: " << maxTime << endl;
    break;

    default:
      break;
    }
    
    if (maxTime < TempoMinimo)
    {
      TempoMinimo = maxTime;
      k = 1;
    }else{
      k++;
      maxTime = TempoMinimo;
    }
    


  }



}

void tabelaFinalArq(ReadaOut infos, Veiculo *caminhaoGuloso, bool enableTerceirizacao, vector<int> terceirizados, int custoTotalTerceirizado, const std::string &outputFileName) {
    std::ofstream outputFile(outputFileName); // Abre o arquivo para escrita

    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        return;
    }

    int custoTotal = 0, custoTotalCaminho = 0, custoTotalVeiculo = 0;

    for (int i = 0; i < infos.veiculos; i++) {
        if (caminhaoGuloso[i].rota.size() == 0)
            continue;

        custoTotalCaminho += caminhaoGuloso[i].custoCaminho;

        custoTotalVeiculo += infos.custoVeiculo;
    }

    if (enableTerceirizacao) {
        custoTotal = custoTotalCaminho + custoTotalVeiculo + custoTotalTerceirizado;
        outputFile << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << "\n" << custoTotalTerceirizado << "\n" << endl;

        for (size_t i = 0; i < terceirizados.size(); i++) {
            outputFile << terceirizados[i] << " ";
        }
        outputFile << "\n";
    } else {
        custoTotal = custoTotalCaminho + custoTotalVeiculo;
        outputFile << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << "\n";
    }

    outputFile << "\n" << custoTotalVeiculo / infos.custoVeiculo << std::endl;

    for (int i = 0; i < infos.veiculos; i++) {
        if (caminhaoGuloso[i].rota.size()) {
            for (size_t j = 1; j < caminhaoGuloso[i].rota.size() - 1; j++) {
                if (j > 1) {
                    outputFile << " " << caminhaoGuloso[i].rota[j];
                } else {
                    outputFile << caminhaoGuloso[i].rota[j];
                }
            }
            outputFile << std::endl;
        }
    }

    outputFile.close(); // Fecha o arquivo
}


// void tabelaFinalArq(ReadaOut infos, Veiculo *caminhaoGuloso, const std::string& outputFileName) {
//     std::ofstream outputFile(outputFileName); // Abre o arquivo para escrita

//     if (!outputFile.is_open()) {
//         std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
//         return;
//     }

//     int custoTotal = 0, custoTotalCaminho = 0, custoTotalVeiculo = 0;

//     for (int i = 0; i < infos.veiculos; i++) {
//         if (caminhaoGuloso[i].rota.size() == 0)
//             continue;

//         custoTotalCaminho += caminhaoGuloso[i].custoCaminho;

//         custoTotalVeiculo += infos.custoVeiculo;
//     }

//     custoTotal = custoTotalCaminho + custoTotalVeiculo;

//     // Escreve os valores no arquivo
//     outputFile << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << "\n";
//     outputFile << "\n" << custoTotalVeiculo / infos.custoVeiculo << std::endl;

//     for (int i = 0; i < infos.veiculos; i++) {
//         if (caminhaoGuloso[i].rota.size()) {
//             for (long unsigned int j = 1; j < caminhaoGuloso[i].rota.size() - 1; j++) {
//                 if (j > 1) {
//                     outputFile << " " << caminhaoGuloso[i].rota[j];
//                 } else {
//                     outputFile << caminhaoGuloso[i].rota[j];
//                 }
//             }
//             outputFile << std::endl;
//         }
//     }

//     outputFile.close(); // Fecha o arquivo
// }


void tabelaFinal(ReadaOut infos, Veiculo *caminhaoGuloso,int &menorCustoVND, bool enableTerceirizacao, vector<int> terceirizados, int custoTotalTerceirizado){
    // if(enableTerceirizacao){
    //     cout << custoTotal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << "\n" << custoTotalTerceirizado << "\n" << endl;
    //     for( long unsigned int i = 0; i < terceirizados.size(); i++ ){
    //         cout <<  terceirizados[i] << " ";
    //     }
    // }else
    


    int custototal = 0, custoTotalCaminho = 0 , custoTotalVeiculo =0;
    
    for (int i = 0; i < infos.veiculos; i++){
      if(caminhaoGuloso[i].rota.size() == 0)
        continue;


      custoTotalCaminho += caminhaoGuloso[i].custoCaminho;
      
      custoTotalVeiculo += infos.custoVeiculo;
    }


    if(enableTerceirizacao){
        custototal = custoTotalCaminho + custoTotalVeiculo + custoTotalTerceirizado;
        cout << custototal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo << "\n" << custoTotalTerceirizado << "\n" << endl;
        for( long unsigned int i = 0; i < terceirizados.size(); i++ ){
            cout <<  terceirizados[i] << " ";
        }  
    }
    else{
        custototal = custoTotalCaminho + custoTotalVeiculo;
        cout << custototal << "\n" << custoTotalCaminho << "\n" << custoTotalVeiculo;
    }

    

    cout << "\n\n" << custoTotalVeiculo / infos.custoVeiculo << endl;   //quantidade de veiculos utilizados
    for (int i = 0; i < infos.veiculos; i++){

        if( caminhaoGuloso[i].rota.size() ){
            
            //DEBUGLOSO**
        
            for( long unsigned int j = 1; j < caminhaoGuloso[i].rota.size() - 1; j++ ){
                if (j > 1){
                    cout << " " << caminhaoGuloso[i].rota[j];
                }
                else
                    cout << caminhaoGuloso[i].rota[j] ;
            }
            //DEBUGLOSO**
            cout << endl;
        }
    }

    if (custototal < menorCustoVND)
        menorCustoVND = custototal;
}




int main (){	


  Guloso guloso;
  ReadaOut infos;
  VNDswap susu;
  VNDtwoopt my2opt;
  VNDVSwap swapperV;
  int vndloop, vndloop2;
  float alpha = 0.7;
  bool ehUmCaminhao = true;
  bool enableTerceirizacao = true;
  int menorCustoVND = INT_MAX;
  int custoTotalTerceirizado;
  vector<int> terceirizados;
  
  vndloop = vndloop2 = 20;

  srand(time (0));

  infos.lerValor( "n31k5_A.txt" );

  while(vndloop--){
    terceirizados.clear();
    custoTotalTerceirizado = 0;
    
    Veiculo caminhaoGuloso[ infos.veiculos ];

    guloso.GulosoFunc( infos, caminhaoGuloso, alpha , enableTerceirizacao, terceirizados, custoTotalTerceirizado);

    

    int numeroDeVizinhancas = 3;


    

    for (int i = 0; i < infos.veiculos; i++)
    {
       
      if (caminhaoGuloso[i].rota.size() == 0)
      { //break;
      }else{
          Vnd(numeroDeVizinhancas,guloso, infos, caminhaoGuloso[i].custoCaminho, caminhaoGuloso, ehUmCaminhao, i ); 
      }
      
    }

    cout << "\nApos VND : " << endl;

    tabelaFinal(infos, caminhaoGuloso, menorCustoVND, enableTerceirizacao, terceirizados, custoTotalTerceirizado);

    tabelaFinalArq(infos, caminhaoGuloso, enableTerceirizacao, terceirizados, custoTotalTerceirizado, "resultado"+to_string(vndloop)+".txt");
    
    cout << "\n\n\n\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    //Sleep(300);
  }

    cout << "\nMenor custo apos rodar " << vndloop2 << " vezes o grasp: " << menorCustoVND;
    
    //my2opt.callVNDTO( infos, caminhaoGuloso, false, 1 );

    //swapperV.callVNDVswap( infos, caminhaoGuloso, false, 1 ); // ok

    //susu.realizarVND( caminhaoGuloso[0].rota, infos.custoij, caminhaoGuloso[0], infos.demanda);
    
    //cout << "\ncustocaminho vic 0: " << caminhaoGuloso[0].custoCaminho << endl;

	return 0;
}
