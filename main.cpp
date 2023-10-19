#include "Guloso.h"

using namespace std;

int main (){	

  Guloso guloso;
  ReadaOut infos;

  infos.lerValor();
  Veiculo caminhaoGuloso[ infos.veiculos ];

  guloso.GulosoFunc( infos, caminhaoGuloso );

	return 0;
}
