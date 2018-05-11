#ifndef CPPPC__A02__VECTOR_MEASUREMENTS_TEST_H__INCLUDED
#define CPPPC__A02__VECTOR_MEASUREMENTS_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class VectorMeasurementsTest : public ::testing::Test {

public:

  VectorMeasurementsTest() {
    LOG_MESSAGE("Opening test suite: VectorMeasurementsTest");
  }

  virtual ~VectorMeasurementsTest() {
    LOG_MESSAGE("Closing test suite: VectorMeasurementsTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A02__VECTOR_MEASUREMENTS_TEST_H__INCLUDED
