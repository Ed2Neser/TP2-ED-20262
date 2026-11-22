#ifndef INDICE_H
#define INDICE_H

#include "cliente.h"
#include "dicionario.h"
#include "vetor.h"

// inserção por id
// remoção por id
// busca via poder
// busca via faixa de poder

class Indice
{
private:
    Vetor<Cliente *> clientes;
    Dicionario *dicionario;

public:
    Indice();  // inicia o dicionario em AVL
    ~Indice(); // destrói também o dicionario

    void trocarModo(char modo); // 'A' para AVL, 'H' para Hash

    // removerCliente retira o cliente do vetor (criar uma função em Vetor que remove ordenado (arrastando o resto do vetor) E do dicionario
};

#endif
