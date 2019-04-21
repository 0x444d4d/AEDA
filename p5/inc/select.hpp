#ifndef SELECT
#define SELECT
#include <vector>
#include <iostream>
//Requirements for Clave:
//operator >
//operator <
//operator =


template< class Clave >
unsigned int find_min ( std::vector<Clave>& Vect, unsigned int left ) {
  unsigned int min = left;
  for ( unsigned int i = left; i < Vect.size(); ++i) {
    if ( Vect[i] < Vect[min] ) min = i;
  }
  
  return min;
}


template< class Clave >
void move_front ( std::vector<Clave>& Vect, unsigned int left,  unsigned int pos) {
  
  if ( pos > left ) {
    Clave aux = Vect[pos];

    //no usar i como unsigned, genera sigsev a causa del underflow.
    for (long i = (pos - 1); i >= left; --i ) {
      Vect[i+1] = Vect[i];
    }

    Vect[left] = aux;
  }
}


template< class Clave >
void select_sort ( std::vector<Clave>& Vect, unsigned int size ) {

  unsigned int left = 0;

  while ( left < size ) {
    move_front( Vect, left, find_min(Vect, left) );
    left++;

    #ifdef DEM
    std::cout << "Iteracion: " << left << std::endl;

    for (int i = 0; i < size; ++i ) {
      std::cout << i << ":  " << Vect[i] << std::endl;
    }   

    std::cout << "pulsa una tecla para continuar con la traza" << std::endl;
    std::cin.get();
    #endif

  }
}


#endif
