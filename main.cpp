#include "Guloso.h"
#include "VNDtwoopt.h"

using namespace std;

int main (){	

  Guloso guloso;
  ReadaOut infos;
  VNDtwoopt my2opt;

  infos.lerValor();
  Veiculo caminhaoGuloso[ infos.veiculos ];

  guloso.GulosoFunc( infos, caminhaoGuloso );

  my2opt.callVNDTO( infos, caminhaoGuloso );

	return 0;
}
