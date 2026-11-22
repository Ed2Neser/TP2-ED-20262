#include "../include/fila_prioridade.h"
#include <stdexcept>

// implementei conforme slides do curso

FilaPrioridade::FilaPrioridade() : v()
{
}

void FilaPrioridade::adicionar(int prioridade, int idCliente)
{
    ElementoPrioridade novo;
    novo.prioridade = prioridade;
    novo.idCliente = idCliente;

    v.adicionar(novo);
    Sobe(v.getTamanho() - 1);
}

ElementoPrioridade FilaPrioridade::remover()
{
    if (v.getTamanho() == 0)
    {
        throw std::runtime_error("Heap vazio");
    }
    ElementoPrioridade topo = v[0];
    v[0] = v.last();
    v.removerUltimo();

    if (v.getTamanho() > 0)
    {
        Desce(0);
    }
    return topo;
}

ElementoPrioridade FilaPrioridade::Maximo() const
{
    if (v.getTamanho() == 0)
    {
        throw std::runtime_error("Heap vazio");
    }
    return v[0];
}

bool FilaPrioridade::Vazio() const
{
    return (v.getTamanho() == 0);
}

int FilaPrioridade::Tamanho() const
{
    return v.getTamanho();
}

int FilaPrioridade::GetAncestral(int i) const
{
    return (i - 1) / 2;
}

int FilaPrioridade::GetSucessorEsq(int i) const
{
    return 2 * i + 1;
}

int FilaPrioridade::GetSucessorDir(int i) const
{
    return 2 * i + 2;
}

bool FilaPrioridade::TemMaiorPrecedencia(const ElementoPrioridade &a, const ElementoPrioridade &b) const
{
    if (a.prioridade != b.prioridade)
    {
        return a.prioridade > b.prioridade;
    }
    return a.idCliente < b.idCliente;
}

void FilaPrioridade::Troca(ElementoPrioridade &a, ElementoPrioridade &b)
{
    ElementoPrioridade aux = a;
    a = b;
    b = aux;
}

void FilaPrioridade::Sobe(int i)
{
    int p = GetAncestral(i);
    while (i > 0 && TemMaiorPrecedencia(v[i], v[p]))
    {
        Troca(v[i], v[p]);
        i = p;
        p = GetAncestral(i);
    }
}

void FilaPrioridade::Desce(int i)
{
    while (true)
    {
        int e = GetSucessorEsq(i);
        int d = GetSucessorDir(i);
        int maior = i;

        if (e < v.getTamanho() && TemMaiorPrecedencia(v[e], v[maior]))
        {
            maior = e;
        }
        if (d < v.getTamanho() && TemMaiorPrecedencia(v[d], v[maior]))
        {
            maior = d;
        }
        if (maior == i)
        {
            return;
        }
        Troca(v[i], v[maior]);
        i = maior;
    }
}