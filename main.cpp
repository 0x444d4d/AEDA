#include "./numbers.hpp"

int main() {

  std::string input;
  std::cin >> input;
  std::cin.ignore();

  numbers<2, 10, char> test( input );
  std::cout << std::endl;

  std::cin >> input;
  std::cin.ignore();

  numbers<2, 10, char> test2( input );
  std::cout << std::endl;

  std::vector<char> result = test.sum(test2);
  for (char digit : result)
    std::cout << digit;
  fflush(stdout);

}
