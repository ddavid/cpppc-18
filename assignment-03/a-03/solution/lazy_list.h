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

    list( size_type count ) : list_(count)
    { }

    ~list() = default;

    list(const self_t & other)
    {
      list_ = other.list_; 
    }

    int32_t size() 
    {
      int32_t count = 0;
      auto viter = this->begin();
      while(viter != this->end()) { ++viter; ++count; }
      return count;
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

    void insert ( value_type val )
    {
      list_.push_front(val);
    }

    void insert( iterator begin, iterator end )
    {
      iterator temp_iter = begin;
      while( temp_iter != end ) 
      { 
        list_.push_front(*temp_iter);
        temp_iter++; // Only ++iter available? 
      }
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

    reference back()
    {
      this->reverse();
      reference tmp = this->front();
      this->reverse();
      return tmp;
    }

    const_reference back() const
    {
      this->reverse();
      const_reference tmp = this->front();
      this->reverse();
      return tmp;
    }

    void sort()
    {
      list_.sort();
    }

    void reverse() 
    {
      list_.reverse();
    }

    void clear() { list_.clear(); }

    bool empty() const { return list_.empty(); }

    bool operator==( const list & rhs )
    {
      return ( list_ == rhs.list_ ); 
    }
    
    const bool operator==( const list & rhs ) const
    {
      return ( list_ == rhs.list_ ); 
    }

    reference operator[]( size_type pos ) 
    { 
      iterator viter = this->begin();
      while(( viter != this->end()) && ( pos != 0 ))
      {
        --pos;
        viter++;
      }
      return *viter;
    }

    const_reference operator[]( size_type pos ) const
    { 
      iterator viter = this->begin();
      while(( viter != this->end()) && ( pos != 0 ))
      {
        --pos;
        viter++;
      }
      return *viter;
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