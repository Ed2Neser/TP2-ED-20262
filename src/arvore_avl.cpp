#include "../include/arvore_avl.h"

ArvoreAVL::ArvoreAVL() : raiz(nullptr) {}

ArvoreAVL::~ArvoreAVL()
{
    destruirRec(raiz);
}

void ArvoreAVL::destruirRec(NoAVL *no)
{
    if (no != nullptr)
    {
        destruirRec(no->esq);
        destruirRec(no->dir);
        delete no;
    }
}

int ArvoreAVL::maiorFilho(int a, int b)
{
    return (a > b) ? a : b;
}

int ArvoreAVL::altura(NoAVL *no) const
{
    return (no == nullptr) ? -1 : no->altura;
}

int ArvoreAVL::fatorBalanceamento(NoAVL *no) const
{
    if (no == nullptr)
        return 0;
    return altura(no->dir) - altura(no->esq);
}

void ArvoreAVL::atualizarAltura(NoAVL *no)
{
    if (no != nullptr)
    {
        no->altura = 1 + maiorFilho(altura(no->esq), altura(no->dir));
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

void ArvoreAVL::rotacaoDireita(NoAVL *&no)
{
    NoAVL *aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    atualizarAltura(no); // primeiro quem desceu
    atualizarAltura(aux);  // depois quem subiu
    no = aux;
}

void ArvoreAVL::rotacaoEsquerda(NoAVL *&no)
{
    NoAVL *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    atualizarAltura(no); // primeiro quem desceu
    atualizarAltura(aux);  // depois quem subiu
    no = aux;
}

void ArvoreAVL::balancear(NoAVL *&no)
{
    atualizarAltura(no);
    int fb = fatorBalanceamento(no);

    if (fb == -2)
    {
        if (fatorBalanceamento(no->esq) > 0)
        {
            rotacaoEsquerda(no->esq); // Rotação dupla Esquerda-Direita
        }
        rotacaoDireita(no); // Rotação simples à direita
    }
    else if (fb == 2)
    {
        if (fatorBalanceamento(no->dir) < 0)
        {
            rotacaoDireita(no->dir); // Rotação dupla Direita-Esquerda
        }
        rotacaoEsquerda(no); // Rotação simples à esquerda
    }
}

void ArvoreAVL::inserir(Cliente *cliente)
{
    if (cliente == nullptr)
        return;
    inserirRec(raiz, cliente->getId(), cliente->getPoder());
}

void ArvoreAVL::inserirRec(NoAVL *&no, int id, int poder)
{
    if (no == nullptr)
    {
        no = new NoAVL(id, poder);
        return;
    }

    if (chaveMenor(poder, id, no->poderCliente, no->idCliente))
    {
        inserirRec(no->esq, id, poder);
    }
    else if (chaveMenor(no->poderCliente, no->idCliente, poder, id))
    {
        inserirRec(no->dir, id, poder);
    }
    else
    {
        return; // Chave (poder, id) já presente
    }

    balancear(no);
}

void ArvoreAVL::remover(Cliente *cliente)
{
    if (cliente == nullptr)
        return;
    removerRec(raiz, cliente->getId(), cliente->getPoder());
}

void ArvoreAVL::removerRec(NoAVL *&no, int id, int poder)
{
    if (no == nullptr)
        return;

    if (chaveMenor(poder, id, no->poderCliente, no->idCliente))
    {
        removerRec(no->esq, id, poder);
    }
    else if (chaveMenor(no->poderCliente, no->idCliente, poder, id))
    {
        removerRec(no->dir, id, poder);
    }
    else
    {
        if (no->esq == nullptr || no->dir == nullptr)
        {
            NoAVL *aux = no;
            no = (no->esq != nullptr) ? no->esq : no->dir;
            delete aux;
        }
        else
        {
            // Antecessor em-ordem (maior da subárvore esquerda)[cite: 791]
            NoAVL *antecessor = no->esq;
            while (antecessor->dir != nullptr)
            {
                antecessor = antecessor->dir;
            }

            no->idCliente = antecessor->idCliente;
            no->poderCliente = antecessor->poderCliente;

            removerRec(no->esq, antecessor->idCliente, antecessor->poderCliente);
        }
    }

    if (no != nullptr)
    {
        balancear(no);
    }
}

void ArvoreAVL::buscarFaixaRec(NoAVL *no, int poderMin, int poderMax,
                               NoLista *&cabeca, NoLista *&cauda) const
{
    if (no == nullptr)
        return;

    // usa >= e <= para não cortar fora os empates de poder em nós filhos
    if (no->poderCliente >= poderMin)
    {
        buscarFaixaRec(no->esq, poderMin, poderMax, cabeca, cauda);
    }

    if (no->poderCliente >= poderMin && no->poderCliente <= poderMax)
    {
        NoLista *novo = new NoLista(no->idCliente, no->poderCliente);
        novo->prox = nullptr;

        if (cabeca == nullptr)
        {
            cabeca = novo;
            cauda = novo;
        }
        else
        {
            cauda->prox = novo;
            cauda = novo;
        }
    }

    if (no->poderCliente <= poderMax)
    {
        buscarFaixaRec(no->dir, poderMin, poderMax, cabeca, cauda);
    }
}

NoLista *ArvoreAVL::buscarPoderExato(int poder)
{
    return buscarPoderFaixa(poder, poder);
}

NoLista *ArvoreAVL::buscarPoderFaixa(int poderMin, int poderMax)
{
    if (poderMin > poderMax)
        return nullptr;

    NoLista *cabeca = nullptr;
    NoLista *cauda = nullptr;
    buscarFaixaRec(raiz, poderMin, poderMax, cabeca, cauda);
    return cabeca; // a lista encadeada ja vem ordenada, pois a arvore tem estrutura sob medida
}