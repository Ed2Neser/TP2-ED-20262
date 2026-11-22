#include "../include/cliente.h"

Cliente::Cliente(int id, const std::string &nome, AtributoValor *build, int tamanhoBuild)
    : id(id), nome(nome), build(build)
{
    poder = 0;
    for (int i = 0; i < tamanhoBuild; ++i)
    {
        poder += build[i].valor;
    }
}

Cliente::~Cliente()
{
    delete[] build;
}

int Cliente::getId() const { return id; }
std::string Cliente::getNome() const { return nome; }
int Cliente::getPoder() const { return poder; }