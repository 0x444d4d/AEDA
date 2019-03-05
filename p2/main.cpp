#include "numbers.hpp"
#include "binary_numbers.hpp"

template<int N, int B, class T = char>
void test_number( std::string v1, std::string v2 );

int main(void) {
  try {

    std::string input1, input2;
    
    std::cout << "Valor del numero 1: ";
    std::cin >> input1;
    std::cin.ignore();


    std::cout << "Valor del numero 2: ";
    std::cin >> input2;
    std::cin.ignore();

    test_number<10,2,char>(input1,input2);
    test_number<10,10,char>(input1,input2);
    test_number<10,16,char>(input1,input2);

  }
  catch( char const* c ) {
    std::cout << c << std::endl;
  }
  catch( std::string c ) {
    std::cout << c << std::endl;
  }
}


template<int N, int B, class T>
void test_number( std::string input1, std::string input2) {
    numbers<N,B,T> v1(input1);
    numbers<N,B,T> v2(input2);
    std::cout << "Base: " << B << std::endl;

    std::cout << "suma" << std::endl;
    std::cout << v1 + v2 << std::endl;
    //std::cout << std::endl;

    std::cout << "resta" << std::endl;
    std::cout << v1 - v2 << std::endl;;
    numbers<N,B,T> v3 = (v1 - v2);
    std::cout << v3 << std::endl;

    std::cout << "numeros" << std::endl;
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << std::endl;


    if (v2 == v1 )
      std::cout << "Los numeros son iguales" << std::endl;
    else
      std::cout << "Los numeros son distintos" << std::endl;


    if (v1 < v2 )
      std::cout << "El numero 1 es menor" << std::endl;
    else
      std::cout << "El numero 1 no es menor" << std::endl;
    
}
