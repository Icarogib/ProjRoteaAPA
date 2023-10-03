#include <iostream>
#include <string>
#include <fstream>

class ReadaOut {
    public:
        ReadaOut();
        void ReadaOut::setDemanda ( int d );
        void ReadaOut::setVeiculos ( int k );
        void ReadaOut::setCapacidade ( int Q );
        void ReadaOut::setCustoVeiculo ( int r );
        void ReadaOut::setTerc ( int p );
        void ReadaOut::setLimiteMinEnt ( int L );

        void ReadaOut::lerValor ();

    private:
        //int clientes ( int n );
        int demanda ( int d );
        int veiculos ( int k );
        int capacidade ( int Q );
        int custoVeiculo ( int r );
        int custoTerc ( int p );
        int limiteMinEnt ( int L ); //limite minimo de entregas antes de tercerizar
        

};