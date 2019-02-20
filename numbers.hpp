#pragma once

#define DEBG

#include <vector>
#include <iostream>

template <size_t N, size_t B, class T = char>
class numbers{

  private:
  char number_[N];
  unsigned short size_;
  
  public:
  numbers(void):size_(0) {};
  explicit numbers( const std::string& number );
  ~numbers(void) {}

  numbers<N, B, T> sum( numbers<N,B,T> A );
  numbers<N, B, T> sub( numbers<N,B,T> A );
  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,B,T>& A ) const;
  bool operator>( const numbers<N,B,T>& A ) const;
  bool operator==( const numbers<N,B,T>& A ) const;
  bool operator!=( const numbers<N,B,T>& A ) const;
  bool less_than( numbers<N,B,T> A );
  bool equals( numbers<N,B,T> A );

  private:

  void to_base( int input, unsigned pos = 0);
  int char_to_int( char num );
  char int_to_char( unsigned num );
  inline std::vector<T> get_number(void) { return number_; }
  
};


//constructor
template <size_t N, size_t B, class T>
numbers<N, B, T>::numbers(const std::string& number):size_(0) {
  if ( B < 2 ) {
    //trow exception, base cant be lower than 2
  }

  to_base( std::stoi(number) );

  /*
  for (int inx = 0; inx < size_ ; ++inx) {
    std::cout << number_[inx];
  }
  */

  fflush(stdout);
}

//int_to_char
template <size_t N, size_t B, class T>
char numbers<N, B, T>::int_to_char(unsigned num) {
  if ( num >= 0 ) {
    if ( num < 10 ) {
      return ( num + '0' );
    } if ( num > 9 && num < 37 ) {
      return ( (num - 10) + 'A' );
    }
  }
  //Throw exeption instead of returning '\n 
  return '\0';
}

//char_to_int
template <size_t N, size_t B, class T>
int numbers<N, B, T>::char_to_int( char num ) {
  if ( num >= '0' && num <= '9' ) {
    return ( num - '0' );
  } else if ( num >= 'A' && num <= 'Z' ) {
    return ( num - 'A' + 10 );
  }
  //Throw exeption instead of returning -1
  return -1;
}

//to_base
template <size_t N, size_t B, class T>
void numbers<N, B, T>::to_base(int input, unsigned pos ) {
  if ( input < B ) {
    //std::cout << "insertando: " << int_to_char(input) << std::endl;
    number_[pos] = int_to_char(input);
    ++size_;
  }
  else {
    //std::cout << "insertando: " << int_to_char(input % B) << std::endl;
    number_[pos]  = int_to_char(input % B);
    ++size_;
    input = input / B;
    to_base( input, ++pos );
  }
  
}

//sum
template <size_t N, size_t B, class T>
numbers<N, B, T> numbers<N, B, T>::sum( numbers A ) {
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

    if ( inx < A.size_ && inx < size_ ) {
      aux = char_to_int( A.number_[inx] ) + char_to_int( number_[inx] );
    } else if ( inx < size_ ) {
      aux = char_to_int( number_[inx] );
    } else {
      aux = char_to_int( A.number_[inx] );
    }

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
      //trow exceptio out of size 
      std::cout << "error" << std::endl;
    } else {
      //std::cout << inx << std::endl;
      C.number_[inx] = int_to_char(1) ;
      ++C.size_;
    }

  }
  return C;
}

//write
template <size_t N, size_t B, class T>
std::ostream& numbers<N, B, T>::write( std::ostream& os ) const {
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

//sub
template <size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::sub( numbers A ) {
  numbers<N,B,T> C;
  size_t result_size = size_ < A.size_ ? A.size_ : size_;
  bool carry = false;

  //Si A > B trow;
  C.size_ =  result_size;

  for ( int inx = 0; inx < result_size; ++inx ) {
    if ( number_[inx] < A.number_[inx] ) {
      C.number_[inx] = ( B - ( char_to_int( A.number_[inx]) - char_to_int(number_[inx]) ) );
      if ( carry ) {
        --C.number_[inx];
      if ( char_to_int(C.number_[inx]) == 0 ) --C.size_;
      }
      carry = true;
    } else {
      C.number_[inx] = ( int_to_char(char_to_int( number_[inx] ) - char_to_int( A.number_[inx] ) ));
      if ( char_to_int(C.number_[inx]) == 0 ) --C.size_;
    }
  }

  //return result;
  return C;
}

template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::less_than(numbers A) {
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
bool numbers<N,B,T>::equals(numbers A) {
  if ( size_ == A.size_ ) {
    for ( int inx = 0; inx < size_; ++inx )
      if ( number_[inx] != A.number_[inx] ) return false;
    return true;
  }
  return false;
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator<( const numbers& A ) const {
  return less( A );
}


template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator>( const numbers& A ) const {
  if ( !equals(A) ) return !less( A );
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
