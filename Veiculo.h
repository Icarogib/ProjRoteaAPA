#ifndef VEICULO_H
#define VEICULO_H

#include "ReadaOut.h"

class Veiculo {
    public:
        Veiculo();

        int carga;      // Carga atual do veiculo
        int custoCaminho;   // custo do caminho
        std::vector<int> rota; //"array" do caminho percorrido
        
        // o ultimo valor do custoRota eh a volta do ponto que ele estava para o 0
        // vai ser um a mais comparado ao rota

};

#endif