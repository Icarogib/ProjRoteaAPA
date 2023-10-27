#include "Guloso.h"
#include "VNDtwoopt.h"
#include "VNDswap.h"

using namespace std;

int main (){	

  Guloso guloso;
  ReadaOut infos;
  VNDswap susu;
  VNDtwoopt my2opt;
  float alpha = 0.5;
  infos.lerValor( "n31k5_A.txt" );
  Veiculo caminhaoGuloso[ infos.veiculos ];
  
  guloso.GulosoFunc( infos, caminhaoGuloso , alpha);

  susu.realizarVND( caminhaoGuloso[0].rota, infos.custoij, caminhaoGuloso[0], infos.demanda);

  cout << "\ncustocaminho vic 0: " << caminhaoGuloso[0].custoCaminho << endl;

  my2opt.callVNDTO( infos, caminhaoGuloso );


	return 0;
}
