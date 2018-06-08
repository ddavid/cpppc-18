#ifndef CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED
#define CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED

#include <vector>
#include <functional>
#include <boost/iterator/transform_iterator.hpp>

template<typename ValueT>
class lazy_sequence
{
public:
  using value_t   = ValueT;
  using self_t    = lazy_sequence<value_t>;
  using iterator  = typename std::vector<std::function<value_t(value_t)>>::iterator;
  using size_type = std::size_t;

/*
  class lazy_iterator : public std::iterator<
      std::random_access_iterator_tag
    , value_t
    , ptrdiff_t
    , value_t *
    , value_t >
  {
    using lazy_seq_t = lazy_sequence<ValueT>;
    using self_t     = lazy_seq_t::lazy_iterator;
    using value_t    = ValueT;
  public:
    lazy_iterator()

  private:
    size_t _pos;
    value_t val; 
  };
*/

  lazy_sequence() = delete;

  lazy_sequence(int count)
  : _generator(count)
  , _functor([](value_t val)-> value_t {return val;})
  {}

  /*
  lazy_sequence(int count, std::function<value_t(value_t)>)
  : _generator(std::enumerate(0,count))
  */
  
  lazy_sequence(int count, value_t val, std::function<value_t(value_t)> fun)
  : _generator(count, val)
  , _functor(fun)
  {}

  value_t operator[](size_type pos) { return _functor(_generator[pos]);}

  auto begin() { return boost::make_transform_iterator(_generator.begin(), _functor);}

  auto end()  { return boost::make_transform_iterator(_generator.end(), _functor);}

  size_type size() { return _generator.size();} 

private:
  std::vector<value_t>              _generator;
  std::function<value_t(value_t)>   _functor;

};

#endif // CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED