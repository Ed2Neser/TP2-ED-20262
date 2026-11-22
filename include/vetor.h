#ifndef VETOR_H
#define VETOR_H

#include <stdexcept>

template <typename T>
class Vetor
{
protected:
    T *elementos;
    int capacidade;
    int tamanho;

    void redimensionar();

public:
    Vetor();
    Vetor(int C);
    ~Vetor()
    {
        delete[] elementos;
    };

    T &operator[](int i);             // substituindo [] (por conveniencia da minha parte)
    const T &operator[](int i) const; // substituindo [] (por conveniencia da minha parte) para const

    // getters
    int getTamanho() const;
    int getCapacidade() const;
    T last() const; // retorna v[tamanho - 1] (ultimo elemento do vetor)

    // push back
    void adicionar(const T &novo);

    void removerUltimo();
};

#endif