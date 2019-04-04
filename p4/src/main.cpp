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
    unsigned  media = 0,maximo = 0, minimo = std::numeric_limits<int>::max();
    float factor;
    Tabla<DNI> hash_table( uint16_t(100), uint16_t(100), modulo, lineal ); 


    std::cout << "Tamaño de la tabla: " << std::endl;
    std::cin >> nDNI;
    std::cin.get();
    std::cout << "Tamaño de las celdas: " << std::endl;
    std::cin >> cellsize;
    std::cin.get();
    std::cout << "Factor de carga: " << std::endl;
    std::cin >> factor;
    std::cin.get();

    hash_table.resize(nDNI, cellsize);
    
    load = factor * nDNI * cellsize;
    for (int i = 0; i < 2*load; ++i) {
        vDNI.push_back ( DNI () );
    }


    for (int i = 0; i < load; ++i) {
        hash_table.Insertar ( vDNI[i]  );

    }

    maincount.start ();

    for (int i = 0; i < load; ++i) {
        static unsigned aux;
        hash_table.Buscar( vDNI[i] );

        aux = maincount.get();
        if (aux < minimo) minimo = aux;
        if (aux > maximo) maximo = aux;
        media += aux;
        maincount.reset();
    }

    std::cout << "----Busqueda----" << std::endl;
    std::cout << "Celdas\tTamaño de celda\tCarga\t" <<  std::endl;
    std::cout << nDNI <<  "\t\t" << cellsize << "\t" << load << std::endl;
    std::cout << "Minimo\tMaximo\tMedia" << std::endl;
    std::cout << minimo << "\t" << maximo << "\t" << media/load << std::endl;
    std::cout << std::endl;


    minimo = std::numeric_limits<int>::max();
    maximo = media  = 0;
    

    for (int i = load; i < 2*load; ++i) {
        static unsigned aux;
        hash_table.Buscar ( vDNI[i]  );
        aux = maincount.get();
        if (aux < minimo) minimo = aux;
        if (aux > maximo) maximo = aux;
        media += aux;
        
    }

    maincount.stop ();

    std::cout << "----Insercion----" << std::endl;
    std::cout << "Celdas\tTamaño de celda\tCarga\t" <<  std::endl;
    std::cout << nDNI <<  "\t\t" << cellsize << "\t" << load << std::endl;
    std::cout << "Minimo\tMaximo\tMedia" << std::endl;
    std::cout << minimo << "\t" << maximo << "\t" << media/load << std::endl;
    std::cout << std::endl;
}


