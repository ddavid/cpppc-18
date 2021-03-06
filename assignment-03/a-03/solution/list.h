#ifndef CPPPC__A03__LIST__INCLUDED
#define CPPPC__A03__LIST__INCLUDED

#include <test/TestBase.h>

#include <iterator>

namespace cpppc {

  // list<int32_t, -1>
  template <
    typename ValueT,
    ValueT   default_value = ValueT()>
  class list {

    struct list_node {

       list_node * next;
       ValueT      value;
       bool operator==(const list_node & rhs)
       {
          return((next == rhs.next) && (value == rhs.value));
       }
       const bool operator==(const list_node & rhs) const
       {
          return((next == rhs.next) && (value == rhs.value));
       }

       bool operator!=(const list_node & rhs) { return !(*this == rhs);}
       
       const bool operator!=(const list_node & rhs) const { return !(*this == rhs);} 
       
       /*
       list_node()
       : list_node(nullptr)
       , value(ValueT())
       {}

       list_node(list_node * node)
       : value(ValueT())
       { list_node = node; }

       list_node(list_node * node, ValueT val)
       : list_node(node)
       , value(val)
       {}
       */
    };

    public:
    // list<T>::iterator
    class iterator {
       typedef
         list<ValueT, default_value>
         list_t;
       typedef typename
         list_t::list_node
         list_node_t;
       typedef typename
         list_t::iterator
         self_t;
       typedef 
         std::forward_iterator_tag 
         iterator_category;

       typedef ValueT                 value_type;
       typedef size_t                 size_type;
       typedef ptrdiff_t              difference_type;
       typedef value_type           * pointer;
       typedef const value_type     * const_pointer;
       typedef value_type           & reference;
       typedef const value_type     & const_reference;
    
    public:
       iterator() = delete;

       
       iterator(const list_t & list, list_node_t * node)
       : _list(list)
       , _list_node(node)
       {
        LOG_MESSAGE("Custom constructed Iterator");
        std::cout << _list_node->next  << std::endl;
        std::cout << _list_node->value << std::endl;
       }

       iterator(const iterator & other)
       : _list(other._list)
       , _list_node(other._list_node)
       {
        //LOG_MESSAGE("Copy constructed Iterator");
       }

       ~iterator()
       {
         //std::free(_list_node);
       }

       self_t & operator=(const self_t & rhs)
       {
        // Identitätsvergleich
        if(this != &rhs)
        {
          std::cout << "Not identical" << std::endl;
          if(_list != rhs._list)
          {
            std::cout << "Different Lists" << std::endl;
            _list = rhs._list;
          }
          std::cout << "Trying to assign node" << std::endl;
          _list_node = rhs._list_node;
        }
        std::cout << "Welp" << std::endl;
        return *this;
       }

       self_t & operator++() {
          _list_node = _list_node->next;
          return *this;
       }

       self_t operator++(int) {
          self_t old(*this);
          _list_node = _list_node->next;
          return old;
       }

       const ValueT & operator*() const {
         return _list_node->value;
       }

       ValueT & operator*() {
         return _list_node->value;
       }

       bool operator==(const self_t & rhs) {
         LOG_MESSAGE("WUT");
         return  (this               == &rhs || // identity
                 (_list_node         == rhs._list_node)
                 /*( _list             == rhs._list &&
                   _list_node->next  == rhs._list_node->next &&
                   _list_node->value == rhs._list_node->value)*/);
       }

       const bool operator==(const self_t & rhs) const {
         LOG_MESSAGE("WOT");
         return  (this               == &rhs || // identity
                 ( _list_node        == rhs._list_node)
                 /*( _list             == rhs._list &&
                   _list_node->next  == rhs._list_node->next &&
                   _list_node->value == rhs._list_node->value)*/);
       }

       bool operator!=(const self_t & rhs) { return !(this->operator==(rhs));}

       const bool operator!=(const self_t & rhs) const { return !(this->operator==(rhs));}

    private:
      list_t            _list;
      list_node_t     * _list_node = nullptr;
    };

    typedef list<ValueT, default_value>         self_t;
    typedef ValueT                              value_type;
    typedef typename self_t::iterator           list_iterator;
    typedef const typename self_t::iterator     const_list_iterator;
    typedef value_type                        & reference;
    typedef const value_type                  & const_reference;
    
  public:

    list() = default;

    ~list()
    {
      /*
      list_iterator iter(this->begin());
      while(iter != this->end())
      {
        iter++;
        *iter = { default_value };
      }
      */
      delete _head;
      delete _tail;
    }

    list(const self_t & other)
    : _head(other._head)
    , _tail(other._tail)
    {
      LOG_MESSAGE("Starting List Copy Constructor");
      list_node * o_head = other._head;
      list_node * tmp    = _head;
      while(o_head != other._tail)
      {
        o_head = o_head->next;
        _head->next = new list_node{_head, o_head->value};
        _head  = _head->next;
      }
      _head = tmp;
      //std::free(tmp);
      //std::free(o_head);
    }

    self_t & operator=(const self_t & rhs)
    {
      LOG_MESSAGE("Copy Assignment");
      // Identitätsvergleich
      if( this != &rhs )
      {
        if( _head != _tail )
        {
          this->clear();
        }
        _head = rhs._head;
        _tail = rhs._tail;
      }
      return *this;
    }

    bool operator==(const self_t & rhs) const 
    {
      // Identitätsvergleich
      if( this != &rhs )
      {
        std::cout << "Iterators not identical" << std::endl;
        list_iterator l_iter = this->begin();
        list_iterator r_iter = rhs.begin();
        std::cout << "Iterators constructed" << std::endl;
        while( l_iter != this->end())
        {
          if((*l_iter != *r_iter) || (r_iter == rhs.end()))
          {
            return false;
          }
          ++l_iter;
          ++r_iter;         
        }
        return true;
      } 
      else return true;
    }
    /*
    const bool operator==(const self_t & rhs) const
    {
      // Identitätsvergleich
      if( this != &rhs )
      {
        list_iterator l_iter(*this, this->begin());
        list_iterator r_iter(*this, rhs.begin());
        while( l_iter != this->end())
        {
          l_iter++;
          r_iter++;
          if(l_iter != r_iter)
          {
            return false;
          }
        }
        return true;
      }
      return true;
    }
    */

    bool operator!=(const self_t & rhs) const { return !(*this == rhs);}

    //const bool operator!=(const self_t & rhs) const { return !(*this == rhs);}

    bool empty() const { return _head->next == nullptr; }

    /*
    void insert_after( const_list_iterator pos, const_reference val )
    {
      list_iterator iter = this->begin();
      while( iter != pos ) { ++iter; }
      list_node insert = { *iter.next, val };
      *iter.next = insert;
    }
    */

    void push_front(const value_type & val)
    {
      list_node * new_front = new list_node{ _head, val };
      LOG_MESSAGE("Created new list_node: ");
      _head = new_front;
    }

    const value_type & front() const
    {
      return _head->value;
    }

    // Dirty test to see if push_front() works
    list_node * next() const
    {
      return _head->next;
    }

    void clear()
    {
      list_iterator iter = this->begin();
      while(iter != this->end())
      {
        iter++;
        *iter = { default_value };
      }
    }

    list_iterator begin() { return iterator(*this, _head); }
    
    const_list_iterator begin() const { return iterator(*this, _head); }

    list_iterator end() { return iterator(*this, _tail); }

    const_list_iterator end() const { return iterator(*this, _tail); }
    
  private:

    //list_node       * _front = new list_node
    list_node        * _head  = new list_node{ nullptr, default_value };
    list_node        * _tail  = new list_node{ nullptr, default_value };

    // self_t * this

    //list_iterator  _begin;// = *this;
    //list_iterator  _end;
  };
}

#endif //CPPPC__A03__LIST__INCLUDED