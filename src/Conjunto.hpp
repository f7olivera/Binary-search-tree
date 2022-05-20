#include "Conjunto.h"
#include <stack>

template<class T>
Conjunto<T>::Conjunto() : _raiz(nullptr), _cardinal(0)
{
}

template<class T>
void Conjunto<T>::destruccionRecursiva(typename Conjunto<T>::Nodo *raiz)
{
    if(raiz != nullptr)
    {
        if(raiz->izq != nullptr)
            destruccionRecursiva(raiz->izq);
        if(raiz->der != nullptr)
            destruccionRecursiva(raiz->der);
        delete raiz;
    }
}

template<class T>
Conjunto<T>::~Conjunto()
{
    destruccionRecursiva(_raiz);
}


template<class T>
bool Conjunto<T>::pertenece(const T &clave) const
{
    bool pertenece = false;
    Nodo *actual = _raiz;
    while(!pertenece and actual != nullptr)
    {
        pertenece = actual->valor == clave;
        actual = clave < actual->valor ? actual->izq : actual->der;
    }
    return pertenece;
}

template<class T>
void Conjunto<T>::insertar(const T &clave)
{
    Nodo *actual = _raiz;
    Nodo *anterior = _raiz;
    while(actual != nullptr and actual->valor != clave)
    {
        anterior = actual;
        actual = clave < actual->valor ? actual->izq : actual->der;
    }
    if(actual == nullptr)
    {
        if(anterior == nullptr)
            _raiz = new Nodo(clave);
        else
        {
            if(clave < anterior->valor)
                anterior->izq = new Nodo(clave);
            else
                anterior->der = new Nodo(clave);
        }
        _cardinal++;
    }
}

template<class T>
void Conjunto<T>::remover(const T &clave)
{
    Nodo *actual = _raiz;
    Nodo *anterior = _raiz;
    while(actual != nullptr and actual->valor != clave)
    {
        anterior = actual;
        actual = clave < actual->valor ? actual->izq : actual->der;
    }
    if(actual != nullptr)
    {
        if(actual->izq == nullptr and actual->der == nullptr)
        {
            if(anterior == actual)
                _raiz = nullptr;
            else if(clave < anterior->valor)
                anterior->izq = nullptr;
            else
                anterior->der = nullptr;
            delete actual;
        }
        else if(actual->izq == nullptr)
        {
            if(anterior == actual)
                _raiz = actual->der;
            else if(clave < anterior->valor)
                anterior->izq = actual->der;
            else
                anterior->der = actual->der;
            delete actual;
        }
        else if(actual->der == nullptr)
        {
            if(anterior == actual)
                _raiz = actual->izq;
            else if(clave < anterior->valor)
                anterior->izq = actual->izq;
            else
                anterior->der = actual->izq;
            delete actual;
        }
        else
        {
            Nodo *sucesor = actual->der;
            while(sucesor->izq != nullptr)
            {
                sucesor = sucesor->izq;
            }
            int tmp = sucesor->valor;
            remover(sucesor->valor);
            _cardinal++;
            actual->valor = tmp;
        }
        _cardinal--;
    }
}

template<class T>
const T &Conjunto<T>::siguiente(const T &clave)
{
    Nodo *actual = _raiz;
    while(actual->valor != clave)
    {
        actual = clave < actual->valor ? actual->izq : actual->der;
    }
    Nodo *sucesor = actual->der;
    if(sucesor != nullptr)
    {
        while(sucesor->izq != nullptr)
        {
            sucesor = sucesor->izq;
        }
    }
    else
        sucesor = _raiz;
    return sucesor->valor;
}

template<class T>
const T &Conjunto<T>::minimo() const
{
    Nodo *actual = _raiz;
    while(actual->izq != nullptr)
    {
        actual = actual->izq;
    }
    return actual->valor;
}

template<class T>
const T &Conjunto<T>::maximo() const
{
    Nodo *actual = _raiz;
    while(actual->der != nullptr)
    {
        actual = actual->der;
    }
    return actual->valor;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const
{
    return _cardinal;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &o) const
{
    o << "{";
    mostrarRecursiva(_raiz, o);
    o << "}";
}

template<class T>
void Conjunto<T>::mostrarRecursiva(typename Conjunto<T>::Nodo *raiz, std::ostream &o) const
{
    if(raiz != nullptr)
    {
        if(raiz->izq != nullptr)
        {
            mostrarRecursiva(raiz->izq, o);
            o << ", ";
        }
        if(raiz->der != nullptr)
        {
            mostrarRecursiva(raiz->der, o);
            o << ", ";
        }
        o << raiz->valor;
    }
}
