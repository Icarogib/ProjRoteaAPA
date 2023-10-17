#include "ReadaOut.h"
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;
int Q = 0; // Demanda máxima permitida.

class Grafo
{
    int V;
    vector<vector<int>> grafo;
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
    grafo.resize(V, vector<int>(V, 0));
    demandas.resize(V, 0);
}

void Grafo::adicionarAresta(int u, int v, int peso)
{
    grafo[u][v] = peso;
    grafo[v][u] = peso;
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

        for (int v = 0; v < V; v++)
        {
            if (grafo[u][v] && incluido[v] == false && grafo[u][v] < chave[v])
            {
                chave[v] = grafo[u][v];
                pai[v] = u;
                filaPrioridade.push(make_pair(chave[v], v));
            }
        }
    }

    // Calcula o custo do caminho mínimo.
    int custoTotal = 0;
    for (long unsigned int i = 1; i < caminho.size(); i++)
    {
        custoTotal += grafo[caminho[i - 1]][caminho[i]];
    }

    return make_pair(custoTotal, caminho);
}

int main()
{
    ReadaOut infos;
    infos.lerValor();
    infos.demanda.insert(infos.demanda.begin(), 0);
    
    Q = infos.capacidade;

    Grafo g(infos.demanda.size());

    // Adicionando arestas e demandas ao grafo.
    for (long unsigned int i = 0; i < infos.demanda.size(); ++i)
    {
        g.adicionarDemanda(i, infos.demanda[i]);
        for (long unsigned int j = i + 1; j < infos.demanda.size(); ++j)
        {
            g.adicionarAresta(i, j, infos.custoij[i][j]);
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
