#include <array>
#include <iostream>

int main(int argc, char * argv[])
{
  std::array<int, 540> arr1 {};
  std::array<int, 540> arr2 {};

  arr1.front() = 111;
  arr1.back()  = 999;

  std::cout << arr1.front() << "\n"
  << arr1.back() << std::endl;
}
