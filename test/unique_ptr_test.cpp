#include <gtest/gtest.h>
#include "unique_ptr.hpp"

TEST(cppcourse, make_unique) {
  auto test_one = cppcourse::make_unique<int>(5);
  EXPECT_EQ(*test_one.get(), 5);
}

TEST(cppcourse, tets_struct_single_arg) {
  struct TestStructSingleArg {
    TestStructSingleArg(int first) : m_first(first){};
    int m_first;
  };

  auto test_ptr = cppcourse::make_unique<TestStructSingleArg>(6);
  EXPECT_EQ(test_ptr.get()->m_first, 6);
}

TEST(cppcourse, tets_struct_multiple_args) {
  struct TestStructTwoArgs {
    TestStructTwoArgs(int first, int second) : m_first(first), m_second(second){};
    int m_first;
    int m_second;
  };

  auto test_ptr = cppcourse::make_unique<TestStructTwoArgs>(5, 7);
  EXPECT_EQ(test_ptr.get()->m_first, 5);
  EXPECT_EQ(test_ptr.get()->m_second, 7);
}