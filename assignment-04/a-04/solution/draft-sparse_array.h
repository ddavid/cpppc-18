#include <unordered_map>
#include <iterator>

#include <iostream>

namespace cpppc {

template <class T, std::size_t N>
class sparse_array;

template <class SparseArray>
class sparse_array_proxy_ref {
  using self_t          = sparse_array_proxy_ref<SparseArray>;
  using index_t         = typename SparseArray::index_t;
  
public:
  using sparse_array_t  = SparseArray;
  using value_type      = typename SparseArray::value_type;
  using const_reference = const value_type &;

public:
  sparse_array_proxy_ref() = delete;
  sparse_array_proxy_ref(sparse_array_t & sa, index_t offset)
    : _sa(sa), _index(offset)
  { }
  sparse_array_proxy_ref(const self_t & rhs) = default;

  //sparse_array_proxy_ref(const value_type rhs) = default;

  self_t & operator=(const self_t & rhs) 
  {
    if( this != &rhs )
    {
      _sa     = rhs._sa;
      _index  = rhs._index;
    }
    return *this;
  }

  self_t & operator=(const value_type rhs) 
  {
    _sa.set_value(_index, rhs);
    return *this;
  }

  // Type Cast Conversion
  operator value_type() const
  {
    //std::cout << "TYPE CAST CONVERSION" << std::endl;
    return _sa.at(_index);
  }
  /*
  // Type Cast Conversion
  operator const value_type &() const
  {
    std::cout << "Const TYPE CAST CONVERSION" << std::endl;
    return _sa[_index];
  }*/

private:
  sparse_array_t & _sa;
  index_t          _index;
};

template <class SparseArray>
class sparse_array_iterator :
public std::iterator<
  std::random_access_iterator_tag,
  typename SparseArray::value_type,
  typename SparseArray::index_t,
  typename SparseArray::pointer,
  sparse_array_proxy_ref<SparseArray> >{
public: 
  
  using sparse_array_t    = SparseArray;
  using self_t            = sparse_array_iterator<SparseArray>; 
  
  using index_t           = typename std::iterator_traits<self_t>::difference_type;

  using reference         = sparse_array_proxy_ref<SparseArray>;
  using const_reference   = const typename SparseArray::value_type &;

  sparse_array_iterator() = default;  // Yes, because both default initializations are correct.
  sparse_array_iterator(sparse_array_t & sa, index_t offset)
  : _sa(&sa), _index(offset)
  { }

  ~sparse_array_iterator() = default; // Default behaviour is what we want here. 

  reference operator*() 
  {
    return (*_sa)[_index];
  }

  const_reference operator*() const
  {
    return (*_sa)[_index];
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
    self_t tmp = _index;
    ++_index;
    return tmp;
  }

  self_t & operator--()
  {
    --_index;
    return *this;
  }

  self_t operator--(int)
  {
    self_t tmp = _index;
    --_index;
    return tmp;
  }

  self_t & operator+=(index_t increment)
  {
    _index += increment;
    return *this;
  }

  self_t & operator-=(index_t decrement)
  {
    _index -= decrement;
    return *this;
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

  bool operator<(const self_t & other) const
  {
    return _index < other._index;
  }

  bool operator<=(const self_t & other) const
  {
    return _index <= other._index;
  }

  bool operator>(const self_t & other) const
  {
    return !(*this <= other);
  }

  bool operator>=(const self_t & other) const
  {
    return !(*this < other);
  }

private:
  sparse_array_t * _sa;    // = nullptr
  index_t          _index; // = 0;
};  

template <class T, std::size_t N>
class sparse_array {

  using self_t                 = sparse_array<T, N>;

public:

  using index_t                = int;

  using value_type             = T;
  using size_type              = std::size_t;
  using difference_type        = std::ptrdiff_t;
  
  using reference              = sparse_array_proxy_ref<self_t>;
  using const_reference        = const value_type &;
  
  using pointer                = value_type *;
  using const_pointer          = const value_type *;

  using iterator               = sparse_array_iterator<self_t>;
  using const_iterator         = sparse_array_iterator<const self_t>;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;


  sparse_array()                          = default;
  ~sparse_array()                         = default;
  sparse_array(const self_t &  other)     = default;
  sparse_array(self_t       && other)     = default;
  self_t & operator=(const self_t &  rhs) = default;
  self_t & operator=(self_t       && rhs) = default;

//------ El access -----//

  const_reference at(index_t index) const
  {
    if (index < 0 || static_cast<int>(this->size()) <= index) {
      std::cout << "This index is out of bounds: " << index << std::endl;
      throw std::invalid_argument("index out of bounds");
    }
    return this->find_entry_or_default(index);
  }

  reference operator[](int offset) {
    //std::cout << "PROXY REF" << std::endl;
    return reference(*this, offset);
  }

  const_reference operator[](int offset) const {
    //std::cout << "CONST REF" << std::endl;
    return this->find_entry_or_default(offset);
  }

  reference front(){ return *(this->begin());}

  const_reference front() const { return *(this->begin());}

  reference back() { return *(this->end() - 1);}

  const_reference back() const { return *(this->end() - 1);}

//------ Iterators ------//

  iterator begin() { return iterator(*this, 0);}

  const_iterator cbegin() const { return const_iterator(*this, 0);}

  iterator end() { return iterator(*this, N);}

  const_iterator cend() const { return const_iterator(*this, N);}

  const_iterator end() const { return iterator(*this, N);}

  reverse_iterator rbegin() { return reverse_iterator(end());}

  const_reverse_iterator crbegin() const { return const_reverse_iterator(end());}

  reverse_iterator rend() { return reverse_iterator(begin());}

  const_reverse_iterator crend() const { return const_reverse_iterator(begin());}

//----- Capacity ------//

  bool empty() const { return !(size() > 0);}

  size_type size() const noexcept { return N;}

  size_type max_size() const { return N;} // For our sparse array

//------ Operations ------//

  void fill(const_reference val)
  {
    iterator iter = begin();
    std::cout << "Started filling sparse_array" << std::endl;
    while(iter != end())
    {
      *iter = val;
      ++iter;
    }
    std::cout << "Finished filling sparse_array" << std::endl;
  }
  // Exchanges the contents of the container with those of other. 
  // Does not cause iterators and references to associate with the other container.
  /*void swap(self_t & other) 
  {
    // For std::array, walk through both arrays applying std::swap?
    // reference doesn't say anything about sizes of both arrays
    if(this != &other) // identity
    {
      if(this->size() == other.size())
      {
        //while...
        {
          //swap(iter1, iter2);
        }
      }
    }
  }*/

//------ Non-member Functions -------//

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

  bool operator<(const self_t & other) const
  {
    return std::lexicographical_compare(
      cbegin(),
      cend(), 
      other.cbegin(),
      other.cend());
  }

  bool operator>(const self_t & other) const
  {
    return std::lexicographical_compare(
      cbegin(),
      cend(), 
      other.cbegin(),
      other.cend(),
      [](const_reference fst, const_reference snd) -> bool 
      { 
        return fst > snd;
      });
  }

  bool operator<=(const self_t & other) const
  {
    return !(*this > other);
  }

  bool operator>=(const self_t & other) const
  {
    return !(*this < other);
  }
  
  /*
  template<typename Index>
  reference get<Index>(const self_t & arr)
  {
    return arr[Index];
  }

  void swap
  */
  
  void set_value(index_t pos, value_type val)
  {
    _entries[pos] = val;
  }

private:

  const_reference find_entry_or_default(const index_t & pos) const
  {
    //typename std::unordered_map<index_t, T>::const_iterator 
    auto iter = _entries.find(pos);
    if(iter == _entries.end()) { return _default;}
    else return std::get<1>(*iter); 
  }

private:
  T                               _default;
  std::unordered_map<index_t, T>  _entries;

};
} // namespace cpppc