#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>


template <class Iter>
inline Iter histogram(Iter first, Iter last) {
    typedef typename std::iterator_traits<Iter>::value_type      value_t;
    typedef typename std::iterator_traits<Iter>::difference_type index_t;

    if( first != last )
    {
        std::unordered_map<value_t, int> count_map;

        Iter rm_iter = first;
        std::for_each(
              first
            , last
            , [&](value_t val) -> void 
            {
                ++rm_iter;
                int count = std::count(first, last, val);
                last = std::remove(rm_iter, last, val);
                count_map.insert(std::make_pair(val, count));
            });

        std::transform(
              first
            , last
            , first
            , [&](value_t val) -> value_t
            {
                return value_t(count_map[val]);
            });
    }
    return last;    
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
