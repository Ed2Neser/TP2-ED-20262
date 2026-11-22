#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "vetor.h"

struct ElementoPrioridade
{
    int prioridade;
    int idCliente;
};

class FilaPrioridade
{
private:
    Vetor<ElementoPrioridade> v;

    int GetAncestral(int i) const;
    int GetSucessorEsq(int i) const;
    int GetSucessorDir(int i) const;
    bool TemMaiorPrecedencia(const ElementoPrioridade &a, const ElementoPrioridade &b) const;
    void Troca(ElementoPrioridade &a, ElementoPrioridade &b);
    void Sobe(int i);
    void Desce(int i);

public:
    FilaPrioridade();
    ~FilaPrioridade() = default;

    void adicionar(int prioridade, int idCliente);
    ElementoPrioridade remover();
    ElementoPrioridade Maximo() const;
    bool Vazio() const;
    int Tamanho() const;
};

#endif