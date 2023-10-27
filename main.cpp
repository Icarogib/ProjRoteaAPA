#include "Guloso.h"
#include "VNDtwoopt.h"
#include "VNDswap.h"
#include "VNDVSwap.h"

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




int main (){	


  Guloso guloso;
  ReadaOut infos;
  VNDswap susu;
  VNDtwoopt my2opt;
  VNDVSwap swapperV;

  bool ehUmCaminhao = true;


  infos.lerValor( "n31k5_A.txt" );
  Veiculo caminhaoGuloso[ infos.veiculos ];

  guloso.GulosoFunc( infos, caminhaoGuloso );


  int numeroDeVizinhancas = 3;
  for (int i = 0; i < infos.veiculos; i++)
  {
    if (caminhaoGuloso[i].rota.size() == 0)
    { //break;
    }else{
        Vnd(numeroDeVizinhancas,guloso, infos, caminhaoGuloso[i].custoCaminho, caminhaoGuloso, ehUmCaminhao, i ); 
    }
  }
  
  //my2opt.callVNDTO( infos, caminhaoGuloso, false, 1 );

  //swapperV.callVNDVswap( infos, caminhaoGuloso, false, 1 ); // ok

  //susu.realizarVND( caminhaoGuloso[0].rota, infos.custoij, caminhaoGuloso[0], infos.demanda);
  
  //cout << "\ncustocaminho vic 0: " << caminhaoGuloso[0].custoCaminho << endl;

	return 0;
}
