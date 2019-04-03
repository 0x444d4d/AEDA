#pragma once

#include <vector>
#include "clave-t.hpp"
#include "fdisp.hpp"
#include "fexp.hpp"
#include "contador.hpp"

namespace aeda{

enum Dispersion{ suma, modulo, aleatoria  };
enum Exploracion{ lineal, cuadratica, doble, redispersion };

template< class T >
class Tabla {

    private:
    //Contador count;
    uint16_t size_;
    Celda<T>* vCeldas; //cambiar a puntero de celdas
    FDispersionBase<DNI>* dispersion;
    FExploracionBase<DNI>* exploracion;

    public:
    explicit Tabla( void ) {}
    explicit Tabla(uint16_t n, uint16_t m);
    explicit Tabla(uint16_t n, uint16_t m, Dispersion fdisp, Exploracion fexp);
    //~Tabla(void) { delete vCeldas; }
    void resize( uint16_t n, uint16_t m);
    bool Buscar( T clave );
    bool Insertar( T clave );
};

template< class T>
Tabla<T>::Tabla(uint16_t n, uint16_t m ) : size_(n) {
    //Comprobar rango inferior a uint16_t para m y n
    
    vCeldas = new Celda<T>[n];
    for ( int i = 0; i < n; ++i) {
        vCeldas[i].resize(m);
    }
    dispersion = new FDispersionSuma<DNI> ( n );
    exploracion = new FExploracionLineal<DNI> ( n );
}

template < class T >
Tabla<T>::Tabla(uint16_t n, uint16_t m, Dispersion fdisp, Exploracion fexp ) : size_(n) {
    //Comprobar rango inferior a uint16_t para m y n
    
    vCeldas = new Celda<T>[n];
    for ( int i = 0; i < n; ++i) {
        vCeldas[i].resize(m);
    }
    switch (fdisp) {
        case suma:
            dispersion = new FDispersionSuma<DNI> ( n );
            break;
        case modulo:
            dispersion = new FDispersionModulo<DNI> ( n );
            break;
        case aleatoria:
            dispersion = new FDispersionPAleatoria<DNI> ( n );
            break;
    }

    switch (fexp) {
        case lineal:
            exploracion = new FExploracionLineal<DNI> ( n );
            break;
        case cuadratica:
            exploracion = new FExploracionCuadratica<DNI> ( n );
            break;
        case doble:
            exploracion = new FExploracionDoble<DNI> ( n );
            break;
        case redispersion:
            exploracion = new FExploracionRedispersion<DNI> ( n );
            break;
    }
    exploracion = new FExploracionLineal<DNI> ( n );
}

template < class T >
void Tabla<T>::resize( uint16_t n, uint16_t m) {
    size_ = n;
    if (vCeldas != nullptr){
        delete vCeldas;
        vCeldas = nullptr;
    } 
    vCeldas = new Celda<T>[n];
    for ( int i = 0; i < n; ++i) {
        vCeldas[i].resize(m);
    }
}

template< class T>
bool Tabla<T>::Buscar ( T clave ) {
    uint8_t offset = 0;
    uint16_t celda = (*dispersion) ( clave );
    int8_t max = 0;

    //count++;
    while ( vCeldas[(celda + offset) % size_].Buscar (clave) == false ) {
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
    while ( vCeldas[(celda + offset) % size_].IsFull () ) {
        if ( max++ < 50 )
            offset = (*exploracion) ( clave, offset++ );
        else return false;
    }

    return vCeldas[ celda + offset ].Insertar(clave);
    //return true;

}

}

