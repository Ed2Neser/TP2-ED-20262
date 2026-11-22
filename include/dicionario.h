#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "cliente.h"

struct NoCliente // nó generico que serve tanto para uma lista quanto para a arvore (avl).
{
    int idCliente;
    int poderCliente;
};

struct NoLista : public NoCliente
{
    NoLista *prox;

    NoLista(int id, int poder)
    {
        idCliente = id;
        poderCliente = poder;
        prox = nullptr;
    };
};

class Dicionario
{
public:
    virtual ~Dicionario() = default;
    virtual void inserir(Cliente *cliente) = 0; // cliente passado pelo Indice
    virtual void remover(Cliente *cliente) = 0; // cliente passado pelo Indice
    virtual NoLista *buscarPoderExato(int poder) = 0;
    virtual NoLista *buscarPoderFaixa(int poderMin, int poderMax) = 0;
};

#endif