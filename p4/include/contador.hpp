#pragma once

namespace aeda {

class Contador{

    private:
    static bool count_;
    static int iter_;

    public:
    Contador(void) {}
    void start(void) { count_ = true; }
    void stop(void) { count_ = false; }
    void reset(void) { iter_ = 0; }
    void operator++(int) { if ( count_ ) ++iter_; }
    int get( void ) { return iter_; }
};


#ifndef COUNT
#define COUNT
//declare contador;
bool Contador::count_ = 0;
int Contador::iter_ = 0;
#endif
}
