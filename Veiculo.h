#include "ReadaOut.h"

class Veiculo {
    public:
        Veiculo();

        int carga;      // Carga atual do veiculo
        int custoCaminho;   // custo do caminho
        bool usado;         // se veiculo foi utilizado
        
        std::vector<int> rota; //"array" do caminho percorrido

};