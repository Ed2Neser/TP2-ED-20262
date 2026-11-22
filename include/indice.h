#ifndef INDICE_H
#define INDICE_H

#include "cliente.h"
#include "dicionario.h"
#include "vetor.h"

// inserção por objeto
// remoção por id
// busca via poder
// busca via faixa de poder

class Indice
{
private:
    Vetor<Cliente *> clientes; // vetor denso pkrl
    Dicionario *dicionario;
    char modo; // 'A' para AVL, 'H' para Hash
public:
    Indice();  // inicia o dicionario em AVL
    ~Indice(); // destrói também o dicionario

    void trocarModo(char modo); // 'A' para AVL, 'H' para Hash

    void inserirCliente(Cliente *cliente);                 // insere no vetor e no dicionario
    void removerCliente(int idCliente);                    // remove do vetor e do dicionario
    NoLista *buscarPoderExato(int poder);                  // busca no dicionario e imprime os clientes encontrados
    NoLista *buscarPoderFaixa(int poderMin, int poderMax); // busca no d

    Cliente *getCliente(int id) const;
};
#endif
