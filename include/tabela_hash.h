#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "dicionario.h"

class TabelaHash : public Dicionario
{
private:
    static const int M = 1009;
    NoLista *tabela[M];

    int hash(int poder) const;

    static bool chaveMenor(const NoLista *a, const NoLista *b);
    static NoLista *dividirLista(NoLista *cabeca);
    static NoLista *mergeListas(NoLista *a, NoLista *b);
    static NoLista *mergeSortLista(NoLista *cabeca);

public:
    TabelaHash();
    ~TabelaHash() override;

    void inserir(Cliente *cliente) override;
    void remover(Cliente *cliente) override;
    NoLista *buscarPoderExato(int poder) override;
    NoLista *buscarPoderFaixa(int poderMin, int poderMax) override;
};

#endif