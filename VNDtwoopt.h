#ifndef VNDTWOOPT_H
#define VNDTWOOPT_H

#include "Veiculo.h"

class VNDtwoopt {
    public:
        VNDtwoopt ();

        void callVNDTO ( ReadaOut info, Veiculo *caminhao );

        //std::vector< int > novaRota; //teriamos problema O(n) com isso
};

#endif