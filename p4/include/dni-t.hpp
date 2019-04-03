#pragma once
//#include <random.h>
#include <iostream>
#include <time.h>
#include "contador.hpp"

namespace aeda {

class DNI {
        
    private:
    char id_ [10];
    Contador cont;
        
    public:
    DNI();

    operator unsigned long(void);
    bool operator<(DNI right);
    bool operator==(DNI right);
    friend std::ostream& operator << (std::ostream& os, const DNI& data);

    private:
    bool menor_que( DNI right );
};


DNI::DNI() { 
    #ifndef RAND
    //srand(time(NULL));
    #define RAND
    #endif

    for (int inx = 0; inx < 9; ++inx) {
        id_[inx] = (rand() % 10) + 48;
    }  
    id_[9] = '\0';
}

DNI::operator unsigned long(void) {
    return atol(id_);
}

bool DNI::operator==(DNI right) {
    cont++;
    for ( int i = 0; i < 9; ++i ) {
        if ( id_[i] != right.id_[i])
            return false;
    }
    return true;
}

bool DNI::menor_que( DNI right ) {
    for (short inx = 0; inx < 9; ++inx) {
        if ( id_[inx] < right.id_[inx] ) return true;
        else if ( id_[inx] > right.id_[inx] ) return false;
    }
    return false;
}

bool DNI::operator<( DNI right ) {

    cont++;
    return menor_que(right);
}


std::ostream& operator<<(std::ostream& os, const DNI& data) {
   for ( char digit : data.id_ ) {
       std::cout << digit;
   }
   return os;
}

}
