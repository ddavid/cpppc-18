#ifndef CPPPC__FORWARD_LIST_H_
#define CPPPC__FORWARD_LIST_H_

#include <iterator>
#include <forward_list>
#include <list>

namespace cpppc {

  // list<int32_t, -1>
  template <typename ValueT>
  class list {

    struct list_node {
       list_node * next;
       ValueT      value;
    };

    typedef size_t                                                  size_type;
    typedef list<ValueT>                                            self_t;
    typedef ValueT                                                  value_type;
    typedef typename std::forward_list<value_type>::iterator        iterator;
    typedef const typename std::forward_list<value_type>::iterator  const_iterator;
    typedef value_type                                            & reference;
    typedef const value_type                                      & const_reference;
    
  public:

    list()  = default;

    ~list() = default;

    list(const self_t & other)
    {
      list_ = other.list_; 
    }

    self_t & operator=(const self_t & rhs)
    { 
      list_ = rhs.list_;
      return *this;
    }

    void assign( size_type count, const_reference value )
    {
      list_.assign(count, value);
    }

    iterator begin()  { return list_.begin(); }
    
    const_iterator begin() const { return list_.begin(); }

    iterator end()    { return list_.end(); }

    const_iterator end() const { return list_.end(); }

    reference front()
    {
      return list_.front();
    }

    const_reference front() const
    {
      return list_.front();
    }

    void sort()
    {
      list_.sort();
    }

    void reverse() 
    {
      list_.reverse();
    }

    bool empty() const { return list_.empty(); }

    bool operator==( const list & rhs )
    {
      return ( list_ == rhs.list_ ); 
    }

    void push_front( value_type val )
    {
      list_.push_front( val );
    }

    void pop_front()
    {
      list_.pop_front();
    }
    
  private:

    std::forward_list<value_type> list_;
    // self_t * this
  };

} // cpppc namespace

#endif // CPPPC__FORWARD_LIST

//cpppc::list<int>;