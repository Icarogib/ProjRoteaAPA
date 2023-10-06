#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class ReadaOut {
    public:
        ReadaOut();

        void lerValor ();   

        int entregas;   // numero de entregas
        int veiculos;   // n de veiculos disponiveis
        int capacidade; // capacidade de cada veiculo
        int limiteMinEnt; // limite minimo de entregas antes de tercerizar
        int custoVeiculo; // preco por usar um veiculo
        
        //int demanda; //vector
        //int custoTerc; //vector
        

};