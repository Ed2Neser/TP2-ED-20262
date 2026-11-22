#include "../include/mapa.h"
#include <stdexcept>

Mapa::Mapa()
    : regioes(),
      componentes(),
      numRotas(0)
{
}

Mapa::~Mapa()
{
    for (int i = 0; i < regioes.getTamanho(); i++)
    {
        delete regioes[i];
    }
}

int Mapa::adicionarRegiao(const std::string &nome)
{
    int id = regioes.getTamanho();

    Regiao *nova = new Regiao(id, nome);
    regioes.adicionar(nova);
    componentes.adicionar(id);

    return id;
}

void Mapa::adicionarRota(int id1, int id2, int custo)
{
    int n = regioes.getTamanho();
    if (id1 < 0 || id1 >= n || id2 < 0 || id2 >= n)
    {
        throw std::out_of_range("Identificador de regiao invalido");
    }
    if (custo <= 0)
    {
        throw std::invalid_argument("O custo da rota deve ser estritamente positivo");
    }

    Rota ida;
    ida.destino = id2;
    ida.custo = custo;
    regioes[id1]->rotas.adicionar(ida);

    Rota volta;
    volta.destino = id1;
    volta.custo = custo;
    regioes[id2]->rotas.adicionar(volta);

    componentes.Union(id1, id2);
    numRotas++;
}

bool Mapa::saoConectados(int id1, int id2)
{
    int n = regioes.getTamanho();
    if (id1 < 0 || id1 >= n || id2 < 0 || id2 >= n)
    {
        throw std::out_of_range("Identificador de regiao invalido");
    }

    return componentes.Find(id1) == componentes.Find(id2);
}

Regiao *Mapa::getRegiao(int id) const
{
    if (id < 0 || id >= regioes.getTamanho())
    {
        throw std::out_of_range("Identificador de regiao invalido");
    }
    return regioes[id];
}

std::string Mapa::getNomeRegiao(int id) const
{
    return getRegiao(id)->nome;
}

int Mapa::getNumRegioes() const
{
    return regioes.getTamanho();
}

int Mapa::getNumRotas() const
{
    return numRotas;
}

const Vetor<Rota> &Mapa::getRotasRegiao(int id) const
{
    return getRegiao(id)->rotas;
}