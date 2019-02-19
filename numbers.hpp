#pragma once

#define DEBG

#include <vector>
#include <iostream>

template <size_t N, size_t B, class T = char>
class numbers{

  private:
  std::vector<T> number_;
  unsigned short size_;
  
  public:
  numbers(void): number_(N), size_(0) {};
  explicit numbers( const std::string& number );
  ~numbers(void) {}

  numbers<N, B, T> sum( numbers<N,B,T> A );
  numbers<N, B, T> sub( numbers<N,B,T> A );
  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,B,T>& A ) const;
  bool operator>( const numbers<N,B,T>& A ) const;
  bool operator==( const numbers<N,B,T>& A ) const;

  private:

  void to_base( int input, unsigned pos = 0);
  int char_to_int( char num );
  char int_to_char( unsigned num );
  inline std::vector<T> get_number(void) { return number_; }
  bool less_than( const numbers<N,B,T>& A );
  bool equals( const numbers<N,B,T>& A );
  
};


//constructor
template <size_t N, size_t B, class T>
numbers<N, B, T>::numbers(const std::string& number): number_(N), size_(0) {
  if ( B < 2 ) {
    //trow exception, base cant be lower than 2
  }

  to_base( std::stoi(number) );
  for (auto digit : number_) {
    std::cout << digit;
  }

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
    number_.push_back( int_to_char(input) );
    ++size_;
  }
  else {
    //std::cout << "insertando: " << int_to_char(input % B) << std::endl;
    number_.push_back( int_to_char(input % B) );
    ++size_;
    input = input / B;
    to_base( input, ++pos );
  }
  
}

//sum
template <size_t N, size_t B, class T>
numbers<N, B, T> numbers<N, B, T>::sum( numbers A ) {
  std::vector<T> A_number = A.get_number();
  numbers<N, B, T> C;
  size_t result_size = number_.size() < A_number.size() ? A_number.size() : number_.size();
  unsigned aux;
  bool carry = false;

  /*
  if ( B != A.B ) {
    //Throw exeption, base not equal.
  }
  */

  for ( int inx = 0; inx < result_size; ++inx ) {
    if ( inx < A_number.size() && inx < number_.size() ) {
      aux = char_to_int( A_number[inx] ) + char_to_int( number_[inx] );
    } else if ( inx < number_.size() ) {
      aux = char_to_int( number_[inx] );
    } else {
      aux = char_to_int( A_number[inx] );
    }


    if ( carry ) {
      ++aux;
      carry = false;
    }
    if ( aux < B ) {
      C.number_.push_back( int_to_char(aux) );
    } else {
      C.number_.push_back( int_to_char( aux - B ) );
      carry = true;
    }
  }
  if ( carry ) {
    C.number_.push_back( int_to_char(1) );
  }
  return C;
}

//write
template <size_t N, size_t B, class T>
std::ostream& numbers<N, B, T>::write( std::ostream& os ) const {
  for (char digit: number_ ){
    os << digit;
  }

  fflush(stdout);
  return os;
}

//sub
template <size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::sub( numbers A ) {
  numbers<N,B,T> C;
  std::vector<T> A_number = A.get_number();
  size_t result_size = number_.size() < A_number.size() ? A_number.size() : number_.size();
  std::vector<T> result;
  bool carry = false;

  //Si A > B trow;

  for ( int inx = 0; inx < result_size; ++inx ) {
    if ( number_[inx] < A_number[inx] ) {
      C.number_.push_back( B - ( char_to_int( A_number[inx]) - char_to_int(number_[inx]) ) );
      if ( carry ) {
        --C.number_[inx];
      }
      carry = true;
    } else {
      C.number_.push_back( int_to_char(char_to_int( number_[inx] ) - char_to_int( A_number[inx] ) ));
    }
  }

  //return result;
  return C;
}

template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::less_than(const numbers& A) {
  if ( size_ < A.size_ ) return true;
  if ( size_ == A.size_ ) {
    for( int inx = (size_ - 1); inx >= 0; --inx) {
      if ( number_[inx] < A.number_[inx] ) return true;
    }
  }
  return false;
}


template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::equals(const numbers& A) {
  if ( size_ == A.size_ ) return true;
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
