#include "VNDswap.h"

VNDswap::VNDswap(){
    melhora = false;
}

bool VNDswap::getTeveMelhora(){
    return melhora;
}
void VNDswap::setTeveMelhora(bool m){
    melhora = m;
}

// Implementação da função para calcular o custo da rota
int VNDswap::calcularCustoRota( const std::vector<int>& rota, const std::vector<std::vector<int> >& custoij ) {
    int custo = 0;
    for (size_t i = 0; i < rota.size() - 1; ++i)
    {
        custo += custoij[rota[i]][rota[i + 1]];
    }
    return custo;
}

bool VNDswap::realizarSwap(std::vector<int> &rota, int i, int j, const std::vector<std::vector<int> > &custoij) {
    // Se i ou j for igual a 0, ou se a troca envolver o ponto 0, não permitimos a troca
    if (i == 0 || j == 0 || rota[i] == 0 || rota[j] == 0) {
        return false;
    }

    // Calcula o custo original da rota
    int custorotatotal = calcularCustoRota(rota, custoij);

    // Calcula o custo excluindo os arcos [i-1, i], [i, i+1], [j-1, j], [j, j+1]
    custorotatotal -= custoij[rota[i - 1]][rota[i]] + custoij[rota[i]][rota[i + 1]];
    custorotatotal -= custoij[rota[j - 1]][rota[j]] + custoij[rota[j]][rota[j + 1]];

    // Calcula o custo incluindo os novos arcos [i-1, j], [j, i+1], [j-1, i], [i, j+1]
    custorotatotal += custoij[rota[i - 1]][rota[j]] + custoij[rota[j]][rota[i + 1]];
    custorotatotal += custoij[rota[j - 1]][rota[i]] + custoij[rota[i]][rota[j + 1]];

    // Compara os custos e realiza a troca se o novo custo for menor
    if (custorotatotal < calcularCustoRota(rota, custoij)) {
        // Troca os elementos no vetor de rota
        std::reverse(rota.begin() + i, rota.begin() + j + 1);
        return true; // Troca aceita e melhora o custo
    } else {
        return false; // Troca não melhora o custo
    }

}

// Implementação da função para realizar o VND com a operação de swap exaustivamente
void VNDswap::realizarVND(std::vector<int>& rotaVeiculo, std::vector<std::vector<int> >& custoij,
                      Veiculo &veiculo, std::vector<int>& demanda) {

    int melhorCusto = calcularCustoRota(veiculo.rota, custoij);

    bool melhoriaEncontrada = true;
    
    while (melhoriaEncontrada) {
        melhoriaEncontrada = false;
           
        // Itera sobre todos os pares de vértices na rota
        for (long unsigned int i = 1; i < rotaVeiculo.size() - 1; ++i) {
            for (long unsigned int j = i + 1; j < rotaVeiculo.size(); ++j) {
                // Realiza a operação de swap

                realizarSwap(rotaVeiculo, i, j, custoij);

                // Calcula o custo da nova rota após o swap
                int novoCusto = calcularCustoRota(rotaVeiculo, custoij);

                // Se a capacidade máxima não for excedida e o custo melhorar, aceita o swap
                if (novoCusto < melhorCusto && veiculo.carga >= demanda[rotaVeiculo[j] - 1]) {
                    veiculo.custoCaminho = melhorCusto = novoCusto;
                    melhoriaEncontrada = true;
                    VNDswap::setTeveMelhora(melhoriaEncontrada);
                    std::cout << "melhoria encontrada, trocando os valores" << std::endl;
                    break;
                } else {
                    // Desfaz o swap se não atender aos critérios
                    realizarSwap(rotaVeiculo, i, j, custoij);
                } 
            }

                if(melhoriaEncontrada)
                    break;
                    
        }
            
    }

    std::cout << "\nnova rota:   ";
    for (const auto& element : veiculo.rota) {
        std::cout << element << " ";
        
    }
    std::cout << "novo custo: " << veiculo.custoCaminho << std::endl;
}