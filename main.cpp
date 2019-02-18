#include "./numbers.hpp"

int main() {

  std::string input;
  std::cin >> input;
  std::cin.ignore();

  //numbers<10, 16, char> C;
  numbers<10, 16, char> test( input );
  std::cout << std::endl;

  std::cin >> input;
  std::cin.ignore();

  numbers<10, 16, char> test2( input );
  std::cout << std::endl;

  test.sum(test2).write(std::cout);
  
  std::cout << std::endl;
  std::cout << "resta: ";

  test.sub(test2).write(std::cout);
 

}
