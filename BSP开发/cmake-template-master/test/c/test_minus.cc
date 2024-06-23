// @Author: Farmer Li, 公众号: 很酷的程序员/RealCoolEngineer
// @Date: 2021-05-10

#include "gtest/gtest.h"
#include "math/minus.h"

TEST(TestMinusInt, test_minus_int_1) {
  int res = minus_int(40, 96);
  EXPECT_EQ(res, -56);
}
