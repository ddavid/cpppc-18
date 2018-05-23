#include <vector>
#include <boost/iterator/transform_iterator.hpp>
#include <iostream>
#include <functional>
#include <typeinfo>


//#define BOOST_RESULT_OF_USE_DECLTYPE

int main(int argc, char * argv[])
{
  std::vector<int> nums(10, 5);

  typedef std::iterator<std::random_access_iterator_tag, int> RAi;
  typedef std::function<int(int)>  int_unary_functor;
  typedef boost::transform_iterator< int_unary_functor, RAi > lazy_iterator;
  
  int_unary_functor times_two = [](int i) -> int {return i * 2;};

  auto lazy_begin = boost::make_transform_iterator(nums.begin(), times_two);
  auto lazy_end   = boost::make_transform_iterator(nums.end(), times_two);

  std::cout << typeid(lazy_begin).name() << std::endl;

  //lazy_iterator lazy_begin(nums.begin(), [](int i){ return i * 2;});
  //lazy_iterator lazy_end(nums.end(), [](int i){ return i * 2;});

  while( lazy_begin != lazy_end )
  {
    std::cout << *lazy_begin++ << " ";
  }
  std::cout << std::endl;

  return 0;
}
