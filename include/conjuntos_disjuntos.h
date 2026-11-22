#ifndef CONJUNTOS_DISJUNTOS_H
#define CONJUNTOS_DISJUNTOS_H

#include "vetor.h"

class ConjuntosDisjuntos
{
private:
    Vetor<int> pai;
    Vetor<int> rank;

public:
    ConjuntosDisjuntos();
    ConjuntosDisjuntos(int n);

    int Find(int x);
    void Union(int x, int y);

    void adicionar(int x);
    int getTamanho() const;
};

#endif