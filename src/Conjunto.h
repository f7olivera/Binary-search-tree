#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

template<class T>
class Conjunto
{
    public:
    // Constructor. Genera un conjunto vacío.
    Conjunto();

    // Destructor. Debe dejar limpia la memoria.
    ~Conjunto();

    // Inserta un elemento en el conjunto. Si este ya existe,
    // el conjunto no se modifica.
    void insertar(const T &);

    // Decide si un elemento pertenece al conjunto o no.
    bool pertenece(const T &) const;

    // Borra un elemento del conjunto. Si este no existe,
    // el conjunto no se modifica.
    void remover(const T &);

    // Siguiente elemento al recibido por párametro, en orden.
    const T &siguiente(const T &elem);

    // Devuelve el mínimo elemento del conjunto según <.
    const T &minimo() const;

    // Devuelve el máximo elemento del conjunto según <.
    const T &maximo() const;

    // Devuelve la cantidad de elementos que tiene el conjunto.
    unsigned int cardinal() const;

    // Muestra el conjunto.
    void mostrar(std::ostream &) const;

    /**
     * Utiliza el método mostrar(os) para sobrecargar el operador <<
     */
    friend ostream &operator<<(ostream &os, Conjunto &c)
    {
        c.mostrar(os);
        return os;
    }


    private:

    struct Nodo
    {
        // El constructor, toma el elemento al que representa el nodo.
        Nodo(const T &v);

        // Puntero a la raíz del subárbol izquierdo.
        Nodo *izq;
        // El elemento al que representa el nodo.
        T valor;
        // Puntero a la raíz del subárbol derecho.
        Nodo *der;
    };

    void mostrarRecursiva(Nodo *raiz, std::ostream &) const;

    // Puntero a la raíz de nuestro árbol.
    Nodo *_raiz;

    // Cantidad de elementos en el conjunto
    unsigned int _cardinal;

    void destruccionRecursiva(Nodo *raiz);
};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) : izq(nullptr), valor(v), der(nullptr) {}

template<class T>
std::ostream &operator<<(std::ostream &os, const Conjunto<T> &c)
{
    c.mostrar(os);
    return os;
}

#include "Conjunto.hpp"

#endif// CONJUNTO_H_
