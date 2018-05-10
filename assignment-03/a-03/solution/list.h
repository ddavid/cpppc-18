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
    };


    typedef list<ValueT, default_value>               self_t;
    typedef ValueT                                    value_type;
    typedef typename list<value_type>::iterator       list_iterator;
    typedef const typename list<value_type>::iterator const_list_iterator;
    typedef value_type                              & reference;
    typedef const value_type                        & const_reference;
  
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

       iterator(const list_t & list)
       : _list(list)
       { }

       ~iterator() = default;

       self_t & operator++() {
          _list_node = _list_node->next;
          return *this;
       }

       self_t operator++(int) {
          self_t old = *this;
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
         return  (this               == &rhs || // identity
                 ( _list             == rhs._list &&
                   _list_node->next  == rhs._list_node->next &&
                   _list_node->value == rhs._list_node->value));
       }

    private:
      list_t        _list;
      list_node_t * _list_node;
    };
    
  public:
    list()
    : _begin(list_iterator(*this))
    , _end(list_iterator(*this))
    { }

    ~list() = default;

    list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;

    bool empty() const { return !(_head.next == nullptr); }

    void insert_after( const_list_iterator pos, const_reference val )
    {
      list_iterator iter = this->begin();
      while( iter != pos ) { ++iter; }
      list_node insert = { *iter.next, val };
      *iter.next = insert;
    }

    list_iterator begin()  { _begin; }
    
    const_list_iterator begin() const { _begin; }

    list_iterator end()    { _end; }

    const_list_iterator end() const { _end; }
    
  private:

    list_node        _head = { nullptr, default_value };
    static list_node _tail = { nullptr, default_value };

    // self_t * this

    list_iterator  _begin;// = *this;
    list_iterator  _end;
  };

}