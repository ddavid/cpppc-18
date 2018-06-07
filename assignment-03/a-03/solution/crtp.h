#ifndef LIST__ITERATOR__ITERATOR_BASE_H__INCLUDED
#define LIST__ITERATOR__ITERATOR_BASE_H__INCLUDED

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

  struct list_node
  {
    list_node(const ValueType & val)
    : value(val)
    , next(0)
    {}

    ValueType              value;
    list_node             * next;
  };

  typedef ForwardIteratorBase<
            IteratorType,
            ValueType,
            IndexType,
            Pointer,
            Reference >          self_t;


  
  typedef IteratorType           derived_t;
 private:
  list_node * _node;

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
  
  ForwardIteratorBase()
  : _node(0)
  {}
  ForwardIteratorBase(self_t &&)       = default;
  ForwardIteratorBase(const self_t &)  = default;
  ~ForwardIteratorBase()               = default;
  self_t & operator=(self_t &&)        = default;
  self_t & operator=(const self_t &)   = default;

  ForwardIteratorBase(list_node * node)
    : _node(node)
    {}

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
    _node = _node->next;
    return derived();
  }

  derived_t operator++(int) {
    derived_t old = *this;
    _node = _node->next;
    return old;
  }

  constexpr bool operator==(const derived_t & rhs) const {
    return _node == rhs._node;
  }

  constexpr bool operator!=(const derived_t & rhs) const {
    return _node != rhs._node;
  }
};

} // namespace cpppc

#endif // LIST__ITERATOR__ITERATOR_BASE_H__INCLUDED