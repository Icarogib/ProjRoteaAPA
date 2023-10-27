#ifndef VNDTWOOPT_H
#define VNDTWOOPT_H

#include "Veiculo.h"

class VNDtwoopt {
    public:
        VNDtwoopt ();
        bool getTeveMelhora();
        void setTeveMelhora(bool melhora);  
        void callVNDTO ( ReadaOut info, Veiculo *caminhao, bool umCaminhao, int numCaminhao );
    private:
        bool melhora = false;
};

#endif