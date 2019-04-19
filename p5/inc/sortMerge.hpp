
#ifndef SORT_QUICK
#define SORT_QUICK

#include <random>
#include "sort.hpp"

//Ejecotar pruebas con mismo vector en main.


namespace aeda {

template < class T >
class sort_merge : public sort_base<T> {
    
    private:
    T* vector;

    public:
    sort_merge( uint8_t size = 0 ); 
    ~sort_merge( void ) { delete[] vector; }
    //void resize( uint8_t size );
    void sort( void );

    void mergeSort( uint8_t left, uint8_t middle, uint8_t right);
    void sort( uint8_t left, uint8_t right );
    void swap( uint8_t pos1, uint8_t pos2  );


};

template < class T >
sort_merge<T>::sort_merge ( uint8_t size ) : sort_base<T>::sort_base( size ) {
    vector = new T[size];

    for ( uint8_t i = 0; i < aeda::sort_base<T>::size_; ++i ) {
        vector[i] = T();
    }

}


template < class T >
void sort_merge<T>::sort( void ) {
    sort ( 0, sort_base<T>::size_ );
}

template < class T >
void sort_merge<T>::mergeSort( uint8_t left, uint8_t middle, uint8_t right ) {
    uint8_t pos1 = left;
    uint8_t pos2 = middle;
    
    T* laux = new T[right - middle];
    T* raux = new T[middle + 1 - right];
    
    while ( pos1 < middle && pos2 < right ) {
        if ( laux[pos1] > raux[pos2] ) {
            swap ( pos1, pos2 ); 
            ++pos2;
        } else {
            ++pos1;
        }
    }

    //delete[] laux;
    //delete[] raux;
}

template < class T >
void sort_merge<T>::sort( uint8_t left, uint8_t right ) {
    if ( left < right ) {
        uint8_t middle = ( left + ( right -1 )) / 2;

        sort( left, middle );
        sort( middle + 1, right );

        mergeSort ( left, middle, right);
    }
}

template < class T >
void sort_merge<T>::swap( uint8_t pos1, uint8_t  pos2) {
    T aux = vector[pos1];
    vector[pos1] =  vector[pos2];
    vector[pos2] =  aux;
}


}

#endif
