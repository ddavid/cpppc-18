#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace cpppc {

template <class Iter>
Iter find_mean_rep(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type value_t;

  int    size = std::distance( first, last );
  double mean = (double)std::accumulate(first, last, 0) / size;

  Iter  lucky = std::find( first, last, mean );
  if ( lucky != last )
  {
    return lucky;
  }
  else 
  {
    std::vector<value_t> tmp(first, last);
    std::vector<double> v( size );
    std::fill( v.begin(), v.end(), mean );

    std::transform( 
        tmp.begin(), 
        tmp.end(), 
        v.begin(), 
        tmp.begin(),
        [](value_t val, double avg) -> value_t { return std::abs(avg - val); });

    auto min_el = std::min_element(tmp.begin(), tmp.end());
    std::advance(first, std::distance(tmp.begin(), min_el));

    return first;
  }
}

} // namespace cpppc

#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
