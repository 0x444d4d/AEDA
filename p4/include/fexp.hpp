#pragma once

#include "dni-t.hpp"

namespace aeda{

template < class T >
class FExploracionBase {

    protected:
    uint16_t size_;

    public:
    FExploracionBase( uint16_t size ) : size_(size) {}
    virtual uint16_t operator()(const T&, const uint16_t i) = 0 ;
    
};


//Exp. Lineal
template < class T >
class FExploracionLineal : public FExploracionBase<T> {
    public:
    FExploracionLineal( uint16_t size) : FExploracionBase<T>( size ) {}
    uint16_t operator()(const T& clave, const uint16_t i);
};

template < class T >
uint16_t FExploracionLineal<T>::operator()(const T& clave, const uint16_t i) {
    //Linal search here
    return i;
}

//Exp.Cuadratica
template < class T >
class FExploracionCuadratica : public FExploracionBase<T> {
    public:
    FExploracionCuadratica( uint16_t size) : FExploracionBase<T>( size ) {}
    uint16_t operator()(const T&, const uint16_t i);
};

template < class T >
uint16_t FExploracionCuadratica<T>::operator()(const T& clave, const uint16_t i) {
    //Cuadratic search here
    return i * i;
}

//Exp.Doble
template < class T >
class FExploracionDoble : public FExploracionBase<T> {
    public:
    FExploracionDoble( uint16_t size) : FExploracionBase<T>( size ) {}
    uint16_t operator()(const T&, const uint16_t i);
};

template < class T >
uint16_t FExploracionDoble<T>::operator()(const T& clave, const uint16_t i) {
    //Aleatory seach here
    return 0;
}

//Exp.Redispersion
template < class T >
class FExploracionRedispersion : public FExploracionBase<T> {
    public:
    FExploracionRedispersion( uint16_t size) : FExploracionBase<T>( size ) {}
    uint16_t operator()(const T&, const uint16_t i);
};

template < class T >
uint16_t FExploracionRedispersion<T>::operator()(const T& clave, const uint16_t i) {
    //Aleatory seach here
    return 0;
}
}
