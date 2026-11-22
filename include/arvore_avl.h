#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

#include "Dicionario.h"

struct NoAVL : public NoCliente
{
    int altura;
    NoAVL *esq;
    NoAVL *dir;

    NoAVL(int id, int poder)
    {
        idCliente = id;
        poderCliente = poder;
        esq = nullptr;
        dir = nullptr;
        altura = 0;
    }

    explicit NoAVL(Cliente *cliente)
    {
        idCliente = cliente->getId();
        poderCliente = cliente->getPoder();
        esq = nullptr;
        dir = nullptr;
        altura = 0;
    }
};

class ArvoreAVL : public Dicionario
{
private:
    NoAVL *raiz;

    static int maiorFilho(int a, int b);
    int altura(NoAVL *p) const;
    int fatorBalanceamento(NoAVL *p) const;
    void atualizarAltura(NoAVL *p);

    static bool chaveMenor(int poderA, int idA, int poderB, int idB);

    void rotacaoDireita(NoAVL *&p);
    void rotacaoEsquerda(NoAVL *&p);
    void balancear(NoAVL *&p);

    void inserirRec(NoAVL *&p, int id, int poder);
    void removerRec(NoAVL *&p, int id, int poder);
    void buscarFaixaRec(NoAVL *p, int poderMin, int poderMax, NoLista *&cabeca, NoLista *&cauda) const;
    void destruirRec(NoAVL *p);

public:
    ArvoreAVL();
    ~ArvoreAVL() override;

    ArvoreAVL(const ArvoreAVL &) = delete;
    ArvoreAVL &operator=(const ArvoreAVL &) = delete;

    void inserir(Cliente *cliente) override;
    void remover(Cliente *cliente) override;
    NoLista *buscarPoderExato(int poder) override;
    NoLista *buscarPoderFaixa(int poderMin, int poderMax) override;
};

#endif