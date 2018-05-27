#ifndef CPPPC__A03__GOTTSCHLING_LIST__INCLUDED
#define CPPPC__A03__GOTTSCHLING_LIST__INCLUDED

#include <test/TestBase.h>
#include <iterator>

namespace cpppc 
{

template <
typename ValueT,
ValueT   default_value = ValueT()>

class list 
{
  struct list_node
  {
    list_node(const ValueT & val)
    : value(val)
    , next(0)
    {}

    ValueT              value;
    list_node         * next;
  };

  class list_iterator
  {
    typedef
         list<ValueT, default_value>
         list_t;

    typedef typename
         list_t::list_node
         list_node_t;
         
    typedef typename
         list_t::list_iterator
         self_t;

    using value_type = ValueT;

  public:

    list_iterator()
    : _node(0)
    {}

    list_iterator(list_node_t * node)
    : _node(node)
    {}

    self_t & operator=(const self_t & rhs)
    {
      if(_node) { std::free(_node); }
      _node = new list_node_t{ rhs._node->value, rhs._node->next };
    }

    value_type & operator*() { return _node->value; }

    const value_type & operator*() const { return _node->value; }

    self_t & operator++()
    {
      _node = _node->next;
      return *this;
    }

    /*
    self_t operator++(int)
    {
      self_t old(*(*this));
      _node = _node->next;
      return old;
    }
    */

    bool operator==(const self_t & other) const
    {
      return !(*this != other);
    }

    bool operator!=(const self_t & other) const
    {
      return _node != other._node;
    }

    private:
      list_node_t * _node;
  };

  typedef list<ValueT, default_value>             self_t;
  typedef ValueT                                  value_type;
  typedef typename self_t::list_iterator          list_iterator;
  typedef const typename self_t::list_iterator    const_list_iterator;
  typedef value_type                            & reference;
  typedef const value_type                      & const_reference;


public:

  list()
  : _head(0)
  , _tail(nullptr)
  {}

  list(int count, value_type val = default_value)
  : _head(0)
  , _tail(nullptr)
  {
    while( count > 0 ) { this->push_front( default_value ); --count;}
  }

  //------- Rule of 3 -------//

  // Destructor
  ~list()
  {
    while (_head)
    {
      list_node * tmp = _head->next;
      delete _head;
      _head = tmp;
    }
  }

  // Copy Constructor
  list(const self_t & other)
  {
    list_iterator iter = other.begin();
    while(iter != other.end())
    {
      /*
      list_node * tmp = new list_node(*iter);
      if(!_head) { _tail = _head = tmp; }
      else { _tail = _tail->next = tmp; }
      ++iter;
      */
      list_node * tmp = new list_node(*iter);
      _tail = (_head ? _tail->next : _head ) = tmp; 
      ++iter;  
    }
  }

  // Move Constructor
  list(self_t && other)
  : _head(other._head)
  , _tail(other._tail)
  {
    other._head = other._tail = nullptr;
  }

  // Copy Assignment
  self_t & operator=(const self_t & other)
  {
    // Identity
    if(this != &other)
    {
      // Clean up *this
      if(!this->empty())
      {
        while(_head)
        {
          list_node * tmp = _head->next;
          delete _head;
          _head = tmp;
        }
      }
      // Copy contents of other into *this
      list_iterator iter = other.begin();
      while(iter != other.end()) 
      { 
        list_node * tmp = new list_node(*iter);
        _tail = (_head ? _tail->next : _head ) = tmp; 
        ++iter; 
      }
    }
    return *this;
  }

  // Move Assignment
  self_t & operator=(self_t && other)
  {
    if(this != &other)
    {
      // Clean up *this
      if(!this->empty())
      {
        while(_head)
        {
          list_node * tmp = _head->next;
          delete _head;
          _head = tmp;
        }
      }
      _head = other._head;
      _tail = other._tail;

      other._head = other._tail = nullptr;
    }
    return *this;
  }

  self_t & assign(int count, value_type val)
  {
    this->clear();
    while( count > 0 ) { count--; this->push_front( val );}
    return *this;
  }

  //------- El Access -------//
  
  const_reference front() const { return _head->value; }
  
  //------- Iterators -------//
  
  list_iterator begin() { return list_iterator(_head);}

  const_list_iterator begin() const { return list_iterator(_head);}

  list_iterator end() { return list_iterator(0);}

  const_list_iterator end() const { return list_iterator(0);}

  //------- Capacity --------//

  bool empty() const { return (this->begin() == this->end()); } 

  //------- Modifiers -------//
  
  void clear()
  {
    while(_head)
    {
      this->pop_front();
    }
  }

  void insert_after(const_list_iterator pos, const value_type & val)
  {
    list_iterator iter  = this->begin();
    list_node * trailer = _head;      
    while(iter != pos) { ++iter; trailer = trailer->next;}
    list_node * tmp = new list_node(val);
    if(trailer->next) { tmp->next = trailer->next; }
    trailer->next = tmp;
  }

  void push_front(const value_type & val)
  {
    list_node * new_front = new list_node(val);
    new_front->next       = _head;
    //LOG_MESSAGE("Created new list_node: ");
    // If list is empty:
    if(!_head) { _tail = _head = new_front; }
    else _head = new_front; 
  }

  void pop_front()
  {
    if(_head)
    {
      list_node * tmp = _head->next;
      delete _head;
      _head = tmp;
    }
  }

  //---- Non-member functions ----//
  
  bool operator==(const self_t & other) const
  {
    if( this != &other )
    {
      list_iterator s_iter = this->begin();
      list_iterator o_iter = other.begin();
      while(s_iter != this->end())
      {
        if((o_iter == other.end()) || (*s_iter != *o_iter)) { return false;}
        ++o_iter;
        ++s_iter;
      }
      return true;
    }
    return true;
  }

  bool operator!=(const self_t & other) const { return !(*this == other); }

private:
  list_node * _head;
  list_node * _tail;
};
} // namespace cpppc

#endif //CPPPC__A03__GOTTSCHLING_LIST__INCLUDED