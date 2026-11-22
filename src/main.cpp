#include "../include/Consultoria.h"
#include <iostream>
#include <string>

namespace
{
void liberarLista(NoLista *lista)
{
    while (lista != nullptr)
    {
        NoLista *proximo = lista->prox;
        delete lista;
        lista = proximo;
    }
}
}

int main()
{
    Consultoria consultoria;
    int proximoIdCliente = 0;
    std::string comando;

    while (std::cin >> comando)
    {
        if (comando == "E")
        {
            char modo;
            std::cin >> modo;
            consultoria.trocarModoIndice(modo);
            std::cout << "E " << modo << '\n';
        }
        else if (comando == "A")
        {
            std::string nome;
            std::cin >> nome;
            int id = consultoria.adicionarAtributo(nome);
            std::cout << "A " << id << '\n';
        }
        else if (comando == "C")
        {
            std::string nome;
            int quantidade;
            std::cin >> nome >> quantidade;

            int quantidadeAtributos = consultoria.getNumAtributos();
            AtributoValor *build = new AtributoValor[quantidadeAtributos];
            for (int i = 0; i < quantidadeAtributos; ++i)
            {
                build[i].idAtributo = i;
                build[i].valor = 0;
            }

            for (int i = 0; i < quantidade; ++i)
            {
                int idAtributo;
                int valor;
                std::cin >> idAtributo >> valor;
                build[idAtributo].valor = valor;
            }

            Cliente *cliente = new Cliente(proximoIdCliente, nome, build, quantidadeAtributos);
            consultoria.inserirCliente(cliente);
            std::cout << "C " << proximoIdCliente << ' ' << cliente->getPoder() << '\n';
            ++proximoIdCliente;
        }
        else if (comando == "D")
        {
            int idCliente;
            std::cin >> idCliente;
            Cliente *cliente = consultoria.getCliente(idCliente);
            std::cout << "D " << cliente->getNome() << ' ' << cliente->getPoder() << '\n';
            consultoria.removerCliente(idCliente);
            delete cliente;
        }
        else if (comando == "BP")
        {
            int poder;
            std::cin >> poder;
            NoLista *resultado = consultoria.buscarPoderExato(poder);
            std::cout << "BP " << poder;
            if (resultado == nullptr)
            {
                std::cout << " VAZIO";
            }
            else
            {
                int posicao = 1;
                for (NoLista *atual = resultado; atual != nullptr; atual = atual->prox)
                {
                    std::cout << " cliente_" << posicao++ << ' ' << atual->idCliente;
                }
            }
            std::cout << '\n';
            liberarLista(resultado);
        }
        else if (comando == "BF")
        {
            int poderMin;
            int poderMax;
            std::cin >> poderMin >> poderMax;
            NoLista *resultado = consultoria.buscarPoderFaixa(poderMin, poderMax);
            std::cout << "BF " << poderMin << ' ' << poderMax;
            if (resultado == nullptr)
            {
                std::cout << " VAZIO";
            }
            else
            {
                int posicao = 1;
                for (NoLista *atual = resultado; atual != nullptr; atual = atual->prox)
                {
                    std::cout << " cliente_" << posicao++ << ' ' << atual->idCliente
                              << ' ' << atual->poderCliente;
                }
            }
            std::cout << '\n';
            liberarLista(resultado);
        }
        else if (comando == "R")
        {
            std::string nome;
            std::cin >> nome;
            int id = consultoria.adicionarRegiao(nome);
            std::cout << "R " << id << '\n';
        }
        else if (comando == "T")
        {
            int id1;
            int id2;
            int custo;
            std::cin >> id1 >> id2 >> custo;
            consultoria.adicionarRota(id1, id2, custo);
            std::cout << "T " << consultoria.getNomeRegiao(id1) << ' '
                      << consultoria.getNomeRegiao(id2) << ' ' << custo << '\n';
        }
        else if (comando == "CC")
        {
            int id1;
            int id2;
            std::cin >> id1 >> id2;
            bool conectados = consultoria.saoConectados(id1, id2);
            std::cout << "CC " << consultoria.getNomeRegiao(id1) << ' '
                      << consultoria.getNomeRegiao(id2) << ' '
                      << (conectados ? "SIM" : "NAO") << '\n';
        }
        else if (comando == "F")
        {
            int idCliente;
            int prioridade;
            std::cin >> idCliente >> prioridade;
            consultoria.adicionarFila(prioridade, idCliente);
            std::cout << "F " << consultoria.tamanhoFila() << '\n';
        }
        else if (comando == "Z")
        {
            int quantidade;
            std::cin >> quantidade;
            int atendidos = consultoria.tamanhoFila();
            if (atendidos > quantidade)
            {
                atendidos = quantidade;
            }

            std::cout << "Z " << atendidos << '\n';
            if (atendidos > 0)
            {
                for (int i = 1; i <= atendidos; ++i)
                {
                    ElementoPrioridade atendimento = consultoria.removerFila();
                    if (i > 1)
                    {
                        std::cout << ' ';
                    }
                    std::cout << "atendimento_" << i << ' ' << atendimento.idCliente
                              << ' ' << atendimento.prioridade;
                }
                std::cout << '\n';
            }
        }
    }

    for (int id = 0; id < proximoIdCliente; ++id)
    {
        Cliente *cliente = consultoria.getCliente(id);
        if (cliente != nullptr)
        {
            delete cliente;
        }
    }

    return 0;
}
