#ifndef MAPA_H
#define MAPA_H

#include <string>
#include "vetor.h"
#include "conjuntos_disjuntos.h"

struct Rota
{
    int destino;
    int custo;
};

struct Regiao
{
    int id;
    std::string nome;
    Vetor<Rota> rotas;

    Regiao(int id, const std::string &nome)
        : id(id), nome(nome), rotas() {}
};

class Mapa
{
private:
    Vetor<Regiao *> regioes;
    ConjuntosDisjuntos componentes;
    int numRotas;

    // pra evitar copia acidental
    Mapa(const Mapa &) = delete;
    Mapa &operator=(const Mapa &) = delete;

public:
    Mapa();
    ~Mapa();

    int adicionarRegiao(const std::string &nome);
    void adicionarRota(int id1, int id2, int custo);
    bool saoConectados(int id1, int id2);

    Regiao *getRegiao(int id) const;
    std::string getNomeRegiao(int id) const;
    int getNumRegioes() const;
    int getNumRotas() const;
    const Vetor<Rota> &getRotasRegiao(int id) const;
};

#endif