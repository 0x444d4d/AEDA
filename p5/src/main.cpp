#define DEM
//#include "../inc/select.hpp"
#include "../inc/shake.hpp"
#include "../inc/dni-t.hpp"


int main(void) {

  srand( time(NULL) );
  aeda::DNI a,b;
  std::vector<aeda::DNI> v1;
  for (int i = 0; i < 10; ++i )
    v1.push_back( aeda::DNI() );



  for ( auto i : v1 )
    std::cout << i << "\n";



  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "a:" << a << std::endl;
  std::cout << "b:" << b << std::endl;
  std::cout << (a < b);

  std::cout << std::endl;

  shake_sort<aeda::DNI>( v1, v1.size() );

}
