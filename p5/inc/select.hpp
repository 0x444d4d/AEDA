#ifndef SELECT
#define SELECT
#include <vector>
//Requirements for Clave:
//operator <
//operator =

template< class Clave >
bool select_sort<Clave> ( std::vector<Clave> Vect, unsigned int left, unsigned int size );

template< class Clave >
void move_front ( std::vector<Clave> Vect, unsigned int left, unsigned int pos);

template< class Clave >
unsigned int find_min ( std::vector<Clave> Vect );



template< class Clave >
bool select_sort<Clave> ( std::vector<Clave> Vect, unsigned int size ) {
  unsigned int left = 0, right = Vect.size() - 1;
  
  while ( left < right ) {
    move_front( Vect, left, find_min(Vect, left) );
    left++;
  }

  return true;
}


template< class Clave >
void move_front ( std::vector<Clave> Vect, unsigned int left,  unsigned int pos) {
  Clave aux = Vect[pos];
  
  for (unsigned int i = (pos - 1); i >= left; --i ) {
    Vect[i+1] = Vect[i];
  }   
}

template< class Clave >
unsigned int find_min ( std::vector<Clave> Vect, unsigned int left ) {
  unsigned int min = 0;
  for ( unsigned int i = left; i < Vect.size(); ++i) {
    if ( Vect[i] < Vect[min] ) min = i;
  }
  
  return min;
}


#endif
