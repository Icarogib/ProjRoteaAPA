#include "ReadaOut.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;
int Q = 0; // Demanda máxima permitida.

class Grafo
{
    int V;
    vector<list<pair<int, int>>> adjList;
    vector<int> demandas;

public:
    Grafo(int vertices);
    void adicionarAresta(int u, int v, int peso);
    void adicionarDemanda(int vertice, int demanda);
    pair<int, vector<int>> primMST();
};

Grafo::Grafo(int vertices)
{
    V = vertices;
    adjList.resize(V);
    demandas.resize(V, 0);
}

void Grafo::adicionarAresta(int u, int v, int peso)
{
    adjList[u].push_back(make_pair(v, peso));
    adjList[v].push_back(make_pair(u, peso));
}

void Grafo::adicionarDemanda(int vertice, int demanda)
{
    demandas[vertice] = demanda;
}

pair<int, vector<int>> Grafo::primMST()
{
    vector<int> chave(V, INF);
    vector<bool> incluido(V, false);
    vector<int> pai(V, -1);

    chave[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;

    filaPrioridade.push(make_pair(0, 0));

    int demandaCaminhao = 0;
    vector<int> caminho;

    while (!filaPrioridade.empty())
    {
        int u = filaPrioridade.top().second;
        filaPrioridade.pop();

        if (demandaCaminhao + demandas[u] <= Q)
        {
            caminho.push_back(u);
            demandaCaminhao += demandas[u];
        }
        else if (u != 0)
        {
            // Se a demanda ultrapassar Q e não é o ponto 0, retorna ao ponto 0.
            caminho.push_back(0);
            demandaCaminhao = demandas[0];
            break; // Caminhão volta para o ponto 0 e encerra a rota.
        }

        incluido[u] = true;

        for (const auto &vizinho : adjList[u])
        {
            int v = vizinho.first;
            int peso = vizinho.second;
            if (!incluido[v] && peso < chave[v])
            {
                chave[v] = peso;
                pai[v] = u;
                filaPrioridade.push(make_pair(chave[v], v));
            }
        }
    }

    // Calcula o custo do caminho mínimo.
    int custoTotal = 0;
    for ( long unsigned int i = 1; i < caminho.size(); i++)
    {
        for (const auto &vizinho : adjList[caminho[i - 1]])
        {
            if (vizinho.first == caminho[i])
            {
                custoTotal += vizinho.second;
                break;
            }
        }
    }

    return make_pair(custoTotal, caminho);
}

int main()
{
    ReadaOut infos;
    infos.lerValor( "n31k5_A.txt" );
    infos.demanda.insert(infos.demanda.begin(), 0);

    Q = infos.capacidade;

    Grafo g(infos.demanda.size());

    // Adicionando arestas e demandas ao grafo.
    for (long unsigned int i = 0; i < infos.demanda.size(); ++i)
    {
        g.adicionarDemanda(i, infos.demanda[i]);
        for (long unsigned int j = 0; j < infos.demanda.size(); ++j)
        {
            if (infos.custoij[i][j] != 0)
            {
                g.adicionarAresta(i, j, infos.custoij[i][j]);
            }
        }
    }

    auto resultado = g.primMST();

    cout << "Caminho mínimo: ";
    for (long unsigned int i = 0; i < resultado.second.size(); i++)
    {
        cout << resultado.second[i] << " ";
    }
    cout << endl;
    cout << "Custo do caminho mínimo: " << resultado.first << endl;

    return 0;
}
