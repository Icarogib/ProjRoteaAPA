#ifndef VNDSWAP_H
#define VNDSWAP_H

#include "Veiculo.h"
#include <vector>
#include <algorithm>

class VNDswap {
public:
    VNDswap ();
    // Função para realizar o VND com a operação de swap exaustivamente
    void realizarVND(std::vector<int>& rotaVeiculo, std::vector<std::vector<int> >& custoij,
                      Veiculo &veiculo, std::vector<int>& demanda);
    bool getTeveMelhora();
    void setTeveMelhora(bool melhora);                 

private:
    bool melhora = false;
    // Função para calcular o custo da rota fornecida
    int calcularCustoRota(const std::vector<int>& rota, const std::vector<std::vector<int> >& custoij);

    // Função para realizar a operação de swap na rota
    bool realizarSwap( std::vector<int> &rota, int i, int j, const std::vector<std::vector<int> > &custoij );
};

#endif
