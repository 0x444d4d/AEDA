//#define DEM

#include "../inc/dni-t.hpp"
#include "../inc/select.hpp"
#include "../inc/heap.hpp"
#include "../inc/shell.hpp"
#include "../inc/shake.hpp"
#include "../inc/merge.hpp"
#include "../inc/contador.hpp"

using namespace aeda;

enum sortMethod { Select, Cocktail, Merge, Heap, Shell };

int main( int argc, char* argv[] ) {

    unsigned short sel = atoi( argv[3] );
    unsigned int size = atoi(argv[1]);
    unsigned int iter = atoi(argv[2]);
    aeda::Contador<> contador;
    contador.start();
    std::vector<aeda::DNI<> > v1;
    unsigned minimo = -1, media = 0, maximo = 0;
    sortMethod opt;


    srand( time(nullptr) );


    #ifdef DEM
    iter = 1;
    #endif


    switch( sel ) {
        case 0:
            std::cout << "Select\n";
            break;
        case 1:
            std::cout << "Cocktail\n";
            break;
        case 2:
            std::cout << "Merge\n";
            break;
        case 3:
            std::cout << "Heap\n";
            break;
        case 4:
            std::cout << "Shell\n";
            break;
    }

    for (unsigned int i = 0; i < iter; ++i) {
        for ( unsigned int i = 0; i < size; ++i ) {
            v1.push_back( DNI<>() );
        }

        switch ( sel ) {
            case Select:
                select_sort<aeda::DNI<>>( v1, v1.size() );
                break;
            case Cocktail:
                shake_sort<aeda::DNI<>>( v1, v1.size() );
                break;
            case Merge:
                merge_sort<aeda::DNI<>>( v1, v1.size() );
                break;
            case Heap:
                heap_sort<aeda::DNI<>>( v1, v1.size() );
                break;
            case Shell:
                if ( argc == 5 ) shell_sort<aeda::DNI<>>( v1, v1.size(), atof(argv[4]) );
                else shell_sort<aeda::DNI<>>( v1, v1.size() );
                break;
        }

        minimo = contador.get() > minimo ? minimo : contador.get();
        maximo = contador.get() < maximo ? maximo : contador.get();
        media += contador.get();

        v1.clear();
        contador.reset();

    }
    media /= iter;
    std::cout << "\t\t\t\tminimo\t\tmedia\t\tmaximo\n";
    std::cout << "Comparaciones:  " << minimo << "\t\t" << media << "\t\t" << maximo << std::endl;

}
