#ifndef CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED
#define CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED

#include <vector>
#include <functional>

template<typename ValueT>
class lazy_sequence
{
public:
  using value_t   = ValueT;
  using self_t    = lazy_sequence<value_t>;
  using iterator  = typename std::vector<std::function<value_t(value_t)>>::iterator;
  using size_type = std::size_t;

  lazy_sequence() = delete;

  lazy_sequence(int count, std::function<value_t(value_t)> fun)
  : _generator(count, fun)
  {}

  value_t operator[](size_type pos) { return _generator[pos](pos);}

  iterator begin() { return _generator.begin();}

  const iterator end() const { return _generator.end();}

  size_type size() { return _generator.size();} 

private:
  std::vector<std::function<value_t(value_t)>> _generator;

};

#endif // CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED