#pragma once

#include <vector>
#include "clave-t.hpp"
#include "fdisp.hpp"
#include "fexp.hpp"
#include "contador.hpp"

namespace aeda{

template< class T >
class Tabla {

    private:
    Contador count;
    std::vector<Celda<T> > vCeldas; //cambiar a puntero de celdas
    FDispersionBase<DNI>* dispersion;
    FExploracionBase<DNI>* exploracion;

    public:
    Tabla(uint16_t n, uint16_t m);
    bool Buscar( T clave );
    bool Insertar( T clave );
};

template< class T>
Tabla<T>::Tabla(uint16_t n, uint16_t m) {
    //Comprobar rango inferior a uint16_t para m y n
    
    vCeldas.resize (n);
    for ( int i = 0; i < n; ++i) {
        vCeldas[i].resize(m);
    }
    dispersion = new FDispersionSuma<DNI> ( n );
    exploracion = new FExploracionLineal<DNI> ( n );
}

template< class T>
bool Tabla<T>::Buscar ( T clave ) {
    uint8_t offset = 0;
    uint16_t celda = (*dispersion) ( clave );
    int8_t max = 0;

    //count++;
    while ( vCeldas[(celda + offset) % vCeldas.size()].Buscar (clave) == false ) {
        if (max++ < 50)
            offset += (*exploracion) ( clave, offset++ );
        else return false;
    }
    return true;

}

template< class T >
bool Tabla<T>::Insertar( T clave ) {
    uint8_t offset = 0;
    uint16_t celda = (*dispersion) ( clave );
    int8_t max = 0;

    //count++;
    while ( vCeldas[(celda + offset) % vCeldas.size()].IsFull () ) {
        if ( max++ < 50 )
            offset = (*exploracion) ( clave, offset++ );
        else return false;
    }

    return vCeldas[ celda + offset ].Insertar(clave);
    //return true;

}

}

