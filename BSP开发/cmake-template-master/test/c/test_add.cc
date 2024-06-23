// @Author: Farmer Li, 公众号: 很酷的程序员/RealCoolEngineer
// @Date: 2021-05-10

#include "gtest/gtest.h"
#include "math/add.h"

TEST(TestAddInt, test_add_int_1) {
  int res = add_int(10, 24);
  EXPECT_EQ(res, 34);
}
