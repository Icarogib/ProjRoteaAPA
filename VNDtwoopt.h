#ifndef VNDTWOOPT_H
#define VNDTWOOPT_H

#include "Veiculo.h"

class VNDtwoopt {
    public:
        VNDtwoopt ();
        bool getTeveMelhora();
        void setTeveMelhora(bool melhora);  
        void callVNDTO ( ReadaOut info, Veiculo *caminhao );
    private:
        bool melhora = false;
        //std::vector< int > novaRota; //teriamos problema O(n) com isso
};

#endif