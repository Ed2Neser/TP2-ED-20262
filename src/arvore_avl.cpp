#include "../include/arvore_avl.h"

ArvoreAVL::ArvoreAVL() : raiz(nullptr) {}

ArvoreAVL::~ArvoreAVL()
{
    destruirRec(raiz);
}

void ArvoreAVL::destruirRec(NoAVL *p)
{
    if (p != nullptr)
    {
        destruirRec(static_cast<NoAVL *>(p->esq));
        destruirRec(static_cast<NoAVL *>(p->dir));
        delete p;
    }
}

int ArvoreAVL::maiorFilho(int a, int b)
{
    return (a > b) ? a : b;
}

int ArvoreAVL::altura(NoAVL *p) const
{
    return (p == nullptr) ? -1 : p->altura;
}

int ArvoreAVL::fatorBalanceamento(NoAVL *p) const
{
    if (p == nullptr)
        return 0;
    return altura(static_cast<NoAVL *>(p->dir)) - altura(static_cast<NoAVL *>(p->esq));
}

void ArvoreAVL::atualizarAltura(NoAVL *p)
{
    if (p != nullptr)
    {
        p->altura = 1 + maiorFilho(altura(static_cast<NoAVL *>(p->esq)),
                                   altura(static_cast<NoAVL *>(p->dir)));
    }
}

bool ArvoreAVL::chaveMenor(int poderA, int idA, int poderB, int idB)
{
    if (poderA != poderB)
    {
        return poderA < poderB;
    }
    return idA < idB;
}

void ArvoreAVL::rotacaoDireita(NoAVL *&p)
{
    NoAVL *f = static_cast<NoAVL *>(p->esq);
    p->esq = f->dir;
    f->dir = p;
    atualizarAltura(p);
    atualizarAltura(f);
    p = f;
}

void ArvoreAVL::rotacaoEsquerda(NoAVL *&p)
{
    NoAVL *f = static_cast<NoAVL *>(p->dir);
    p->dir = f->esq;
    f->esq = p;
    atualizarAltura(p);
    atualizarAltura(f);
    p = f;
}

void ArvoreAVL::balancear(NoAVL *&p)
{
    atualizarAltura(p);
    int fb = fatorBalanceamento(p);

    if (fb == -2)
    {
        NoAVL *esq = static_cast<NoAVL *>(p->esq);
        if (fatorBalanceamento(esq) > 0)
        {
            rotacaoEsquerda(esq); // Rotação dupla Esquerda-Direita
            p->esq = esq;
        }
        rotacaoDireita(p); // Rotação simples à direita
    }
    else if (fb == 2)
    {
        NoAVL *dir = static_cast<NoAVL *>(p->dir);
        if (fatorBalanceamento(dir) < 0)
        {
            rotacaoDireita(dir); // Rotação dupla Direita-Esquerda
            p->dir = dir;
        }
        rotacaoEsquerda(p); // Rotação simples à esquerda
    }
}

void ArvoreAVL::inserir(Cliente *cliente)
{
    if (cliente == nullptr)
        return;
    inserirRec(raiz, cliente->getId(), cliente->getPoder());
}

void ArvoreAVL::inserirRec(NoAVL *&p, int id, int poder)
{
    if (p == nullptr)
    {
        p = new NoAVL(id, poder);
        return;
    }

    if (chaveMenor(poder, id, p->poderCliente, p->idCliente))
    {
        NoAVL *esq = static_cast<NoAVL *>(p->esq);
        inserirRec(esq, id, poder);
        p->esq = esq;
    }
    else if (chaveMenor(p->poderCliente, p->idCliente, poder, id))
    {
        NoAVL *dir = static_cast<NoAVL *>(p->dir);
        inserirRec(dir, id, poder);
        p->dir = dir;
    }
    else
    {
        return; // Chave (poder, id) já presente
    }

    balancear(p);
}

void ArvoreAVL::remover(Cliente *cliente)
{
    if (cliente == nullptr)
        return;
    removerRec(raiz, cliente->getId(), cliente->getPoder());
}

void ArvoreAVL::removerRec(NoAVL *&p, int id, int poder)
{
    if (p == nullptr)
        return;

    if (chaveMenor(poder, id, p->poderCliente, p->idCliente))
    {
        NoAVL *esq = static_cast<NoAVL *>(p->esq);
        removerRec(esq, id, poder);
        p->esq = esq;
    }
    else if (chaveMenor(p->poderCliente, p->idCliente, poder, id))
    {
        NoAVL *dir = static_cast<NoAVL *>(p->dir);
        removerRec(dir, id, poder);
        p->dir = dir;
    }
    else
    {
        if (p->esq == nullptr || p->dir == nullptr)
        {
            NoAVL *aux = p;
            p = static_cast<NoAVL *>((p->esq != nullptr) ? p->esq : p->dir);
            delete aux;
        }
        else
        {
            // Antecessor em-ordem (maior da subárvore esquerda)
            NoAVL *antecessor = static_cast<NoAVL *>(p->esq);
            while (antecessor->dir != nullptr)
            {
                antecessor = static_cast<NoAVL *>(antecessor->dir);
            }

            p->idCliente = antecessor->idCliente;
            p->poderCliente = antecessor->poderCliente;

            NoAVL *esq = static_cast<NoAVL *>(p->esq);
            removerRec(esq, antecessor->idCliente, antecessor->poderCliente);
            p->esq = esq;
        }
    }

    if (p != nullptr)
    {
        balancear(p);
    }
}

void ArvoreAVL::buscarFaixaRec(NoAVL *p, int poderMin, int poderMax,
                               NoCliente *&cabeca, NoCliente *&cauda) const
{
    if (p == nullptr)
        return;

    // Usa >= e <= para não podar empates de poder em nós filhos
    if (p->poderCliente >= poderMin)
    {
        buscarFaixaRec(static_cast<NoAVL *>(p->esq), poderMin, poderMax, cabeca, cauda);
    }

    if (p->poderCliente >= poderMin && p->poderCliente <= poderMax)
    {
        NoCliente *novo = new NoCliente();
        novo->idCliente = p->idCliente;
        novo->poderCliente = p->poderCliente;
        novo->esq = nullptr;
        novo->dir = nullptr;

        if (cabeca == nullptr)
        {
            cabeca = novo;
            cauda = novo;
        }
        else
        {
            cauda->dir = novo;
            cauda = novo;
        }
    }

    if (p->poderCliente <= poderMax)
    {
        buscarFaixaRec(static_cast<NoAVL *>(p->dir), poderMin, poderMax, cabeca, cauda);
    }
}

NoCliente *ArvoreAVL::buscarPoderExato(int poder)
{
    return buscarPoderFaixa(poder, poder);
}

NoCliente *ArvoreAVL::buscarPoderFaixa(int poderMin, int poderMax)
{
    if (poderMin > poderMax)
        return nullptr;

    NoCliente *cabeca = nullptr;
    NoCliente *cauda = nullptr;
    buscarFaixaRec(raiz, poderMin, poderMax, cabeca, cauda);
    return cabeca;
}