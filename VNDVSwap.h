#ifndef VNDVSWAP_H
#define VNDVSWAP_H

#include "Veiculo.h"

class VNDVSwap{
    public:
        VNDVSwap ();
        bool getTeveMelhora();
        void setTeveMelhora(bool melhora);  
        void callVNDVswap ( ReadaOut info, Veiculo *veiculos, bool umCaminhao, int numCaminhao );
    private:
    bool melhora = false;
};

#endif