#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct AtributoValor
{
    int idAtributo;
    int valor;
};

class Cliente
{
private:
    int id;
    std::string nome;
    AtributoValor *build;
    int poder;

public:
    Cliente(int id, const std::string &nome, AtributoValor *build, int tamanhoBuild);
    ~Cliente();

    int getId() const;
    std::string getNome() const;
    int getPoder() const;
};

#endif
