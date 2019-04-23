#ifndef HEAP
#define HEAP

#include <iostream>
#include <vector>

template < class Clave >
void swap ( std::vector<Clave>& Vect, unsigned int left, unsigned int right ) {
    Clave aux = Vect[left];
    Vect[left] = Vect[right];
    Vect[right] = aux;
}

template < class Clave >
void heap ( std::vector<Clave>& Vect, unsigned int size, long i ) {
    long largest = i;
    long l = 2*i + 1;
    long r = 2*i + 2;

    if (l < size && Vect[l] > Vect[largest]) largest = l;
    if (r < size && Vect[r] > Vect[largest]) largest = r;
    if (largest != i) {
        swap( Vect, i, largest );
        heap( Vect, size, largest );
    }
}

template < class Clave >
void heap_sort ( std::vector<Clave>& Vect, unsigned int size ) {

    for ( long i = size/2 - 1; i >= 0 ; --i ) {
        heap( Vect, size, i );
    }

    for ( long i = size - 1; i >= 0; --i ) {
        swap(Vect, 0, i);
        heap(Vect, i, 0);
    }

}

#endif
