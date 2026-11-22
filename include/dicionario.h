#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "cliente.h"

struct NoCliente // nó generico que serve tanto para a tabela hash quanto para a avl.
{
    int idCliente;
    int poderCliente;
    NoCliente *esq; // ponteiro para o filho esquerdo (para AVL)
    NoCliente *dir; // ponteiro para o próximo nó na lista encadeada (para Hash) ou para o filho direito (para AVL)
};

class Dicionario
{
private:
    char modo; // 'A' para AVL, 'H' para Hash
public:
    virtual ~Dicionario() = default;
    virtual void inserir(Cliente *cliente) = 0; // cliente passado pelo Indice
    virtual void remover(Cliente *cliente) = 0; // cliente passado pelo Indice
    virtual NoCliente *buscarPoderExato(int poder) = 0;
    virtual NoCliente *buscarPoderFaixa(int poderMin, int poderMax) = 0;
};

#endif