#ifndef MERGE
#define MERGE

#include <vector>
#include <iostream>

template < class Clave >
void swap ( std::vector<Clave>& Vect, unsigned int left, unsigned int middle, unsigned int right ) {

  std::vector<Clave> v1( Vect.begin() + left, Vect.begin() + ( middle + 1 ));
  std::vector<Clave> v2( Vect.begin() + (middle + 1), Vect.begin() + ( right + 1 ));

  
  #ifdef DEM
  std::cout << "Vectores:" << std::endl;
  std::cout << "v1: " << v1.size() << std::endl;
  for (auto i : v1 ) {
    std::cout << i << std::endl;
  }   
  std::cout << "v2: " << v2.size() << std::endl;
  for (auto i : v2 ) {
    std::cout << i << std::endl;
  }   

  std::cout << "Pulse una tecla para continuar\n\n\n" << std::flush;
  std::cin.get();
  #endif

  
  unsigned int min = v1.size() < v2.size() ? v1.size() : v2.size();
  unsigned int pos = left;
  unsigned int l = 0, r = 0;

  while ( l < min && r < min) {
    if ( v1[l] < v2[r] ) {
      Vect[left] = v1[l];
      ++l;
      ++left;
    } else {
      Vect[left] = v2[r];
      ++r;
      ++left;
    }
  }

  for (unsigned int i = l; i < v1.size(); ++i ) {
    Vect[left] = v1[i];
    ++left;
  }   

  for (unsigned int i = r; i < v2.size(); ++i ) {
    Vect[left] = v2[i];
    ++left;
  }   


}

template < class Clave >
void divide ( std::vector<Clave>& Vect, unsigned int left, unsigned int right ) {
  unsigned int middle;

  if ( left < right ) {
    middle = ( right + left ) / 2;

    divide( Vect, left, middle );
    divide( Vect, middle + 1, right );

    swap( Vect, left, middle, right );
  }
}

template < class Clave >
void merge_sort ( std::vector<Clave>& Vect, unsigned int size ) {
  divide( Vect, 0, Vect.size() - 1 );
}

#endif
