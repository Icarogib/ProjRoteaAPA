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

int Vnd(Guloso guloso, ReadaOut infos, VNDswap swap, VNDtwoopt opt,VNDVSwap vertical, Veiculo *caminhaoG){


   while (!swap.getTeveMelhora() && !opt.getTeveMelhora() && vertical.getTeveMelhora())
    {
        for (int i = 0;i < infos.veiculos; i++)
        {
          swap.realizarVND(caminhaoG[i].rota, infos.custoij, caminhaoG[i], infos.demanda);
          if (swap.getTeveMelhora() == false)
          {
             opt.callVNDTO( infos, caminhaoG ); //ok
             if (opt.getTeveMelhora() == true )
             {
              
             }
             
          }
          
        }
    }
      int custoTotal = caminhaoG[0].custoCaminho;
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


  Vnd(guloso,infos,susu,my2opt,swapperV,caminhaoGuloso);  
  
  swapperV.callVNDVswap( infos, caminhaoGuloso ); // ok

  //my2opt.callVNDTO( infos, caminhaoGuloso );
  

  susu.realizarVND( caminhaoGuloso[0].rota, infos.custoij, caminhaoGuloso[0], infos.demanda);
  
  //cout << "\ncustocaminho vic 0: " << caminhaoGuloso[0].custoCaminho << endl;

	return 0;
}
