#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Vertice
{
    bool jaExec = false;
    int menorCusto = std::numeric_limits<int>::max();
    int numVizinho = -1;
    int demanda;
};

struct Caminhao
{
    int pos = 0;
    std::vector<int> verticesArmazenados = {};
    int peso = 0;
};

int numeroDePontos = 6;   // (esse é o n)
int numeroDeVeiculos = 2; // k
int capacidade = 10;      // Q

std::vector<int> demandaPorVeiculo = {0, 3, 6, 2, 4, 1, 4}; // d
std::vector<int> custoTercerizacao = {5, 2, 4, 4, 5, 3};    // Pi

int matriz[7][7] = {
    {0, 2, 3, 4, 1, 9, 6},     // VERTICE 0
    {2, 0, 3, 2, 3, 2, 9},     // VERTICE 1
    {5, 5, 0, 5, 13, 7, 5},    // VERTICE 2
    {7, 3, 1, 0, 3, 4, 11},    // VERTICE 3
    {6, 5, 3, 1, 0, 4, 15},    // VERTICE 4
    {2, 8, 11, 2, 3, 0, 8},    // VERTICE 5
    {7, 10, 7, 10, 15, 8, 0}}; // VERTICE 6

void Guloso()
{
    std::vector<Vertice> verticesAUX(numeroDePontos + 1);
    std::vector<Caminhao> caminhaoAUX(numeroDeVeiculos);
    std::vector<std::vector<bool>> verticeVisitado(numeroDeVeiculos, std::vector<bool>(numeroDePontos + 1, false));
    std::vector<int> demandaCaminhao(numeroDeVeiculos, 0);

    for (int i = 0; i <= numeroDePontos; i++)
    {
        verticesAUX[i].demanda = demandaPorVeiculo[i];
    }

    for (int k = 0; k < numeroDeVeiculos; k++)
    {
        for (int n = 0; n < numeroDePontos; n++)
        {
            if (!verticesAUX[n].jaExec && caminhaoAUX[k].peso + verticesAUX[n].demanda <= capacidade)
            {
                for (int i = 1; i <= numeroDePontos; i++)
                {
                    if (!verticesAUX[i].jaExec &&
                        !verticeVisitado[k][i] &&
                        caminhaoAUX[k].peso + verticesAUX[i].demanda <= capacidade &&
                        verticesAUX[n].menorCusto > matriz[caminhaoAUX[k].pos][i] &&
                        matriz[caminhaoAUX[k].pos][i] > 0)
                    {
                        verticesAUX[n].menorCusto = matriz[caminhaoAUX[k].pos][i];
                        verticesAUX[n].numVizinho = i;
                    }
                }

                if (verticesAUX[n].numVizinho != -1)
                {
                    verticesAUX[n].jaExec = true;
                    caminhaoAUX[k].peso += verticesAUX[n].demanda;
                    caminhaoAUX[k].verticesArmazenados.push_back(verticesAUX[n].numVizinho);
                    verticeVisitado[k][verticesAUX[n].numVizinho] = true;
                    caminhaoAUX[k].pos = verticesAUX[n].numVizinho;
                    demandaCaminhao[k] += verticesAUX[n].demanda;
                }
            }
        }
    }

    // Imprimir resultados
    for (int k = 0; k < numeroDeVeiculos; k++)
    {
        cout << "Caminhao " << k + 1 << ": ";
        for (int i : caminhaoAUX[k].verticesArmazenados)
        {
            cout << i << " ";
        }
        cout << " - Demanda: " << demandaCaminhao[k] << endl;
    }
}

int main(void)
{
    Guloso();
    return 0;
}
