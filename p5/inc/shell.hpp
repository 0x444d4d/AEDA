#ifndef SHELL
#define SHELL

#include <vector>
#include <iostream>

template < class Clave >
void shell_sort ( std::vector<Clave>& Vect, unsigned int size, float factor = 0.5 ) {
    
    unsigned int delta = size * factor;

    for ( unsigned int gap = size/2; gap > 0; gap *= factor ) {
        for ( unsigned int i = gap; i < size; ++i ) {

            Clave temp = Vect[i];
            int j;

            for ( j = i; ( j >= gap ) && ( Vect[j - gap] > temp ); j -= gap ) {
                Vect[j] = Vect[j - gap];
            }

            Vect[j] = temp;
        }

        #ifdef DEM
        std::cout << "Vector:\n";
        for ( auto a : Vect ) {
            std::cout << a << "\n";
        }

        std::cout << "Pulse una tecla para continuar" << std::flush;
        std::cin.get();

        std::cout << "\n\n\n" << std::flush;
        #endif

    }
}

#endif
