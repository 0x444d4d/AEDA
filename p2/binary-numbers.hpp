#pragma once

#define DEBG

#include "numbers.hpp"
//#include "numbers-helpers.hpp"

#include <vector>
#include <iostream>
#include <stdexcept>


//PENDIENTE: ;
//Resta de negativos.
//Suma de negativos.

template <size_t N, class T>
class numbers<N,2,T>{

  private:
  T* number_;
  //bool negative_;
  unsigned short size_;
  
  public:

  numbers( void );
  explicit numbers( const int number );
  numbers( const numbers<N,2,T>& old);
  //~numbers( void );

  numbers<2*N,2,T> mul( numbers<N,2,T> A );
  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,2,T>& A ) const;
  bool operator>( const numbers<N,2,T>& A ) const;
  bool operator==( const numbers<N,2,T>& A ) const;
  bool operator!=( const numbers<N,2,T>& A ) const;
  numbers<N,2,T> operator+( const numbers<N,2,T>& A);
  numbers<N,2,T> operator-( const numbers<N,2,T>& A);
  numbers<N,2,T>& operator=( const numbers<N,2,T>& A );

  private:

  void to_base( int input, unsigned pos = 0);
  void complement( void );
  void fill( int i );
  bool less_than( numbers<N,2,T> A ) const;
  bool equals( numbers<N,2,T> A ) const;
  numbers<N, 2, T> sum( const numbers<N,2,T> A ) const;
  numbers<N,2,T>& copy( const numbers<N,2,T>& old );
 
};



template <size_t N, class T>
numbers<N, 2, T>::numbers(void):size_(0) {
  number_ = new T[N];
  fill(0);
}

//constructor
template <size_t N, class T>
numbers<N, 2, T>::numbers(const int number):size_(0) {

    number_ = new T[N];

    if ( number_ == NULL) 
      throw std::bad_alloc();
    else {
      fill(0);

      if ( number < 0 ) {
        to_base( -number );
        complement();
      }
      else{
        to_base( number );
      }
    }
}

//constructor de copia
template <size_t N, class T>
numbers<N,2,T>::numbers(const numbers<N,2,T>& old) {
  copy(old);
}



//destructor
template <size_t N, class T>
numbers<N,2,T>::~numbers(void) noexcept(false) {
  
  if ( number_ != NULL ) {
    delete number_;
    number_ = NULL;
  } else {
    throw "Double free";
  }
  
}


//fill
template <size_t N, class T>
void numbers<N,2,T>::fill( int i ) {
  for (int inx = 0; inx < N; ++inx)
    number_[inx] = i;
}


//to_base
template <size_t N, class T>
void numbers<N, 2, T>::to_base(int input, unsigned pos ) {
  if ( input < 2 ) {
    number_[pos] = input;
    ++size_;
  }
  else {
    number_[pos]  = input % 2;
    ++size_;
    input = input / 2;
    to_base( input, ++pos );
  }
}


template <size_t N, class T>
void numbers<N,2,T>::complement( void ) {
  bool neg_flag = false;
  for (unsigned short inx = 0; inx < N; ++inx ) {
    if ( neg_flag ) {
      if ( number_[inx] == 0  ) number_[inx] = 1;
      else number_[inx] = 0;
    } else {
      if ( number_[inx] == 1 ) neg_flag = true;
    }
  } 
}

//sum
template <size_t N, class T>
numbers<N, 2, T> numbers<N, 2, T>::sum( const numbers A ) const {
  numbers<N, 2, T> C; //resultado de la suma.
  size_t result_size = size_ < A.size_ ? A.size_ : size_; //tamaño del resultado.
  unsigned aux; //resultado de la suma de dos digitos.
  uint_fast8_t carry = 0;
  unsigned short inx;


  for ( inx = 0; inx < N; ++inx ) {

    aux = A.number_[inx] + number_[inx] + carry;
    
    carry = 0;

    if ( aux < 2 ) {
      C.number_[inx] = aux;
      ++C.size_;
    } else {
      C.number_[inx] = ( aux - 2 );
      ++C.size_;
      carry = 1;
    }
  }

  if ( carry == 1 ) {

  }
  return C;
}

template< size_t N, class T>
numbers<N,2,T>& numbers<N,2,T>::copy( const numbers<N,2,T>& old) {
  size_ = old.size_;
  number_ = new T[N];

  if ( number_ == NULL) 
    throw "Could not create array";
  else {
    for (int inx = 0; inx < N; ++inx)
      number_[inx] = old.number_[inx];
  }

  return *this;
}

//write
template <size_t N, class T>
std::ostream& numbers<N, 2, T>::write( std::ostream& os ) const {
  if ( size_ == 0 ) {
    os << 0;
  } else {
    for (int inx = (N - 1); inx >= 0; --inx ){
      os << int_to_char( number_[inx] );
    }
  }

  fflush(stdout);
  return os;
}


template<size_t N, class T> 
bool numbers<N,2,T>::less_than(numbers A) const {
  if ( size_ < A.size_ ) return true;
  if ( size_ == A.size_ ) {
    for( int inx = (size_ - 1); inx >= 0; --inx) {
      if ( number_[inx] < A.number_[inx] ) return true;
      if ( number_[inx] > A.number_[inx] ) return false;
    }
  }
  return false;
}



template<size_t N, class T> 
bool numbers<N,2,T>::equals(numbers A) const {
  if ( size_ == A.size_ ) {
    for ( int inx = 0; inx < size_; ++inx )
      if ( number_[inx] != A.number_[inx] ) return false;
    return true;
  }
  return false;
}



template< size_t N, class T>
bool numbers<N,2,T>::operator<( const numbers& A ) const {
  return less_than( A );
}

template< size_t N, class T>
bool numbers<N,2,T>::operator>( const numbers& A ) const {
  if ( !equals(A) ) return !less_than( A );
  return false;
}

template< size_t N, class T>
bool numbers<N,2,T>::operator==( const numbers& A ) const {
  return equals( A );
}

template< size_t N, class T>
numbers<N,2,T>& numbers<N,2,T>::operator=( const numbers& A ) {
  return copy(A);
}

template< size_t N, class T>
bool numbers<N,2,T>::operator!=( const numbers& A ) const {
  return !equals( A );
}

template< size_t N, class T>
numbers<N,2,T> numbers<N,2,T>::operator+( const numbers& A ) {
  return sum( A );
}

template< size_t N, class T>
numbers<N,2,T> numbers<N,2,T>::operator-( const numbers& A ) {
  numbers<N,2,T> X(A);
  
  if ( A.number_[N - 1] == 1 ) {
    X.complement();
    return sum(X); 
  } else return sum( A );
}

template< size_t N, class T>
std::ostream& operator<<(std::ostream& os, const numbers<N,2,T>& A) {
  return A.write(os);
}

