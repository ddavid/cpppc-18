
#include "sparse_array_test.h"

#include <solution/draft-sparse_array.h>

#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>

// you might want to set this to 1 for debugging
constexpr int NMULT = 1;

using namespace cpppc;


TEST_F(SparseArrayTest, StandardConcept)
{
  constexpr size_t N = 1000 * NMULT;

  LOG_MESSAGE("SparseArrayTest.StandardConcept: default ctor");
  sparse_array<int, N> sa1 { };
  sparse_array<int, N> sa2 { };

  LOG_MESSAGE("SparseArrayTest.StandardConcept: ==");
  ASSERT_EQ(sa1, sa1);
  ASSERT_EQ(sa2, sa2);

  ASSERT_EQ(N, sa1.size());
  ASSERT_EQ(N, sa2.size());

  int test = (sa1 == sa2) ? 10 : 0;

  std::cout << test << std::endl;

  LOG_MESSAGE("MADE IT THIS FAR");

  sa1[400] = 44;
  sa1[500] = 55;

  ASSERT_EQ(44, sa1[400]);
  ASSERT_EQ(55, sa1[500]);

  LOG_MESSAGE("SparseArrayTest.StandardConcept: =");
  sa2 = sa1;
  ASSERT_EQ(sa1, sa2);

  ASSERT_EQ(44, sa2[400]);
  ASSERT_EQ(55, sa2[500]);

  LOG_MESSAGE("SparseArrayTest.StandardConcept: Copy Constructor");

  sparse_array<int, N> sa3(sa2);
  ASSERT_EQ(sa1, sa3);
}

TEST_F(SparseArrayTest, RandomAccess)
{
  LOG_MESSAGE("SparseArrayTest.RandomAccess");

  constexpr int N = 840 * NMULT;
  sparse_array<int, N> sa;

  LOG_MESSAGE("Test");
  
  auto it = sa.begin() + 621;

  *it  = 123;
  ASSERT_EQ(it, std::find(sa.begin(), sa.end(),  123));

  it  += 100;
  *it  = 2340;
  ASSERT_EQ(it, std::find(sa.begin(), sa.end(), 2340));
}

TEST_F(SparseArrayTest, ArrayInterface)
{
  LOG_MESSAGE("SparseArrayTest.ArrayInterface");

  constexpr int N = 540 * NMULT;
  sparse_array<int, N> sa1 {};
  sparse_array<int, N> sa2 {};

  ASSERT_EQ(false, sa1.empty());
  ASSERT_EQ(false, sa2.empty());

  ASSERT_EQ(sa1.size(), sa1.max_size());
  ASSERT_EQ(sa2.size(), sa2.max_size());

  LOG_MESSAGE("I'm almost jumping off!");

  //std::cout << "Size: " << sa1.size() <<" " << sa1.max_size() << std::endl;

  sa1.front() = 111;
  std::cout << sa1.front() << std::endl;
  sa1.back()  = 999;
  std::cout << sa1.back() << std::endl;

  ASSERT_EQ(*sa1.begin(), sa1.front());
  ASSERT_EQ(*sa1.begin(), 111);
  ASSERT_EQ(*sa1.rbegin(), sa1.back());
  ASSERT_EQ(*sa1.rbegin(), 999);

  std::swap(sa1, sa2);

  ASSERT_EQ(*sa2.begin(), sa2.front());
  ASSERT_EQ(*sa2.begin(), 111);
  ASSERT_EQ(*sa2.rbegin(), sa2.back());
  ASSERT_EQ(*sa2.rbegin(), 999);

  LOG_MESSAGE("OOMKILLER");
  // You know what you didn't do in a long time? Swapping to disk.
  // Say hello to oomkiller from fuchsto.
  sa2.fill(42);
  ASSERT_NE(sa1, sa2);
  ASSERT_EQ(sa2.begin(), std::find(sa2.begin(), sa2.end(), 42));
  ASSERT_EQ(sa2[10],  42);
  ASSERT_EQ(sa2[100], 42);
  ASSERT_EQ(sa2[300], 42);

  sa1.fill(42);
  ASSERT_EQ(sa1, sa2);

  sa2[sa2.size() / 2] = 0;

  std::vector<bool> vb(10, true);
  std::vector<bool> vb2(vb);
  vb[5] = false;

  ASSERT_LT(vb, vb2);

  ASSERT_LT(sa2, sa1);
  ASSERT_GT(sa1, sa2);

  ASSERT_EQ(1, (sa2 < sa1));
  LOG_MESSAGE("WUT");
  ASSERT_EQ(1, (sa1 > sa2));

  sa2.fill(std::numeric_limits<int>::max());
/*
  int idx;

  idx = 2;
  std::generate_n(sa2.begin() + 220, 16,
                  [&]() { return idx *= 2; });

  idx = 2;
  std::for_each(sa2.begin() + 220,
                sa2.begin() + 220 + 16,
                [&](int v) { ASSERT_EQ(idx *= 2, v); });

  std::sort(sa2.begin(), sa2.end());

  idx = 2;
  std::for_each(sa2.begin(),
                sa2.begin() + 16,
                [&](int v) { ASSERT_EQ(idx *= 2, v); });
*/
  LOG_MESSAGE("SparseArrayTest.ArrayInterface: sa2 = { %s }",
              range_to_string(sa2.begin(), sa2.begin() + 16).c_str());
}