#ifndef CONSULTORIA_H
#define CONSULTORIA_H

#include <string>
#include "atributo.h"
#include "fila_prioridade.h"
#include "indice.h"
#include "mapa.h"

class Consultoria
{
private:
    Vetor<Atributo> atributos;
    Indice indice;
    Mapa mapa;
    FilaPrioridade filaPrioridade;

public:
    int adicionarAtributo(const std::string &nome);
    const Atributo &getAtributo(int id) const;
    int getNumAtributos() const;

    void trocarModoIndice(char modo);
    void inserirCliente(Cliente *cliente);
    void removerCliente(int idCliente);
    NoLista *buscarPoderExato(int poder);
    NoLista *buscarPoderFaixa(int poderMin, int poderMax);
    Cliente *getCliente(int id) const;

    int adicionarRegiao(const std::string &nome);
    void adicionarRota(int id1, int id2, int custo);
    bool saoConectados(int id1, int id2);
    Regiao *getRegiao(int id) const;
    std::string getNomeRegiao(int id) const;
    int getNumRegioes() const;
    int getNumRotas() const;
    const Vetor<Rota> &getRotasRegiao(int id) const;

    void adicionarFila(int prioridade, int idCliente);
    ElementoPrioridade removerFila();
    ElementoPrioridade maximoFila() const;
    bool filaVazia() const;
    int tamanhoFila() const;
};

#endif
