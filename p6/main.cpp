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

    aeda::Contador<0> counter;
    counter.start();

    counter.stop();
    //tree.insert(10);
    //tree.insert(3);
    //tree.insert(33);
    //tree.insert(2);
    //tree.insert(20);
    //tree.insert(4);
    //tree.insert(31);
    //tree.insert(34);

    //tree.remove(33);

    //tree.printTree();
#endif
    return 0;
}
