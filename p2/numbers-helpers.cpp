#include <iostream>

#include "numbers-helpers.hpp"

bool check_char_range( const char character ) {
  if ( character >= '0' && character <= '9' ) {
    return true;
  } else if(character >= 'A' && character <= 'Z') {
    return true;
  } else {
    return false;
  }
}

bool check_string( const std::string input ) {
  //retornar true si la cadena solo contiene caracteres validos.
  unsigned short inx = 0;

  if ( input[0] == '+' || input[0] == '-') inx = 1;
  for ( inx; inx < input.size(); ++inx ) {
    if ( check_char_range( input[inx] ) == false ) {
      return false;
    }
  }   
  return true;
}

int char_to_int( const char num ) {
  if ( num >= '0' && num <= '9' ) {
    return ( num - '0' );
  } else if ( num >= 'A' && num <= 'Z' ) {
    return ( num - 'A' + 10 );
  }
  throw std::string("invalid argument in function: char_to_int( const char ): int(char) = " + std::to_string( int( num )));
}


char int_to_char( const int num ) {
  if ( num >= 0 ) {
    if ( num < 10 ) {
      return ( num + '0' );
    } if ( num > 9 && num < 37 ) {
      return ( (num - 10) + 'A' );
    }
  }
  throw std::string("invalid argument in function: int_to_char( const int ): int = " + std::to_string(num) );
}
