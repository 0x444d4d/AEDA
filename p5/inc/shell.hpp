#ifndef SHELL
#define SHELL

#include <vector>
#include <iostream>

template < class Clave >
void shell_sort ( std::vector<Clave>& Vect, unsigned int size ) {

    for ( unsigned int gap = size/2; gap > 0; gap /= 2 ) {
        for ( unsigned int i = gap; i < size; ++i ) {

            Clave temp = Vect[i];
            int j;

            for ( j = i; ( j >= gap ) && ( Vect[j - gap] > temp ); j -= gap ) {
                Vect[j] = Vect[j - gap];
            }

            Vect[j] = temp;
        }
    }
}

#endif
