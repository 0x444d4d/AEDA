#pragma once

#include <iostream>
#include <vector>
#include "dni-t.hpp"
#include "contador.hpp"

namespace aeda {

template < class T >
class Celda {

    private:
    Contador count;
    //std::vector< T > vClave;
    T* vClave;
    uint8_t size_;
    uint8_t nDNI_;

    public:
    Celda() : nDNI_(0) {}
    Celda(uint16_t size) : nDNI_(0), size_(size) { vClave = new T[size]; }
    //~Celda(void) { delete vClave; }
    void resize( uint16_t size ) { vClave = new T[size]; size_ = size; }
    bool Buscar( T clave );
    bool Insertar( T clave );
    bool IsFull( void );

};

template < class T >
bool Celda<T>::Buscar( T clave ){
    //for ( auto  claveHash : vClave ) {
    for (int i = 0; i < nDNI_; ++i) {
        //count++;
        if (clave == vClave[i] ) {
            return true;
        }
    }
    return false;
}

template < class T >
bool Celda<T>::Insertar( T clave ) {
    if ( IsFull () ) {
        return false;
    } else {
        vClave[++nDNI_] = clave;
        return true;
    }
}

template < class T >
bool Celda<T>::IsFull ( void ) {
    //count++;
    //if ( nDNI_ == vClave.size () )
    if ( nDNI_ >= size_ )
        return true;
    else 
        return false;
}
}
