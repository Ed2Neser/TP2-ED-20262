#include "../include/tabela_hash.h"

TabelaHash::TabelaHash()
{
    for (int i = 0; i < M; ++i)
    {
        tabela[i] = nullptr;
    }
}

TabelaHash::~TabelaHash()
{
    for (int i = 0; i < M; ++i)
    {
        NoLista *atual = tabela[i];
        while (atual != nullptr)
        {
            NoLista *prox = atual->prox;
            delete atual;
            atual = prox;
        }
    }
}

int TabelaHash::hash(int poder) const
{
    return ((poder % M) + M) % M;
}

bool TabelaHash::chaveMenor(const NoLista *a, const NoLista *b)
{
    if (a->poderCliente != b->poderCliente)
    {
        return a->poderCliente < b->poderCliente;
    }
    return a->idCliente < b->idCliente;
}

NoLista *TabelaHash::dividirLista(NoLista *cabeca)
{
    NoLista *lento = cabeca;
    NoLista *rapido = cabeca->prox;

    while (rapido != nullptr && rapido->prox != nullptr)
    {
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }

    NoLista *segundaMetade = lento->prox;
    lento->prox = nullptr;
    return segundaMetade;
}

NoLista *TabelaHash::mergeListas(NoLista *a, NoLista *b)
{
    NoLista cabecaFalsa(0, 0);
    NoLista *cauda = &cabecaFalsa;

    while (a != nullptr && b != nullptr)
    {
        if (chaveMenor(a, b))
        {
            cauda->prox = a;
            a = a->prox;
        }
        else
        {
            cauda->prox = b;
            b = b->prox;
        }
        cauda = cauda->prox;
    }

    cauda->prox = (a != nullptr) ? a : b;
    return cabecaFalsa.prox;
}

NoLista *TabelaHash::mergeSortLista(NoLista *cabeca)
{
    if (cabeca == nullptr || cabeca->prox == nullptr)
    {
        return cabeca;
    }

    NoLista *segundaMetade = dividirLista(cabeca);
    NoLista *esquerda = mergeSortLista(cabeca);
    NoLista *direita = mergeSortLista(segundaMetade);

    return mergeListas(esquerda, direita);
}

void TabelaHash::inserir(Cliente *cliente)
{
    if (cliente == nullptr)
        return;

    int id = cliente->getId();
    int poder = cliente->getPoder();
    int pos = hash(poder);

    NoLista *atual = tabela[pos];
    while (atual != nullptr)
    {
        if (atual->idCliente == id && atual->poderCliente == poder)
        {
            return; // Evita duplicata
        }
        atual = atual->prox;
    }

    // Inserção no início da lista encadeada em O(1)
    NoLista *novo = new NoLista(id, poder);
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

void TabelaHash::remover(Cliente *cliente)
{
    if (cliente == nullptr)
        return;

    int id = cliente->getId();
    int poder = cliente->getPoder();
    int pos = hash(poder);

    NoLista *anterior = nullptr;
    NoLista *atual = tabela[pos];

    while (atual != nullptr)
    {
        if (atual->idCliente == id && atual->poderCliente == poder)
        {
            if (anterior == nullptr)
            {
                tabela[pos] = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            delete atual;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

NoLista *TabelaHash::buscarPoderExato(int poder)
{
    int pos = hash(poder);
    NoLista *resultado = nullptr;

    NoLista *atual = tabela[pos];
    while (atual != nullptr)
    {
        if (atual->poderCliente == poder)
        {
            NoLista *novo = new NoLista(atual->idCliente, atual->poderCliente);
            novo->prox = resultado;
            resultado = novo;
        }
        atual = atual->prox;
    }

    return mergeSortLista(resultado);
}

NoLista *TabelaHash::buscarPoderFaixa(int poderMin, int poderMax)
{
    if (poderMin > poderMax)
        return nullptr;

    NoLista *resultado = nullptr;

    for (int i = 0; i < M; ++i)
    {
        NoLista *atual = tabela[i];
        while (atual != nullptr)
        {
            if (atual->poderCliente >= poderMin && atual->poderCliente <= poderMax)
            {
                NoLista *novo = new NoLista(atual->idCliente, atual->poderCliente);
                novo->prox = resultado;
                resultado = novo;
            }
            atual = atual->prox;
        }
    }

    return mergeSortLista(resultado);
}