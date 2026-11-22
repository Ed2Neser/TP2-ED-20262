#include "../include/indice.h"
#include "../include/arvore_avl.h"
#include "../include/tabela_hash.h"

Indice::Indice() : clientes(), dicionario(new ArvoreAVL()), modo('A') // inicia o dicionario em AVL (por preguiça sendo honesto)
{
}

Indice::~Indice() // destroi o dicionario
{
    delete dicionario;
}

void Indice::trocarModo(char newmodo) // 'A' para AVL, 'H' para Hash
{
    if (newmodo == this->modo)
    {
        return; // Se o modo for o mesmo, mantém
    }
    else if (newmodo == 'A')
    {
        // troca para AVL
        Dicionario *novoDicionario = new ArvoreAVL();
        for (int i = 0; i < clientes.getTamanho(); ++i)
        {
            if (clientes[i] != nullptr)
                novoDicionario->inserir(clientes[i]);
        }
        delete dicionario;
        dicionario = novoDicionario;
    }
    else if (newmodo == 'H')
    {
        // troca para Hash
        Dicionario *novoDicionario = new TabelaHash();
        for (int i = 0; i < clientes.getTamanho(); ++i)
        {
            if (clientes[i] != nullptr)
                novoDicionario->inserir(clientes[i]);
        }
        delete dicionario;
        dicionario = novoDicionario;
    }
    else
    {
        throw std::invalid_argument("Modo inválido. Use 'A' para AVL ou 'H' para Hash.");
    }

    modo = newmodo;
}

void Indice::inserirCliente(Cliente *cliente) // insere no vetor e no dicionario
{
    clientes.adicionar(cliente); // como é sempre sequencial, só botar no fim
    dicionario->inserir(cliente);
}

void Indice::removerCliente(int idCliente) // remove do vetor e do dicionario
{
    dicionario->remover(clientes[idCliente]);
    clientes[idCliente] = nullptr; // marca como removido, mas não remove do vetor (para manter o id como índice)
}
NoLista *Indice::buscarPoderExato(int poder) // busca no dicionario
{
    return dicionario->buscarPoderExato(poder);
}
NoLista *Indice::buscarPoderFaixa(int poderMin, int poderMax) // busca no dicionario
{
    return dicionario->buscarPoderFaixa(poderMin, poderMax);
}

Cliente *Indice::getCliente(int id) const
{
    return clientes[id];
}