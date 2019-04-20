#ifndef SHAKE
#define SHAKE
#include <vector>
#include <iostream>

//PENDIENTE cambiar a metodo comun (usado por select y shake )
template< class Clave >
unsigned int find_min ( std::vector<Clave>& Vect, unsigned int left, unsigned int right ) {
  unsigned int min = left;
  for ( unsigned int i = left; i <= right; ++i) {
    if ( Vect[i] < Vect[min] ) min = i;
  }
  
  return min;
}


template < class Clave >
unsigned int find_max ( std::vector<Clave>& Vect, unsigned int left, unsigned int right ) {
  unsigned int max = right;
  for ( unsigned int i = right; i >= left; --i) {
    if ( Vect[i] > Vect[max] ) max = i;
  }
  
  return max;
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
void move_back ( std::vector<Clave>& Vect, unsigned int right,  unsigned int pos) {
  
  if ( pos < right ) {
    Clave aux = Vect[pos];

    //no usar i como unsigned, genera sigsev a causa del underflow.
    for (long i = pos; i < right; ++i ) {
      Vect[i] = Vect[i+1];
    }

    Vect[right] = aux;
  }
}


template < class Clave >
void shake_sort ( std::vector<Clave>& Vect, unsigned int right ) {
  unsigned int left = 0;
  --right;
  while ( left < right ) {
    move_front( Vect, left, find_min( Vect, left, right ) );
    ++left;
    move_back( Vect, right,  find_max( Vect, left, right) );
    --right;


    #ifdef DEM
    std::cout << "Iteracion: " << left << std::endl;

    for (int i = 0; i < Vect.size(); ++i ) {
      std::cout << i << ":  " << Vect[i] << std::endl;
    }   

    std::cout << "pulsa una tecla para continuar con la traza" << std::endl;
    std::cin.get();
    #endif
  }
}

#endif
