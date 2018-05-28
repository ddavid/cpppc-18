#include <iostream>
#include <vector>
#include <array>

int main()
{
  std::array<int, 10> a1 {};
  std::array<int, 10> a2 {};
  std::cout << (a1 == a2) << std::endl;
  
  std::array<int, 10> a3;
  std::array<int, 10> a4;

  std::cout << (a3 == a4) << std::endl;

  return 0;
}
