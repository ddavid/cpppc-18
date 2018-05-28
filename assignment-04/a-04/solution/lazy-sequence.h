#ifndef CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED
#define CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED

#include <functional>
#include <iostream>

namespace cpppc
{

template <class T>
class lazy_sequence {

public:

    using self_t          = lazy_sequence<T>;
    using index_t         = int;
    using value_t         = T;
    using reference       = T &;
    using const_reference = const reference;

  class iterator
  {

  public:
    
    using seq_t           = cpppc::lazy_sequence<T>; 
    using self_t          = seq_t::iterator;
    using value_t         = seq_t::value_t;
    using reference       = seq_t::reference;
    using const_reference = seq_t::const_reference;
    using index_t         = seq_t::index_t;
    
    iterator()                               = default;
    ~iterator()                              = default;
    iterator(const self_t & other)           = default;
    self_t & operator=(const self_t & other) = default;

    iterator(const seq_t & container, index_t pos)
    : _container(&container)
    , _pos(pos)
    {}

    bool operator==(const self_t & rhs) const
    {
      return     (this       == &rhs) 
             || ((_container == rhs._container)
             &&  (_pos       == rhs._pos));
    }

    bool operator!=(const self_t & rhs) const
    { 
      return not (*this == rhs);
    }

    value_t operator*()
    {
      return _container->operator[](_pos);
    }

    const value_t operator*() const
    {
      return _container->operator[](_pos);
    }

    self_t & operator++()
    {
      ++_pos;
      return *this;
    }

    self_t operator++(int)
    {
      self_t tmp(*this);
      ++_pos;
      return tmp;
    }

  private:
    const seq_t * _container;
    index_t       _pos;
  };

public:

  using iterator  = self_t::iterator;

  lazy_sequence(int size, std::function<T(int)> generator)
  : _size(size), _gen_fun(generator)
  { }
  value_t operator[](int index) const { return _gen_fun(index); }
  iterator begin() { return iterator(*this, 0); }
  const iterator end()   { return iterator(*this, this->size()); }

  index_t size()
  {
    return _size;
  }
  
private:
  
  index_t                   _size     = 0;
  std::function<T(int)>     _gen_fun;
};

} // cpppc

#endif // CPPPC__S04__LAZY_SEQUENCE_H__INCLUDED