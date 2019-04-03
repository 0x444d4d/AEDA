#include "../include/dni-t.hpp"
#include "../include/fdisp.hpp"
#include "../include/table-t.hpp"
#include "../include/clave-t.hpp"
#include <vector>
#include <limits>

using namespace aeda;


void print_test(void);


int main(void) {
    srand(time(NULL));
    std::vector<DNI> vDNI;
    Contador maincount;
    int cellsize, nDNI, load;
    int media = 0,maximo = 0, minimo = std::numeric_limits<int>::max();
    float factor;
    Tabla<DNI> hash_table( uint16_t(100), uint16_t(100) ); 


    std::cout << "Tamaño de la tabla: " << std::endl;
    std::cin >> nDNI;
    std::cin.get();
    std::cout << "Tamaño de las celdas: " << std::endl;
    std::cin >> cellsize;
    std::cin.get();
    std::cout << "Factor de carga: " << std::endl;
    std::cin >> factor;
    std::cin.get();

    
    load = factor * nDNI * cellsize;
    for (int i = 0; i < 2*load; ++i) {
        vDNI.push_back ( DNI () );
    }


    for (int i = 0; i < load; ++i) {
        hash_table.Insertar ( vDNI[i]  );

    }

    maincount.start ();

    for (int i = 0; i < load; ++i) {
        static int aux;
        hash_table.Buscar( vDNI[i] );

        aux = maincount.get();
        if (aux < minimo) minimo = aux;
        if (aux > maximo) maximo = aux;
        media += aux;
        maincount.reset();
    }

    std::cout << "----Busqueda----" << std::endl;
    std::cout << "Minimo: " << minimo << std::endl;
    std::cout << "Maximo: " << maximo << std::endl;
    std::cout << "Media: " << media/load << std::endl;


    minimo = std::numeric_limits<int>::max();
    maximo = media  = 0;
    

    for (int i = load; i < 2*load; ++i) {
        static int aux;
        //std::cout << hash_table.Buscar ( vDNI[i]  ) << std::endl;
        hash_table.Buscar ( vDNI[i]  );
        aux = maincount.get();
        if (aux < minimo) minimo = aux;
        if (aux > maximo) maximo = aux;
        media += aux;
        
    }

    maincount.stop ();

    std::cout << "----Insersion----" << std::endl;
    std::cout << "Minimo: " << minimo << std::endl;
    std::cout << "Maximo: " << maximo << std::endl;
    std::cout << "Media: " << media/load << std::endl;

    std::cout << "Numero de pruebas: " << std::endl;
    std::cout << maincount.get() << std::endl;
    //aeda::FDispersionBase<aeda::DNI>* dispersion = new aeda::FDispersionPAleatoria<aeda::DNI>(100);
}


