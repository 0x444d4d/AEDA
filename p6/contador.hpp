#ifndef COUNT
#define COUNT

namespace aeda {

//template se usa para crear distintas clases de forma que
//puedan existir varios contadores que no compartan los atributos
//count_ y iter_.

template < unsigned id = 0 >
class Contador {

    private:
    unsigned short id_;
    static bool count_;
    static int iter_;

    public:
    Contador (void) : id_(id) {}
    unsigned short getId (void) { return id_; }
    void start (void) { count_ = true; }
    void stop (void) { count_ = false; }
    void reset (void) { iter_ = 0; }
    void operator++ (int) { if ( count_ ) ++iter_; }
    int get ( void ) { return iter_; }

};



//declaracion de contador;
template < unsigned id >
bool Contador<id>::count_ = 0;
template < unsigned id >
int Contador<id>::iter_ = 0;


}

#endif
