#ifndef CPPPC__A03__MEASUREMENTS_H__INCLUDED
#define CPPPC__A03__MEASUREMENTS_H__INCLUDED

#include <vector>
#include <cmath>

namespace cpppc {

template <typename T>
class Measurements
{

  typedef Measurements<T>                            self_t;
  typedef T                                          value_t;

  typedef       T &                                  reference;
  typedef const T &                                  const_reference;
  typedef typename std::vector<T>::iterator          iterator;
  typedef typename std::vector<T>::const_iterator    const_iterator;
  typedef size_t                                     size_type;

public:

    Measurements() = default;

    Measurements( size_type size ) : _values( size )
    {}

    ~Measurements() = default;

    self_t & operator=( const_reference other )
    {
        _values = other._values;
    }

    void assign( size_type count, const_reference val )
    {
        _values.assign( count, val );
    }

    bool operator==( const self_t & rhs )
    {
      return ( _values == rhs._values ); 
    }

    const bool operator==( const self_t & rhs ) const
    {
      return ( _values == rhs._values ); 
    }

    reference operator[]( size_type pos ) { return _values[pos]; }

    const_reference operator[]( size_type pos ) const { return _values[pos]; }

    iterator begin()  { return _values.begin(); }
    
    const_iterator begin() const { return _values.begin(); }

    iterator end()    { return _values.end(); }

    const_iterator end() const { return _values.end(); }

    reference front()
    {
        return _values.front();
    }

    const_reference front() const
    {
        return _values.front();
    }

    reference back()
    {
        return _values.back();
    }

    const_reference back() const
    {
        return _values.back();
    }

    bool empty() { return _values.empty(); }

    size_type size() { return _values.size(); }

    void clear() { _values.clear(); }

    //void sort() { _values.sort(); }

    void insert( value_t val ) { _values.push_back(val); }

    void insert( iterator first, iterator last )
    {
        _values.insert( first, last );
    }

    value_t median()
    {
        this->sort();
        int index = std::floor(_values.size() / 2);
        if ( this->begin() == this->end()) { return 0.0; }
        else return _values.at( index );   
    }

    double mean()
    {
        double acc = 0.0;
        iterator viter = _values.begin();
        if(viter == _values.end()) { return acc; }
        else
        {
            while( viter != _values.end()) 
            { 
                acc += (double)(*viter); 
                viter++; 
            }
            return (acc / _values.size());
        }
    }

    double sigma()
    {
        return std::sqrt(this->variance());
    }

    double variance()
    {
        int acc = 0;
        double mean = this->mean();
        iterator viter = _values.begin();
        while( viter != _values.end())
        { 
            acc += std::pow(*viter - mean, 2);
            viter++;
        }
        return (acc / this->size());
    }

private:

  std::vector<T> _values;

};

} // namespace cpppc

#endif // CPPPC__A03__MEASUREMENTS_H__INCLUDED
