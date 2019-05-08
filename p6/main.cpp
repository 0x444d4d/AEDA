#include <iostream>
#include "bbtree.hpp"
#include "dni.hpp"
#include "contador.hpp"
//#define DEFAULT

int main(void) {


#ifdef DEM
    aeda::bbtree<int> tree;
    unsigned short option = 1;
    int value;    
    //aeda::DNI<> dni;

    while ( option ) {

        std::cout << "[0] Salir\n";
        std::cout << "[1] Insertar\n";
        std::cout << "[2] Buscar\n";
        std::cout << "[3] Borrar\n";
        std::cout << "[4] Imprimir\n";

        std::cin >> option;
        std::cin.ignore();
        if ( !option ) exit(0);
        
        if ( option != 4 ) {
            std::cin >> value;
            std::cin.ignore();
        }

        switch( option ) {


            case 1:
                if ( tree.insert(value) ) std::cout << "Valor insertado\n";
                else std::cout << "Valor no insertado, ya se encuentra en el arbol\n";
                break;

            case 2:
                //if ( tree.search(value) ) std::cout << "Valor encontrado\n";
                //else std::cout << "Valor no encontrado\n";
                std::cout << "no implementado\n";
                break;
                
            case 3:
                if ( tree.remove(value) ) std::cout << "Valor eliminado\n";
                else std::cout << "Valor no encontrado\n";
                break;

            case 4:
                tree.printTree();
                break;

            default:
                std::cout << "Opcion no valida\n";
           
        }
    }


#endif

#ifndef DEM

    aeda::bbtree<aeda::DNI<>> tree;

    unsigned minimo = -1, media = 0, maximo = 0; 
    unsigned int nPruebas;
    std::vector<aeda::DNI<>> bPruebas;
    aeda::Contador<> counter;

    std::cout << "Numero de pruebas\n";
    std::cin >> nPruebas;
    std::cin.get();

    bPruebas.resize( nPruebas );


    for ( unsigned int i = 0; i < nPruebas; ++i) {
        bPruebas[i] = aeda::DNI<>();
        tree.insert( bPruebas[i] );
    }

    counter.start();

    std::cout << "Estadísticas de insersion\n";

    for ( unsigned int i = 0; i < nPruebas; ++i ) {
        tree.insert(aeda::DNI<>());

        if ( minimo > counter.get() ) minimo = counter.get();
        if ( maximo < counter.get() ) maximo = counter.get();

        media += counter.get();
        counter.reset();
    }

    std::cout << "minimo: " << minimo << "\n";
    std::cout << "media: " << media / nPruebas << "\n";
    std::cout << "maximo: " << maximo << "\n";

    minimo = -1;
    maximo = media = 0;

    std::cout << "Estadísticas de busqueda\n";

    for ( unsigned int i = 0; i < nPruebas; ++i ) {
        tree.search( bPruebas[i] );
        if ( minimo > counter.get() ) minimo = counter.get();
        if ( maximo < counter.get() ) maximo = counter.get();

        media += counter.get();
        counter.reset();

    }
    counter.stop();

    std::cout << "minimo: " << minimo << "\n";
    std::cout << "media: " << media / nPruebas << "\n";
    std::cout << "maximo: " << maximo << "\n";

#endif
    return 0;
}
