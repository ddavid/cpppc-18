//#include <vector>
//#include <functional>
#include "lazy-sequence.h"
#include <iostream>

using namespace cpppc;

int main(int argc, char * argv[])
{
  std::function<int(int)> example = [](int count){return count;};
  std::cout << example(20) << std::endl;
  lazy_sequence<int> lazy(10, example);

  std::cout << lazy[5] << std::endl;

  std::cout << lazy.size() << std::endl;

  lazy_sequence<int> seq(10, [](int i) {return (100 + i * i);});
  std::cout << "sequence size: " << seq.size() << '\n';
  
  auto it = seq.begin();
  // still nothing computed

  int first = *it; // <-- returns value from generator(it._pos)

  for (auto e : seq) {
    // generates values one by one:
    std::cout << e << " ";
  }
  std::cout << std::endl;
  // prints:
  // 100 101 104 109 116 125 136 149 164 181
  
  return 0;
}
