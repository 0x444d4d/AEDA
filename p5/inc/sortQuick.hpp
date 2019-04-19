
#ifndef SORT_QUICK
#define SORT_QUICK

#include "sort.hpp"


namespace aeda {

template < class T >
class sort_quick : public sort_base<T> {
    
    private:
    T* vector;

    public:
    sort_quick( uint8_t size = 0 ) : sort_base<T>::sort_base( size ) { vector = new T[size]; }
    ~sort_quick( void ) { delete[] vector; }
    void resize( uint8_t size );
    void sort( void );
    void rsort( uint8_t left, uint8_t right );
    uint8_t swap( uint8_t pivot, uint8_t pos );


};

template < class T >
void sort_quick<T>::sort( void ) {
    uint8_t left = 0, right = (sort_base<T>::size_ - 1);
    uint8_t middle = ( (right + left)/2 );

    rsort ( left, middle);
    rsort ( middle + 1, right );

}

template < class T >
void sort_quick<T>::rsort( uint8_t left, uint8_t right ) {

    if ( right <= left ) return;

    uint8_t middle = ( (right + left)/2 );
    uint8_t pivot = ( left + middle ) / 2;

    for ( uint8_t i = left; i < middle; ++i ) {
        if ( vector[i] > vector[pivot] ) 
            pivot = swap ( pivot, i );
    }

    rsort ( left, pivot );
    rsort ( pivot + 1, middle);


    pivot = (middle + 1 + right) / 2;
    for ( uint8_t i = middle + 1; i < right; ++i ) {
        if ( vector[i] > vector[pivot] ) 
            pivot = swap ( pivot, i );
    }

    rsort ( middle + 1, pivot );
    rsort ( pivot + 1, right);

}

template < class T >
uint8_t sort_quick<T>::swap( uint8_t pivot, uint8_t pos ) {
    T aux = vector[pivot];
    vector[pivot] = vector[pos];

    return pos;
}

}

#endif
