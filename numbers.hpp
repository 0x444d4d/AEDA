#pragma once

#include <vector>
#include <iostream>

template <size_t N, size_t B, class T = char>
class numbers{

  private:
  std::vector<T> number_;
  
  public:
  numbers(void);
  numbers( std::string number );

  std::vector<T> sum( numbers A );
  private:
  //bool fits( std::string input );
  std::vector<T> get_number(void);
  char int_to_char( unsigned num );
  int char_to_int( char num );
  void to_base( int input, unsigned pos = 0);
  
};

template < size_t N, size_t B, class T >
std::vector<T> numbers<N, B, T>::get_number(void) {
  return number_;
}

template <size_t N, size_t B, class T>
numbers<N, B, T>::numbers(std::string number) {
  if ( B < 2 ) {
    //trow exception, base cant be lower than 2
  }

  to_base( std::stoi(number) );
  for (auto digit : number_)
    std::cout << digit;

  fflush(stdout);
}

/*
template <size_t N, size_t B, class T>
bool numbers<N, B, T>::fits( std::string input ) {

  for (int aux : input) {
    if ( char_to_int(aux) > N) {
      return false;
    }
  }
     
  return true;
}
*/

template <size_t N, size_t B, class T>
char numbers<N, B, T>::int_to_char(unsigned num) {
  if ( num >= 0 ) {
    if ( num < 10 ) {
      return ( num + '0' );
    } if ( num > 9 && num < 37 ) {
      return ( (num - 10 ) + 'A' );
    }
  }
  //Throw exeption instead of returning '\n 
  return '\0';
}

template <size_t N, size_t B, class T>
int numbers<N, B, T>::char_to_int( char num ) {
  if ( num >= '0' && num <= '9' )
    return ( num - '0' );
  else if ( num >= 'A' && num <= 'Z' )
    return ( num - 'A' );
  //Throw exeption instead of returning -1
  return -1;
}

template <size_t N, size_t B, class T>
void numbers<N, B, T>::to_base(int input, unsigned pos ) {
  if ( input < B ) {
    std::cout << "insertando: " << int_to_char(input) << std::endl;
    number_.push_back( int_to_char(input) );
  }
  else {
    std::cout << "insertando: " << int_to_char(input % B) << std::endl;
    number_.push_back( int_to_char(input % B) );
    input = input / B;
    to_base( input, ++pos );
  }
  
}

template <size_t N, size_t B, class T>
std::vector<T> numbers<N, B, T>::sum( numbers A ) {
  std::vector<T> A_number = A.get_number();
  size_t result_size = number_.size() < A_number.size() ? A_number.size() : number_.size();
  std::vector<T> result;
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

    std::cout << "A+B = " << aux << std::endl;

    if ( carry ) {
      std::cout << "A+B+C = " << (aux + 1) << std::endl;
      ++aux;
      carry = false;
    }
    if ( aux < B ) {
      result.push_back( int_to_char(aux) );
    } else {
      result.push_back( int_to_char( aux - B ) );
      carry = true;
    }
  }
  if ( carry ) result.push_back( int_to_char(1) );
  return result;
}
