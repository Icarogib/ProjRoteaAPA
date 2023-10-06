

#include <iostream>
#include<list>
#include<vector>
#include<string>
#include<limits>

using namespace std;

typedef struct 
{
    bool jaExec = false;
    int veiculo_armazenado = -1; //SE O VEICULO FOR 0 SIGNIFICA QUE ELE VAI SER TERCERIZADO

    int menor_custo = std::numeric_limits<int>::max();
    int demanda;
    int num_vizinho;
    

}Vertices;

typedef struct 
{
   int pos =0;
   std::vector<int> vertices_armazenados = {}; 
   int peso = 0;

}caminhao;





int numero_de_pontos = 6; // (esse é o n)
int numero_de_veiculos = 2; // k
int capacidade = 10; // Q

std::vector<int> demanda_por_veiculo = {0,3,6,2,4,1,4}; // d
std::vector<int> custo_tercerizacao = {5,2,4,4,5,3}; //Pi

int custo_veiculo = 5; // R
int num_estregas_NT =3; //L

int matriz[7][7] = {
    {0, 2, 3, 4, 1, 9, 6},
    {2, 0, 3, 2, 3, 2, 9},
    {5, 5, 0, 5, 13, 7, 5},
    {7, 3, 1, 0, 3, 4, 11},
    {6, 5, 3, 1, 0, 4, 15},
    {2, 8, 11, 2, 3, 0, 8},
    {7, 10, 7, 10, 15, 8, 0}
}; // matriz teste CIJ







int Guloso()
{


std::vector<Vertices> verticesAUX;

for (int i = 0; i < numero_de_pontos ; i++)
{
    Vertices Pontos;
    verticesAUX.push_back(Pontos); 
    Pontos.demanda = demanda_por_veiculo[i+1];
}

std::vector<caminhao> caminhaoAUX; 

for (int index = 0; index < numero_de_veiculos; index++)
{
    caminhao VrumVrum;
    caminhaoAUX.push_back(VrumVrum);
}

// criando as estruturas de dados auxiliares


for (int k = 0; k < numero_de_veiculos; k++)
{
    if (caminhaoAUX[k].peso < 10)
    {
       
        for (int n = 0; n < numero_de_pontos; n++)
        {
            
            if (verticesAUX[n].jaExec == false)
            {

                for (int i = 0; i < numero_de_pontos; i++)
                {
                    if (verticesAUX[n].menor_custo > matriz[caminhaoAUX[k].pos][i + 1] && verticesAUX[n].menor_custo > 0)
                    {
                        verticesAUX[n].menor_custo = matriz[caminhaoAUX[k].pos][i + 1];
                        verticesAUX[n].num_vizinho = i+1;
                        caminhaoAUX[k].pos = verticesAUX[n].num_vizinho;
                    }

                }
                verticesAUX[n].jaExec == true;
                caminhaoAUX[k].peso += verticesAUX[n].demanda;
                cout << "o caminhao " << k << " esta com peso : " << caminhaoAUX[k].peso << endl;
                cout << "o caminhao " << k << " esta na posicao : " << caminhaoAUX[k].pos << endl;
            }
         }
    }
}











}

int main(void){

Guloso();

}



