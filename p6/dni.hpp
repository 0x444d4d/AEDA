#pragma once
//#include <random.h>
#include <iostream>
#include <time.h>
#include "contador.hpp"


namespace aeda {

template < unsigned id = 0 >
class DNI {

    private:
        char id_ [10];
        Contador<id> cont;

    public:
        DNI();

        //operator unsigned long(void);
        bool operator<(DNI right);
        bool operator>(DNI right);
        bool operator==(DNI right);

        friend std::ostream& operator<<(std::ostream& os, const DNI<id>& data) {
            for ( char digit : data.id_ ) {
                std::cout << digit;
            }
            return os;
        }

    private:
        bool menor_que( DNI right );
};


template < unsigned id >
DNI<id>::DNI() { 

    for (int inx = 0; inx < 9; ++inx) {
        id_[inx] = (rand() % 10) + 48;
    }  
    id_[9] = '\0';
}

/*
template < unsigned id >
DNI<id>::operator unsigned long(void) {
    return atol(id_);
}
*/

template < unsigned id >
bool DNI<id>::operator==(DNI right) {

#ifdef DEM
    std::cout << (*this) << " = = " << right << std::endl;
#endif

    cont++;
    for ( int i = 0; i < 9; ++i ) {
        if ( id_[i] != right.id_[i])
            return false;
    }
    return true;
}

template < unsigned id >
bool DNI<id>::menor_que( DNI right ) {
    for (short inx = 0; inx < 9; ++inx) {
        if ( id_[inx] < right.id_[inx] ) return true;
        else if ( id_[inx] > right.id_[inx] ) return false;
    }
    return false;
}

template < unsigned id >
bool DNI<id>::operator<( DNI right ) {

    #ifdef DEM
    std::cout << (*this) << " < " << right << std::endl;
    #endif

    cont++;
    return menor_que(right);
}

template < unsigned id >
bool DNI<id>::operator>( DNI right ) {

    #ifdef DEM
    std::cout << (*this) << " > " << right << std::endl;
    #endif

    cont++;
    if ( menor_que( right )) return false;
    else if ( (*this) == right  ) return true;
    else return true;
}

/*
template < unsigned id >
std::ostream& operator<<(std::ostream& os, const DNI<id>& data) {
    for ( char digit : data.id_ ) {
        std::cout << digit;
    }
    return os;
}
*/

}
