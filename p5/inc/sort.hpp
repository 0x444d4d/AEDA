
#ifndef SORT_BASE
#define SORT_BASE

#include <cstdlib>
#include <iostream>

namespace aeda {

template < class T >
class sort_base {

    protected:
    uint8_t size_;

    public:
    //sort_base(void) : size_(0) {}
    sort_base( uint8_t size  = 0 ) : size_(size) {}
    //virtual void resize( uint8_t size ) = 0;
    virtual void sort( void ) = 0;
};

}

#endif
