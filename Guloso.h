#ifndef GULOSO_H
#define GULOSO_H

#include "Veiculo.h"
using std::vector;
class Guloso {
    public:
        Guloso();
        
        
        void GulosoFunc ( ReadaOut info, Veiculo *veiculo , float alpha, bool enableTerceirizacao, vector<int> &terceirizados, int &custoTotalTerceirizado);

};

#endif