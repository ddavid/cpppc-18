#ifndef FORWARD__ITERATOR__ITERATOR_BASE_H__INCLUDED
#define FORWARD__ITERATOR__ITERATOR_BASE_H__INCLUDED

#include <iterator>


namespace cpppc {

template <
  class IteratorType,
  class ValueType    = typename IteratorType::value_type,
  class IndexType    = std::ptrdiff_t,
  class Pointer      = ValueType *,
  class Reference    = ValueType & >

class ForwardIteratorBase
{

  typedef ForwardIteratorBase<
            IteratorType,
            ValueType,
            IndexType,
            Pointer,
            Reference >          self_t;
  
  typedef IteratorType           derived_t;

 private:
  derived_t & derived() {
    return static_cast<IteratorType &>(*this);
  }
  constexpr const derived_t & derived() const {
    return static_cast<const derived_t &>(*this);
  }

 public:
  typedef std::forward_iterator_tag             iterator_category;

  typedef ValueType                                    value_type;
  typedef IndexType                               difference_type;
  typedef Pointer                                         pointer;
  typedef const Pointer                             const_pointer;
  typedef Reference                                     reference;
  typedef const Reference                         const_reference;

 public:
  
  ForwardIteratorBase()                = default;
  ForwardIteratorBase(self_t &&)       = default;
  ForwardIteratorBase(const self_t &)  = default;
  ~ForwardIteratorBase()               = default;
  self_t & operator=(self_t &&)        = default;
  self_t & operator=(const self_t &)   = default;

  reference operator*() {
    return derived().dereference();
  }

  const reference operator*() const {
    return derived().dereference();
  }

  const reference operator->() const {
    return derived().dereference();
  }

  derived_t & operator++() {
    derived().advance(1);
    return derived();
  }

  derived_t operator++(int) {
    derived_t old = derived();
    derived().advance(1);
    return old;
  }

  void advance(const difference_type steps)
  {
    int i = 0;
    while( i != steps )
    {
      derived().increment();
      ++i;
    }
  }
};

} // namespace cpppc

#endif // FORWARD__ITERATOR__ITERATOR_BASE_H__INCLUDED