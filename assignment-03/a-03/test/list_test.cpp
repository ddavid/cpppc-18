/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "list_test.h"

#include <iostream>

#include <solution/lazy_list.h>
#include <gtest/gtest.h>

typedef cpppc::list<int> list;

TEST_F(ListTest, StandardConcept)
{
  LOG_MESSAGE("ListTest.StandardConcept: list__equals");
  ASSERT_EQ(true, l1 == l2);

  l1.push_front( 12 );
  l1.push_front( 34 );

  ASSERT_EQ(false, l1 == l2);

  LOG_MESSAGE("ListTest.StandardConcept: list__assign");
  l2 = l1;

  ASSERT_EQ(true, l1 == l2);
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
  list * vcopy = new list(l1);

  ASSERT_EQ(1, l1 == *vcopy);

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
  list l_empty;
  l_empty.assign(3, 101);

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
  ASSERT_EQ(10, l_ctr.size());

  LOG_MESSAGE("ListTest.ListConcept: list__insert( list__begin, list__end)");
  list l_insert;
  l_insert.insert(l2.begin(), l2.end());

  ASSERT_EQ(true, l_insert == l2);

  LOG_MESSAGE("ListTest.ListConcept: list__insert( list__begin, list__end)");
  list l_in;
  l_in.insert(20);
  list l_temp;
  l_temp.push_front(20);

  ASSERT_EQ(1, l_in.size());
  ASSERT_EQ(true, l_in == l_temp);

  ASSERT_EQ(true, l2 == l_empty);
  ASSERT_EQ(0, l2.empty());
  ASSERT_EQ(0, l1.empty());
  ASSERT_EQ(0, l_empty.empty());

  delete vcopy;
}