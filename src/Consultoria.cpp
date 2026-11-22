#include "../include/Consultoria.h"
#include <stdexcept>

int Consultoria::adicionarAtributo(const std::string &nome)
{
    Atributo novo;
    novo.id = atributos.getTamanho();
    novo.nome = nome;
    atributos.adicionar(novo);
    return novo.id;
}

const Atributo &Consultoria::getAtributo(int id) const
{
    if (id < 0 || id >= atributos.getTamanho())
    {
        throw std::out_of_range("Identificador de atributo invalido");
    }
    return atributos[id];
}

int Consultoria::getNumAtributos() const
{
    return atributos.getTamanho();
}

void Consultoria::trocarModoIndice(char modo)
{
    indice.trocarModo(modo);
}

void Consultoria::inserirCliente(Cliente *cliente)
{
    indice.inserirCliente(cliente);
}

void Consultoria::removerCliente(int idCliente)
{
    indice.removerCliente(idCliente);
}

NoLista *Consultoria::buscarPoderExato(int poder)
{
    return indice.buscarPoderExato(poder);
}

NoLista *Consultoria::buscarPoderFaixa(int poderMin, int poderMax)
{
    return indice.buscarPoderFaixa(poderMin, poderMax);
}

Cliente *Consultoria::getCliente(int id) const
{
    return indice.getCliente(id);
}

int Consultoria::adicionarRegiao(const std::string &nome)
{
    return mapa.adicionarRegiao(nome);
}

void Consultoria::adicionarRota(int id1, int id2, int custo)
{
    mapa.adicionarRota(id1, id2, custo);
}

bool Consultoria::saoConectados(int id1, int id2)
{
    return mapa.saoConectados(id1, id2);
}

Regiao *Consultoria::getRegiao(int id) const
{
    return mapa.getRegiao(id);
}

std::string Consultoria::getNomeRegiao(int id) const
{
    return mapa.getNomeRegiao(id);
}

int Consultoria::getNumRegioes() const
{
    return mapa.getNumRegioes();
}

int Consultoria::getNumRotas() const
{
    return mapa.getNumRotas();
}

const Vetor<Rota> &Consultoria::getRotasRegiao(int id) const
{
    return mapa.getRotasRegiao(id);
}

void Consultoria::adicionarFila(int prioridade, int idCliente)
{
    filaPrioridade.adicionar(prioridade, idCliente);
}

ElementoPrioridade Consultoria::removerFila()
{
    return filaPrioridade.remover();
}

ElementoPrioridade Consultoria::maximoFila() const
{
    return filaPrioridade.Maximo();
}

bool Consultoria::filaVazia() const
{
    return filaPrioridade.Vazio();
}

int Consultoria::tamanhoFila() const
{
    return filaPrioridade.Tamanho();
}
