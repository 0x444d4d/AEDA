#pragma once

#define DEBG

#include <vector>
#include <iostream>
#include <stdexcept>

#include "numbers-helpers.hpp"

//PENDIENTE: clear();
//Resta de negativos.
//Suma de negativos.

template <size_t N, size_t B, class T = char>
class numbers{

  private:
  T* number_;
  bool negative_;
  unsigned short size_;
  
  public:

  explicit numbers( const std::string& number = "0");
  numbers( const numbers<N,B,T>& old);
  ~numbers( void );

  numbers<2*N, B, T> mul( numbers<N,B,T> A );
  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,B,T>& A ) const;
  bool operator>( const numbers<N,B,T>& A ) const;
  bool operator==( const numbers<N,B,T>& A ) const;
  bool operator!=( const numbers<N,B,T>& A ) const;
  numbers<N,B,T> operator+( const numbers<N,B,T>& A);
  numbers<N,B,T> operator-( const numbers<N,B,T>& A);

  private:

  void to_base( int input, unsigned pos = 0);
  void clear(void);
  bool less_than( numbers<N,B,T> A ) const;
  bool equals( numbers<N,B,T> A ) const;
  numbers<N, B, T> sum( const numbers<N,B,T> A ) const;
  numbers<N, B, T> sub( const numbers<N,B,T> A ) const;
  
};



//constructor
template <size_t N, size_t B, class T>
numbers<N, B, T>::numbers(const std::string& number):size_(0) {
  if ( B < 2 ) {
    throw "exception, base cant be lower than 2";
  }

  if ( check_string(number) ) {

    if ( number[0] == '-' ) negative_ = true;
    else negative_ = false;
            

    number_ = new T[N];

    if ( number[0] == '-' || number[0] == '+' )
      to_base( std::stoi( std::string (number.begin() + 1, number.end() )));
    else
      to_base( std::stoi( number ));

    fflush(stdout);
  } else {
    throw "Invalid number sent to constructor";
  }

}

//constructor de copia
template <size_t N, size_t B, class T>
numbers<N,B,T>::numbers(const numbers<N,B,T>& old) {
  size_ = old.size_;
  negative_ = old.negative_;
  number_ = new T[N];

  for (int inx = 0; inx < size_; ++inx)
    number_[inx] = old.number_[inx];
}

//destructor
template <size_t N, size_t B, class T>
numbers<N,B,T>::~numbers(void) {
  //delete number_;
}

//to_base
template <size_t N, size_t B, class T>
void numbers<N, B, T>::to_base(int input, unsigned pos ) {
  if ( input < B ) {
    number_[pos] = int_to_char(input);
    ++size_;
  }
  else {
    number_[pos]  = int_to_char(input % B);
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
  bool carry = false;
  unsigned short inx;

  /*
  if ( B != A.B ) {
    //Throw exeption, base not equal.
  }
  */

  for ( inx = 0; inx < result_size; ++inx ) {

    if ( inx < A.size_ && inx < size_ )
      aux = char_to_int( A.number_[inx] ) + char_to_int( number_[inx] );
    else if ( inx < size_ ) 
      aux = char_to_int( number_[inx] );
    else 
      aux = char_to_int( A.number_[inx] );
    

    if ( carry ) {
      ++aux;
      carry = false;
    }

    if ( aux < B ) {
      C.number_[inx] = int_to_char(aux);
      ++C.size_;
    } else {
      C.number_[inx] = int_to_char( aux - B );
      ++C.size_;
      carry = true;
    }
  }

  if ( carry ) {

    if ( inx >= N ) {
      throw "out of size: number to big for array size";
    } else {
      C.number_[inx] = int_to_char(1) ;
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
  bool carry = false;
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
      aux = char_to_int( X.number_[inx] ) - char_to_int( Y.number_[inx] );
    } else if ( inx < X.size_ ) {
      aux = char_to_int( X.number_[inx] );
    } else  {
      aux = char_to_int( Y.number_[inx] );
    }

    if ( carry ) --aux;

    if ( aux < 0 ) {
      aux += B;
      C.number_[inx] = int_to_char( aux );
      ++C.size_;
      carry = true;
    } else {
       
      C.number_[inx] = int_to_char( aux );
      ++C.size_;
      carry = false;
    }
  }
    
  for (int inx = (C.size_ - 1); inx >= 0; --inx ) {
    if ( check_char_range( C.number_[inx] ) == false ) --C.size_;
    else {
      if ( char_to_int(C.number_[inx]) == 0  ) --C.size_;
      else break;
    }
  }   
  return C;
}

//write
template <size_t N, size_t B, class T>
std::ostream& numbers<N, B, T>::write( std::ostream& os ) const {
  if ( negative_ ) os << "-";
  if ( size_ == 0 ) {
    os << 0;
  } else {
    for (int inx = (size_ - 1); inx >= 0; --inx ){
      os << number_[inx];
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
bool numbers<N,B,T>::operator!=( const numbers& A ) const {
  return !equals( A );
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator+( const numbers& A ) {
  return sum( A );
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator-( const numbers& A ) {
  return sub( A );
}

template< size_t N, size_t B, class T>
std::ostream& operator<<(std::ostream& os, const numbers<N,B,T>& A) {
  return A.write(os);
}
