#pragma once

#include"dni-t.hpp"

namespace aeda{

template< class T >
class FDispersionBase {

    protected:
    uint16_t size_;

    public:
    FDispersionBase( uint16_t size ) : size_(size) {}
    virtual uint16_t operator()( T& ) = 0;
    
};


//Dis. Truncamiento
template < class T >
class FDispersionPAleatoria: public FDispersionBase<T> {

    public:
    FDispersionPAleatoria( uint16_t size ) : FDispersionBase<T>(size) {}
    uint16_t operator()( T& );
};

template < class T >
uint16_t FDispersionPAleatoria<T>::operator()( T& clave) {
    //truncar con 6
    srand((long unsigned)clave);
    return rand() % FDispersionBase<T>::size_;
}

//Dis. Modulo
template < class T >
class FDispersionModulo : public FDispersionBase<T> {

    public:
    FDispersionModulo(uint16_t size) : FDispersionBase<T>(size) {}
    uint16_t operator()(T& clave);
};

template < class T >
uint16_t FDispersionModulo<T>::operator()( T& clave) {
    return (unsigned long)clave % FDispersionBase<T>::size_;
}

//Dis. Suma
template < class T >
class FDispersionSuma : public FDispersionBase<T> {

    public:
    FDispersionSuma(uint16_t size) : FDispersionBase<T>(size) {}
    uint16_t operator()(T& clave);
    
};

template < class T >
uint16_t FDispersionSuma<T>::operator()( T& clave) {
    unsigned long y = 0;
    unsigned long x = (unsigned long)clave;
    while (x > 0) { 
        y += x % 10;
        x /= 10;
    } 
    return(y % FDispersionBase<T>::size_);
}
}
