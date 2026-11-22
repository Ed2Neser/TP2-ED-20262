#include "../include/conjuntos_disjuntos.h"

ConjuntosDisjuntos::ConjuntosDisjuntos() : pai(), rank()
{
}

ConjuntosDisjuntos::ConjuntosDisjuntos(int n) : pai(n), rank(n)
{
    for (int i = 0; i < n; i++)
    {
        pai.adicionar(i);
        rank.adicionar(0);
    }
}

int ConjuntosDisjuntos::Find(int x)
{
    if (pai[x] != x)
    {
        pai[x] = Find(pai[x]);
    }
    return pai[x];
}

void ConjuntosDisjuntos::Union(int x, int y)
{
    int raiz_x = Find(x);
    int raiz_y = Find(y);

    if (raiz_x == raiz_y)
    {
        return;
    }

    if (rank[raiz_x] < rank[raiz_y])
    {
        pai[raiz_x] = raiz_y;
    }
    else if (rank[raiz_x] > rank[raiz_y])
    {
        pai[raiz_y] = raiz_x;
    }
    else
    {
        pai[raiz_x] = raiz_y;
        rank[raiz_y]++;
    }
}

int ConjuntosDisjuntos::getTamanho() const
{
    return pai.getTamanho();
}

void ConjuntosDisjuntos::adicionar(int x)
{
    pai.adicionar(x);
    rank.adicionar(0);
}