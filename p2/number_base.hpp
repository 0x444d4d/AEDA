#pragma once

#include <stdint.h>
#include <iostream>
#include "number_exeptions.hpp"

class number_base {

  private:
  uint8_t base;
  int size;

  public:
  number_base( void );
  virtual number_base* operator+( const number_base* A) const = 0;
  virtual number_base* operator-( const number_base* A) const = 0;
  virtual std::ostream& write( std::ostream& os ) const = 0;

  protected:
  virtual void to_base( int input, unsigned pos = 0 ) = 0;
  virtual number_base* duplicate() const = 0;

};

number_base::number_base( void ) {
  //if ( base < 1 ) throw wrong_number_exception();
  //if ( size < 1 ) throw wrong_number_exception();
}

std::ostream& operator<<(std::ostream& os, number_base* A) {
  return A->write(os);
}
