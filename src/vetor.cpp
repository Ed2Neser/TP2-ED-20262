#include "../include/vetor.h"
#include "../include/fila_prioridade.h"

template <typename T> // Construtor generico
Vetor<T>::Vetor() : elementos(nullptr), capacidade(0), tamanho(0)
{
}

template <typename T> // Construtor com capacidade
Vetor<T>::Vetor(int C) : elementos(nullptr), capacidade(C), tamanho(0)
{
    elementos = new T[capacidade];
}

template <typename T> // Getter de tamanho
int Vetor<T>::getTamanho() const
{
    return tamanho;
}

template <typename T> // getter de capacidade
int Vetor<T>::getCapacidade() const
{
    return capacidade;
}

template <typename T> // redimensiona o vetor se necessário, tornando ele dinamico
void Vetor<T>::redimensionar()
{
    if (tamanho < capacidade)
        return; // se houver espaço, n tem pq redimensionar
    capacidade = (capacidade == 0) ? 1 : capacidade * 2;
    T *novosElementos = new T[capacidade];

    for (int i = 0; i < tamanho; ++i)
    {
        novosElementos[i] = elementos[i];
    }

    delete[] elementos;
    elementos = novosElementos;
}

template <typename T> // push back (adiciona no final)
void Vetor<T>::adicionar(const T &novo)
{
    redimensionar();
    elementos[tamanho++] = novo;
}

template <typename T>
void Vetor<T>::removerUltimo()
{
    if (tamanho > 0)
    {
        --tamanho;
    }
}

template <typename T>
T Vetor<T>::last() const
{
    if (tamanho == 0)
    {
        throw std::out_of_range("Vetor vazio");
    }
    return elementos[tamanho - 1];
}

template <typename T>
T &Vetor<T>::operator[](int i)
{
    if (i >= tamanho)
    {
        throw std::out_of_range("Indice fora dos limites");
    }
    return elementos[i];
}

template <typename T>
const T &Vetor<T>::operator[](int i) const
{
    if (i >= tamanho)
    {
        throw std::out_of_range("Indice fora dos limites");
    }
    return elementos[i];
}

// Links
template class Vetor<ElementoPrioridade>;