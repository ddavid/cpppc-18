#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

int main(int argc, char * argv[])
{
  std::vector<int> v1(10, 40);
  std::vector<int> v2(v1);

  v2[5] = 0;

  bool result = std::lexicographical_compare(
    v2.cbegin(),
    v2.cend(), 
    v1.cbegin(),
    v1.cend(),
    [](const int fst, const int snd) -> bool 
    { 
      return fst <= snd; 
    });

  std::cout << result << std::endl;
    
  return 0;
}
