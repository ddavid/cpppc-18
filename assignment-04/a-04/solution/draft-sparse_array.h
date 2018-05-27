#include <unordered_map>
#include <iterator>

#include <iostream>

namespace cpppc {

template<class SparseArrayT>
class proxy_reference {
  using sparse_array_t  = SparseArrayT;
  using index_t         = typename SparseArrayT::index_t;
  using value_t         = typename SparseArrayT::value_t;
  using self_t          = proxy_reference;
  //using const_reference = const value_t &;
public:
  proxy_reference() = delete;
  proxy_reference(sparse_array_t & sa, index_t offset)
    : _sa(sa), _index(offset)
  { }

  self_t & operator=(const value_t & rhs) 
  {
    _sa.set_value(_index, rhs);
    return *this;
  }

  // Type Cast Conversion
  operator value_t() const
  {
    //std::cout << "TYPE CAST CONVERSION" << std::endl;
    return _sa[_index];
  }

  bool operator==(const value_t & other) const 
  {
    return (*this == other);
  }

private:
  sparse_array_t & _sa;
  index_t          _index;
};

template<class SparseArrayT>
class iterator :
public std::iterator<
  std::random_access_iterator_tag,
  typename SparseArrayT::value_t,
  typename SparseArrayT::index_t,
  typename SparseArrayT::value_t *,
  proxy_reference<SparseArrayT>
>{
public: 
  
  using sparse_array_t    = SparseArrayT;
  using index_t           = typename SparseArrayT::index_t;
  using self_t            = iterator<sparse_array_t>;
  using reference         = proxy_reference<sparse_array_t>;
  using const_reference   = typename SparseArrayT::const_reference;
  //using reference         = typename SparseArrayT::reference; 
  //using const_reference   = typename SparseArrayT::const_reference;

  iterator() = default;  // Yes, because both default initializations are correct.
  iterator(sparse_array_t & sa, index_t offset)
  : _sa(&sa), _index(offset)
  { }

  ~iterator() = default; // Default behaviour is what we want here. 

  reference operator*() 
  {
    return (*_sa)[_index];
  }

  
  const reference operator*() const
  {
    return (*_sa)[_index];
  }
  

  bool operator==(const self_t & rhs) const
  {
    return (this == &rhs) ||
          ((_sa  == rhs._sa) && (_index == rhs._index));
  }

  bool operator!=(const self_t & rhs) const
  { 
    return not (*this == rhs);
  }

  self_t operator+(index_t increment)
  { 
    return self_t(*_sa, (_index + increment));
  }

  self_t operator-(index_t decrement)
  {
    return self_t(*_sa, (_index - decrement));
  }

  // difference_type
  index_t operator-(const self_t & rhs)
  {
    return index_t(_index - rhs._index);
  }

  self_t & operator++()
  {
    ++_index;
    return *this;
  }

  self_t operator++(int)
  {
    self_t result = _index;
    ++_index;
    return result;
  }

  self_t & operator+=(index_t increment)
  {
    _index += increment;
    return *this;
  }

private:
  sparse_array_t * _sa;    // = nullptr
  index_t          _index; // = 0;
  };

template <class T, std::size_t N>
class sparse_array {

public:
  using index_t = int;

  using value_t           = T;
  using self_t            = sparse_array<T, N>;
  //using pointer           = value_t *;
  //using const_pointer     = const value_t *;
  using reference         = typename cpppc::proxy_reference<self_t>;
  using const_reference   = const value_t &;
  using iterator          = typename cpppc::iterator<self_t>;
  using const_iterator    = typename cpppc::iterator<const self_t>;

  sparse_array()                          = default;
  ~sparse_array()                         = default;
  sparse_array(const self_t &  other)     = default;
  sparse_array(self_t       && other)     = default;
  self_t & operator=(const self_t &  rhs) = default;
  self_t & operator=(self_t       && rhs) = default;

  iterator begin() 
  {
    return iterator(*this, 0);
  }

  const_iterator begin() const
  {
    return const_iterator(*this, 0);
  }

  const_iterator end() const 
  {
    return const_iterator(*this, N);
  }

  std::size_t size() const noexcept { return N; }

  reference operator[](int offset) {
    std::cout << "PROXY REF" << std::endl;
    return proxy_reference<self_t>(*this, offset);
  }

  const_reference operator[](int offset) const {
    std::cout << "CONST REF" << std::endl;
    return find_entry_or_default(offset);
  }

  bool operator==(const self_t & other) const
  {
    return    (this      == &other)
           || ((_default == other._default)
           &&  (_entries == other._entries));
  }

  bool operator!=(const self_t & other) const
  {
    return not (*this == other);
  }

  void set_value(index_t pos, value_t val)
  {
    _entries[pos] = val;
  }

private:

  const_reference find_entry_or_default(index_t pos) const
  {
    //typename std::unordered_map<index_t, T>::const_iterator 
    auto iter = std::find(pos, _entries);
    if(iter == _entries.end()) { return _default;}
    else return _entries[pos]; 
  }

private:
  T                               _default;
  std::unordered_map<index_t, T>  _entries;

};
} // namespace cpppc