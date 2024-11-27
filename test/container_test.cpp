#include <gtest/gtest.h>
#include "container.hpp"

TEST(cppcourse, create) {
  cppcourse::container cont;
  EXPECT_TRUE(cont.empty());
}

TEST(cppcourse, add_single) {
  cppcourse::container cont;
  cont.push_back(1);
  EXPECT_EQ(cont.at(0), 1);
  EXPECT_EQ(cont.size(), 1);
  EXPECT_FALSE(cont.empty());
}

TEST(cppcourse, add_multiple)
{
  cppcourse::container cont;
  cont.push_back(1);
  cont.push_back(2);
  cont.push_back(3);
  cont.push_back(4);
  cont.push_back(5);
  EXPECT_EQ(cont.at(0), 1);
  EXPECT_EQ(cont.at(1), 2);
  EXPECT_EQ(cont.at(2), 3);
  EXPECT_EQ(cont.at(3), 4);
  EXPECT_EQ(cont.at(4), 5);
  EXPECT_EQ(cont.size(), 5);
  EXPECT_FALSE(cont.empty());
}

TEST(cppcourse, remove_one)
{
  cppcourse::container cont;
  cont.push_back(1);
  EXPECT_EQ(cont.at(0), 1);

  cont.erase(0);
  EXPECT_TRUE(cont.empty());
}

TEST(cppcourse, assign)
{
  cppcourse::container cont;
  cont.push_back(1);
  EXPECT_EQ(cont.at(0), 1);
  cont.assign(0, 5);
  EXPECT_EQ(cont.at(0), 5);
}

TEST(cppcourse, copy_construct)
{
  cppcourse::container cont;
  cont.push_back(1);
  EXPECT_EQ(cont.at(0), 1);

  cppcourse::container cont_copy{cont};
  EXPECT_EQ(cont_copy.at(0), 1);
  EXPECT_EQ(cont_copy.size(), cont.ize());
}

TEST(cppcourse, copy_assign)
{
  cppcourse::container cont;
  cont.push_back(1);
  EXPECT_EQ(cont.at(0), 1);

  cppcourse::container cont_copy;
  cont_copy = cont;
  EXPECT_EQ(cont_copy.at(0), 1);
  EXPECT_EQ(cont_copy.current_size, cont.current_size);
}

TEST(cppcourse, copy_with_shrink)
{
  cppcourse::container cont;
  cont.push_back(1);
  cont.push_back(2);
  EXPECT_EQ(cont.at(0), 1);
  EXPECT_EQ(cont.at(1), 2);

  cppcourse::container cont_copy;
  cont_copy.push_back(1);

  cont = cont_copy;
  EXPECT_EQ(cont.at(0), 1);
  EXPECT_EQ(cont.current_size, 1);
}


TEST(cppcourse, move)
{

}