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

void Vnd(int r,Guloso gulo, ReadaOut infos, int TempoMinimo, Veiculo cami){
  
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
      cout << "custo antes " << cami.custoCaminho << endl; 
      swap.realizarVND(cami.rota,infos.custoij,cami,infos.demanda);
      maxTime = cami.custoCaminho;
      cout << "Max time: " << maxTime << endl;
      break;

    case 2:
      cout << "custo antes " << cami.custoCaminho << endl; 
      //opt.lixo(cami.rota,infos.custoij,cami,infos.demanda);
      maxTime = cami.custoCaminho;
      cout << "Max time: " << maxTime << endl;
    break;  
    
    case 3:
      cout << "custo antes " << cami.custoCaminho << endl; 
      //vertical.lixo2(cami.rota,infos.custoij,cami,infos.demanda);
      maxTime = cami.custoCaminho;
      cout << "Max time: " << maxTime << endl;
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



  infos.lerValor( "n31k5_A.txt" );
  Veiculo caminhaoGuloso[ infos.veiculos ];

  guloso.GulosoFunc( infos, caminhaoGuloso );

/*
  int numeroDeVizinhancas = 3;
  for (int i = 0; i < infos.veiculos; i++)
  {
    if (caminhaoGuloso[i].rota.size() <= 0)
    {
    }else{
        Vnd(numeroDeVizinhancas,guloso, infos, caminhaoGuloso[i].custoCaminho, caminhaoGuloso[i]);
    }
  }
  */
    
  // swapperV.callVNDVswap( infos, caminhaoGuloso ); // ok
cout << "1lixo" << endl;
  for (int vic = 0; vic < infos.veiculos; vic++){

        if( caminhaoGuloso[vic].rota.size() ){
            
                cout << "\nVeiculo [" << vic+1 << "]: ";
        
            for( long unsigned int i = 1; i < caminhaoGuloso[vic].rota.size() - 1; i++ ){
                if (i > 1){
                    cout << " " << caminhaoGuloso[vic].rota[i];
                }
                else
                    cout << caminhaoGuloso[vic].rota[i] ;
            }
                cout << " - custo da rota: " << caminhaoGuloso[vic].custoCaminho;

            cout << endl;
        }
    }

  my2opt.callVNDTO( infos, caminhaoGuloso, false, 0 );
  cout << "2lixo" << endl;

    for (int vic = 0; vic < infos.veiculos; vic++){

        if( caminhaoGuloso[vic].rota.size() ){
            
                cout << "\nVeiculo [" << vic+1 << "]: ";
        
            for( long unsigned int i = 1; i < caminhaoGuloso[vic].rota.size() - 1; i++ ){
                if (i > 1){
                    cout << " " << caminhaoGuloso[vic].rota[i];
                }
                else
                    cout << caminhaoGuloso[vic].rota[i] ;
            }
                cout << " - custo da rota: " << caminhaoGuloso[vic].custoCaminho;

            cout << endl;
        }
    }

  //susu.realizarVND( caminhaoGuloso[0].rota, infos.custoij, caminhaoGuloso[0], infos.demanda);
  
  //cout << "\ncustocaminho vic 0: " << caminhaoGuloso[0].custoCaminho << endl;

	return 0;
}
