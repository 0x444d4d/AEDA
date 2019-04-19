#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "../inc/dni-t.hpp"
#include "../inc/sortMerge.hpp"


int main(void) {
    aeda::sort_base<aeda::DNI>* vector;

    vector = new aeda::sort_merge<aeda::DNI> (5);

    vector->sort ();
}
