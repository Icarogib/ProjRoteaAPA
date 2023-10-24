#include "VNDswap.h"

VNDswap::VNDswap(){

}

// Implementação da função para calcular o custo da rota
int VNDswap::calcularCustoRota( const std::vector<int>& rota, const std::vector<std::vector<int>>& custoij ) {
    int custo = 0;
    for (size_t i = 0; i < rota.size() - 1; ++i)
    {
        custo += custoij[rota[i]][rota[i + 1]];
    }
    return custo;
}

bool VNDswap::realizarSwap( std::vector<int> &rota, int i, int j, const std::vector<std::vector<int>> &custoij ) {
    // Se i ou j for igual a 0, ou se a troca envolver o ponto 0, não permitimos a troca
    if (i == 0 || j == 0 || rota[i] == 0 || rota[j] == 0)
    {
        return false;
    }

    //IMPLEMENTACAO LIXO TESTE 1
    int custorotatotal = calcularCustoRota( rota, custoij );

    int custo1, custo2;

    custo1 = custorotatotal 
            - custoij[rota[i-1]][rota[i]] - custoij[rota[i]][rota[i+1]]
            - custoij[rota[j-1]][rota[j]] - custoij[rota[j]][rota[j+1]]

            + custoij[rota[i-1]][rota[j]] + custoij[rota[j]][rota[i+1]] 
            + custoij[rota[j-1]][rota[i]] + custoij[rota[i]][rota[j+1]];

    std::cout << "\ncalculo = " << custorotatotal << " - " << custoij[rota[i-1]][rota[i]] << " - " << custoij[rota[i]][rota[i+1]]
            << " - " << custoij[rota[j-1]][rota[j]] << " - " << custoij[rota[j]][rota[j+1]] << 
            " + " << custoij[rota[i-1]][rota[j]] << " + " << custoij[rota[j]][rota[i+1]] <<
            " + " << custoij[rota[j-1]][rota[i]] << " + " << custoij[rota[i]][rota[j+1]];


    std::cout << "\nCustoIcaro: " << custo1 ;

    std::vector<int> rotaOriginal = rota; // Salva a rota original para desfazer a troca se necessário
    std::reverse(rota.begin() + i, rota.begin() + j + 1);
    int novoCusto = calcularCustoRota(rota, custoij );

    std::cout << " - CustoEdu: " << novoCusto << std::endl;

    if ( novoCusto < calcularCustoRota(rotaOriginal, custoij ))
    {
        return true; // Troca aceita e melhora o custo
    }
    else
    {
        rota = rotaOriginal; // Desfaz a troca
        return false;        // Troca não melhora o custo
    }
}

// Implementação da função para realizar o VND com a operação de swap exaustivamente
void VNDswap::realizarVND(std::vector<int>& rotaVeiculo, std::vector<std::vector<int>>& custoij,
                      Veiculo &veiculo, std::vector<int>& demanda) {

    int melhorCusto = calcularCustoRota(rotaVeiculo, custoij);
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
                } else {
                    // Desfaz o swap se não atender aos critérios
                    realizarSwap(rotaVeiculo, i, j, custoij);
                }
            }
        }
    }
}