/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "list_test.h"

#include <iostream>

//#include <solution/list.h>
#include <gtest/gtest.h>

typedef cpppc::list<int> list;

TEST_F(ListTest, StandardConcept)
{
  list l_default(1);
  LOG_MESSAGE("Default Assign Constructor:");
  ASSERT_EQ(0, l_default.front());

  LOG_MESSAGE("ListTest.StandardConcept: list__equals");
  ASSERT_EQ(true, l1 == l2);
 
  LOG_MESSAGE("ListTest.IteratorConcept: list_iterator_equals");
  ASSERT_EQ(true, l1.begin() == l1.begin());

  LOG_MESSAGE("ListTest.StandardConcept: list__push_front");
  l1.push_front( 12 );
  ASSERT_EQ(12, l1.front());

  LOG_MESSAGE("ListTest.StandardConcept: list__push_front");
  l1.push_front( 34 );
  ASSERT_EQ(34, l1.front());
  //ASSERT_EQ(12, *(++l1.begin()));
  l1.push_front( 54 );

  LOG_MESSAGE("ListTest.StandardConcept: list__equals");
  ASSERT_EQ(false, l1 == l2);

  LOG_MESSAGE("ListTest.StandardConcept: list__assign");
  l2 = l1;

  LOG_MESSAGE("ListTest.StandardConcept: list__equals");
  //std::cout << l1.front() << std::endl;
  //std::cout << l2.front() << std::endl;
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  while(iter1 != l1.end())
  {
    std::cout << "L1: " << *iter1 << std::endl;
    std::cout << "L2: " << *iter2 << std::endl;
    ++iter1;
    ++iter2;
  }  
  ASSERT_EQ(true, l1 == l2);

  list l3(l2);
  ASSERT_EQ(true, l3 == l1);
}

TEST_F(ListTest, ListConcept)
{
  LOG_MESSAGE("ListTest.ListConcept: list__new");
  ASSERT_EQ(1,  l1.empty());

  LOG_MESSAGE("ListTest.ListConcept: list__begin, list__end");
  ASSERT_EQ(l1.begin(), l1.end());

  LOG_MESSAGE("ListTest.ListConcept: list__push_front(56)");
  l1.push_front(56);

  LOG_MESSAGE("ListTest.ListConcept: list__push_front(78)");
  l1.push_front(78);
 
  LOG_MESSAGE("ListTest.ListConcept: list__push_front(90)");
  l1.push_front(90);

  LOG_MESSAGE("ListTest.ListConcept: list__push_front(34)");
  l1.push_front(34);
  LOG_MESSAGE("ListTest.ListConcept: list__push_front(12)");
  l1.push_front(12);

  LOG_MESSAGE("ListTest.ListConcept: list__copy");
  //list * vcopy = new list(l1);
  list vcopy(l1);
  /*l2 = l1;

  std::cout << l1.front() << std::endl;
  std::cout << vcopy.front() << std::endl;
  */

  ASSERT_EQ(true, l1 == vcopy);

  LOG_MESSAGE("ListTest.ListConcept: list__push_front(1)");
  l2.push_front(1);
  LOG_MESSAGE("ListTest.ListConcept: list__push_front(1)");
  l2.push_front(1);
  LOG_MESSAGE("ListTest.ListConcept: list__push_front(1)");
  l2.push_front(1);

  LOG_MESSAGE("ListTest.ListConcept: list__begin, list__end");
  auto viter = l2.begin();
  auto vend  = l2.end();

  for (; viter != vend; ++viter) {
    *viter += 100;
    //std::cout << *viter << std::endl;
  }

  LOG_MESSAGE("ListTest.ListConcept: list__assign(3, 101)");
  list l_ass;
  l_ass.assign(3, 101);
  std::cout << "Ass: " << l_ass.front() << std::endl;
  std::cout << "L2: " << l2.front() << std::endl;


  LOG_MESSAGE("ListTest.StandardConcept: list__default_construction");
  list l_ctr(10);

  int counter = 0;
  auto iter   = l_ctr.begin();
  while(iter != l_ctr.end())
  {
    ++iter;
    ++counter;
  }
  ASSERT_EQ(10, counter);
  //ASSERT_EQ(10, l_ctr.size());

  LOG_MESSAGE("ListTest.ListConcept: list__insert_after( list__begin, list__end)");
  list l_insert;
  l_insert.push_front(20);
  l_insert.insert_after(l_insert.begin(), 10);

  LOG_MESSAGE("ListTest.ListConcept: list__insert_after( list__begin, list__end)");
  list l_in;
  l_in.push_front(10);
  l_in.push_front(20);

  ASSERT_EQ(true, l_in == l_insert);

  ASSERT_EQ(true, l2 == l_ass);
  ASSERT_EQ(0, l2.empty());
  ASSERT_EQ(0, l1.empty());
  ASSERT_EQ(0, l_ass.empty());

  typename std::iterator_traits<list::list_iterator>::value_type val(10);
  std::cout << val << std::endl;

  //delete vcopy;
}