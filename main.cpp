#include "Guloso.h"
#include "VNDtwoopt.h"
#include "VNDswap.h"
#include "VNDVSwap.h"

using namespace std;




int Vnd(Guloso guloso, ReadaOut infos, VNDswap swap, VNDtwoopt opt,VNDVSwap vertical, Veiculo *caminhaoG){


   while (!swap.getTeveMelhora() && !opt.getTeveMelhora() && vertical.getTeveMelhora())
    {
        for (int i = 1;i <= infos.veiculos; i++)
        {
          swap.realizarVND(caminhaoG[0].rota, infos.custoij, caminhaoG[0], infos.demanda);
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

  

  susu.realizarVND( caminhaoGuloso[0].rota, infos.custoij, caminhaoGuloso[0], infos.demanda);
  
  //cout << "\ncustocaminho vic 0: " << caminhaoGuloso[0].custoCaminho << endl;

	return 0;
}
