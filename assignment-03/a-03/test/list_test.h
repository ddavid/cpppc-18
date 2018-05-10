#ifndef CPPPC__01__LIST_TEST_H__INCLUDED
#define CPPPC__01__LIST_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include <solution/lazy_list.h>
#include "TestBase.h"

class ListTest : public ::testing::Test {

public:

  cpppc::list<int> l1;
  cpppc::list<int> l2;

  ListTest() {
    LOG_MESSAGE("Opening test suite: ListTest");
  }

  virtual ~ListTest() {
    LOG_MESSAGE("Closing test suite: ListTest");
    //std::cout << "VectorTest Destructor" << std::endl;
  }

  virtual void SetUp() {
    std::cout << "ListTest SetUp" << std::endl;
  }

  virtual void TearDown() {
    std::cout << "ListTest TearDown" << std::endl;
  }

};

#endif // CPPPC__01__LIST_TEST_H__INCLUDED
