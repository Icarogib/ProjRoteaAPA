#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;
const int Q = 50; // Demanda máxima permitida.

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
    for (int i = 1; i < caminho.size(); i++)
    {
        custoTotal += grafo[caminho[i - 1]][caminho[i]];
    }

    return make_pair(custoTotal, caminho);
}

int main()
{
    Grafo g(10);

    int matriz[10][10] = {
        {0, 35, 78, 76, 98, 55, 52, 38, 86, 89},
        {35, 0, 61, 60, 91, 81, 41, 13, 85, 95},
        {78, 61, 0, 4, 38, 87, 27, 49, 41, 59},
        {76, 60, 4, 0, 37, 84, 24, 47, 39, 57},
        {98, 91, 38, 37, 0, 84, 51, 78, 18, 34},
        {55, 81, 87, 84, 84, 0, 66, 75, 67, 57},
        {52, 41, 27, 24, 51, 66, 0, 28, 45, 57},
        {38, 13, 49, 47, 78, 75, 28, 0, 72, 82},
        {86, 85, 41, 39, 18, 67, 45, 72, 0, 20},
        {89, 95, 59, 57, 34, 57, 57, 82, 20, 0}};

    int demandas[10] = {0, 19, 21, 6, 19, 7, 12, 16, 6, 16};

    // Adicionando arestas e demandas ao grafo.
    for (int i = 0; i < 10; ++i)
    {
        g.adicionarDemanda(i, demandas[i]);
        for (int j = i + 1; j < 10; ++j)
        {
            g.adicionarAresta(i, j, matriz[i][j]);
        }
    }

    auto resultado = g.primMST();

    cout << "Caminho mínimo: ";
    for (int i = 0; i < resultado.second.size(); i++)
    {
        cout << resultado.second[i] << " ";
    }
    cout << endl;
    cout << "Custo do caminho mínimo: " << resultado.first << endl;

    return 0;
}
