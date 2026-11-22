#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

#include "Dicionario.h"

struct NoAVL : public NoCliente
{
    int altura;

    NoAVL(int id, int poder)
    {
        idCliente = id;
        poderCliente = poder;
        esq = nullptr;
        dir = nullptr;
        altura = 0;
    };
    NoAVL(Cliente *cliente)
    {
        idCliente = cliente->getId();
        poderCliente = cliente->getPoder();
        esq = nullptr;
        dir = nullptr;
        altura = 0;
    };
};

class ArvoreAVL : public Dicionario
{
private:
    NoAVL *raiz;
    char modo = 'A'; // 'A' para AVL, 'H' para Hash

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
    void buscarFaixaRec(NoAVL *p, int poderMin, int poderMax, NoCliente *&cabeca, NoCliente *&cauda) const;
    void destruirRec(NoAVL *p);

public:
    ArvoreAVL();
    ~ArvoreAVL() override;

    ArvoreAVL(const ArvoreAVL &) = delete;
    ArvoreAVL &operator=(const ArvoreAVL &) = delete;

    void inserir(Cliente *cliente) override;
    void remover(Cliente *cliente) override;
    NoCliente *buscarPoderExato(int poder) override;
    NoCliente *buscarPoderFaixa(int poderMin, int poderMax) override;
};

#endif