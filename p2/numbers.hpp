#pragma once

#define DEBG

#include <vector>
#include <iostream>
#include <stdexcept>

#include "number_exeptions.hpp"
#include "numbers-helpers.hpp"


template <size_t N, size_t B, class T = char>
class numbers{

  private:
  T* number_;
  bool negative_;
  unsigned short size_;
  
  public:

  numbers( void ): size_(0), negative_(false) { number_ = new T[N]; }
  explicit numbers( const int number );
  numbers( const numbers<N,B,T>& old);
  ~numbers( void );

  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,B,T>& A ) const;
  bool operator>( const numbers<N,B,T>& A ) const;
  bool operator==( const numbers<N,B,T>& A ) const;
  bool operator!=( const numbers<N,B,T>& A ) const;
  numbers<N,B,T> operator+( const numbers<N,B,T>& A);
  numbers<N,B,T> operator-( const numbers<N,B,T>& A);
  numbers<N,B,T>& operator=( const numbers<N,B,T>& A );

  private:

  void to_base( int input, unsigned pos = 0);
  numbers<N,B,T>& copy( const numbers<N,B,T>& old );
  bool less_than( numbers<N,B,T> A ) const;
  bool equals( numbers<N,B,T> A ) const;
  numbers<N, B, T> sum( const numbers<N,B,T> A ) const;
  numbers<N, B, T> sub( const numbers<N,B,T> A ) const;
  
};


//constructor
template <size_t N, size_t B, class T>
numbers<N, B, T>::numbers(const int number):size_(0) {
  if ( B < 2 ) {
    throw base_exception(); 
  }
  if ( number < 0 ) negative_ = true;
  else negative_ = false;
  
  number_ = new T[N];
  
  if ( number_ == NULL) throw "Could not create array";
  else {
    if ( number < 0 ) to_base( -number );
    else to_base( number );
  }
}

//constructor de copia
template <size_t N, size_t B, class T>
numbers<N,B,T>::numbers(const numbers<N,B,T>& old) {
  copy(old);
}


//destructor
template <size_t N, size_t B, class T>
numbers<N,B,T>::~numbers(void) noexcept(false) {
  
  if ( number_ != NULL ) {
    delete number_;
    number_ = NULL;
  } else {
    throw double_free();
  }
  
}

//to_base
template <size_t N, size_t B, class T>
void numbers<N, B, T>::to_base(int input, unsigned pos ) {
  if ( input < B ) {
    number_[pos] = input;
    ++size_;
  }
  else {
    number_[pos]  = input % B;
    ++size_;
    input = input / B;
    to_base( input, ++pos );
  }
}

//sum
template <size_t N, size_t B, class T>
numbers<N, B, T> numbers<N, B, T>::sum( const numbers A ) const {
  numbers<N, B, T> C; //resultado de la suma.
  size_t result_size = size_ < A.size_ ? A.size_ : size_; //tamaño del resultado.
  unsigned aux; //resultado de la suma de dos digitos.
  uint_fast8_t carry = 0;
  unsigned short inx;


  for ( inx = 0; inx < result_size; ++inx ) {

    if ( inx < A.size_ && inx < size_ )
      aux = A.number_[inx] + number_[inx] + carry;
    else if ( inx < size_ ) 
      aux = number_[inx] + carry;
    else 
      aux = A.number_[inx] + carry;
    
    carry = 0;

    if ( aux < B ) {
      C.number_[inx] = aux;
      ++C.size_;
    } else {
      C.number_[inx] = ( aux - B );
      ++C.size_;
      carry = 1;
    }
  }

  if ( carry ) {

    if ( inx >= N ) {
      throw out_of_range();
    } else {
      C.number_[inx] = 1;
      ++C.size_;
    }
  }
  return C;
}

//sub
template <size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::sub( const numbers A ) const {
  numbers<N,B,T> X,Y,C;
  size_t result_size = size_ < A.size_ ? A.size_ : size_;
  uint_fast8_t borrow = 0;
  int aux = 0;

  if ( less_than(A) ) {
    C.negative_ = true;

    X = A;
    Y = *this;
  } else {
    C.negative_ = false;

    X = *this;
    Y = A;
  }


  C.size_ = 0;

  for ( int inx = 0; inx < result_size; ++inx ) {

    if ( inx < X.size_ && inx < Y.size_ ) {
      aux =  X.number_[inx] - Y.number_[inx] - borrow;
    } else if ( inx < X.size_ ) {
      aux = X.number_[inx] - borrow;
    } else  {
      aux = Y.number_[inx] - borrow;
    }

    //if ( borrow ) --aux;

    if ( aux < 0 ) {
      aux += B;
      C.number_[inx] = aux;
      ++C.size_;
      borrow = 1;
    } else {
       
      C.number_[inx] = aux;
      ++C.size_;
      borrow = 0;
    }
  }
    
  for (int inx = (C.size_ - 1); inx >= 0; --inx ) {
    if ( C.number_[inx] == 0 ) --C.size_;
    else break;
  }

  return C;
}

template< size_t N, size_t B, class T>
numbers<N,B,T>& numbers<N,B,T>::copy( const numbers<N,B,T>& old) {
  size_ = old.size_;
  negative_ = old.negative_;
  number_ = new T[N];

  if ( number_ == NULL) 
    throw std::bad_alloc();
  else {
    for (int inx = 0; inx < size_; ++inx)
      number_[inx] = old.number_[inx];
  }

  return *this;
}

//write
template <size_t N, size_t B, class T>
std::ostream& numbers<N, B, T>::write( std::ostream& os ) const {
  if ( negative_ ) os << "-";
  if ( size_ == 0 ) {
    os << 0;
  } else {
    for (int inx = (size_ - 1); inx >= 0; --inx ){
      os << int_to_char( number_[inx] );
    }
  }

  fflush(stdout);
  return os;
}

template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::less_than(numbers A) const {
  if ( size_ < A.size_ ) return true;
  if ( size_ == A.size_ ) {
    for( int inx = (size_ - 1); inx >= 0; --inx) {
      if ( number_[inx] < A.number_[inx] ) return true;
      if ( number_[inx] > A.number_[inx] ) return false;
    }
  }
  return false;
}

template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::equals(numbers A) const {
  if ( size_ == A.size_ ) {
    for ( int inx = 0; inx < size_; ++inx )
      if ( number_[inx] != A.number_[inx] ) return false;
    return true;
  }
  return false;
}



template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator<( const numbers& A ) const {
  return less_than( A );
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator>( const numbers& A ) const {
  if ( !equals(A) ) return !less_than( A );
  return false;
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator==( const numbers& A ) const {
  return equals( A );
}

template< size_t N, size_t B, class T>
numbers<N,B,T>& numbers<N,B,T>::operator=( const numbers& A ) {
  return copy(A);
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator!=( const numbers& A ) const {
  return !equals( A );
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator+( const numbers& A ) {
  numbers<N,B,T> X;

  if (!negative_ && A.negative_ ) {
    X = A;
    return sub(X);
  } else if ( !negative_ && !A.negative_ ) {
    return sum(A);
  } else if ( negative_ && A.negative_ ) {
    X = sum(A);
    X.negative_ = true;
    return X;

  } else if ( negative_ && !A.negative_ ) {
    return A.sub(*this);
  }
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator-( const numbers& A ) {
  numbers<N,B,T> X;

  if (!negative_ && A.negative_ ) {
    X = A;
    return sum(X);
  } else if ( !negative_ && !A.negative_ ) {
    return sub(A);
  } else if ( negative_ && A.negative_ ) {
    return sub(A);
  } else if ( negative_ && !A.negative_ ) {
    X = A.sum(*this);
    X.negative_ = true;
    return X;
  }
}

template< size_t N, size_t B, class T>
std::ostream& operator<<(std::ostream& os, const numbers<N,B,T>& A) {
  return A.write(os);
}

