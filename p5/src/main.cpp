//#define DEM

#include "../inc/dni-t.hpp"
#include "../inc/select.hpp"
#include "../inc/heap.hpp"
#include "../inc/shell.hpp"
#include "../inc/shake.hpp"
#include "../inc/merge.hpp"
#include "../inc/contador.hpp"

using namespace aeda;

int main( int argc, char* argv[] ) {
    srand( time(nullptr) );

    unsigned int size = atoi(argv[1]);

    aeda::Contador<0> contadorSelect;
    aeda::Contador<1> contadorCocktail;
    aeda::Contador<2> contadorMerge;
    aeda::Contador<3> contadorHeap;
    aeda::Contador<4> contadorShell;

    contadorSelect.start();
    contadorCocktail.start();
    contadorMerge.start();
    contadorHeap.start();
    contadorShell.start();

    std::vector<aeda::DNI<0>> v1;
    std::vector<aeda::DNI<1>> v2;
    std::vector<aeda::DNI<2>> v3;
    std::vector<aeda::DNI<3>> v4;
    std::vector<aeda::DNI<4>> v5;

    for ( unsigned int i = 0; i < size; ++i ) {
        v1.push_back( DNI<0>() );
        v2.push_back( DNI<1>() );
        v3.push_back( DNI<2>() );
        v4.push_back( DNI<3>() );
        v5.push_back( DNI<4>() );
    }

    for (unsigned int i = 0; i < 10; ++i) {
        select_sort<aeda::DNI<0>>( v1, v1.size() );
        shake_sort<aeda::DNI<1>>( v2, v2.size() );
        merge_sort<aeda::DNI<2>>( v3, v3.size() );
        heap_sort<aeda::DNI<3>>( v4, v4.size() );
        shell_sort<aeda::DNI<4>>( v5, v5.size() );
    }


    std::cout << "Comparaciones Select Sort:  "  << contadorSelect.get() << std::endl;
    std::cout << "Comparaciones Cocktail Sort:  "  << contadorCocktail.get() << std::endl;
    std::cout << "Comparaciones Merge Sort:  "  << contadorMerge.get() << std::endl;
    std::cout << "Comparaciones Heap Sort:  "  << contadorHeap.get() << std::endl;
    std::cout << "Comparaciones Shell Sort:  "  << contadorShell.get() << std::endl;

    contadorSelect.start();
    contadorCocktail.start();
    contadorMerge.start();
    contadorHeap.start();
    contadorShell.start();

}
