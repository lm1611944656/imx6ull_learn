// @Author: Farmer Li, 公众号: 很酷的程序员/RealCoolEngineer
// @Date: 2021-05-24

#include "gtest/gtest.h"

int fibo(int i) {
  if (i <= 0) {
    return 0;
  }
  if (i == 1 || i == 2) {
    return 1;
  }

  return fibo(i - 1) + fibo(i - 2);
}

TEST(TestGtestDemo, gtest_bool) {
  ASSERT_TRUE(3 == (1 + 2));
  ASSERT_FALSE(3 == 1);
}

TEST(TestGtestDemo, gtest_binary) {
  ASSERT_EQ(1, 1);  // 判断是否相等
  ASSERT_NE(1, 2);  // 判断是否不相等
  ASSERT_LT(1, 2);  // 判断是否小于
  ASSERT_LE(2, 2);  // 判断是否小于等于
  ASSERT_GT(2, 1);  // 判断是否大于
  ASSERT_GE(2, 2);  // 判断是否大于等于
}

TEST(TestGtestDemo, gtest_string) {
  ASSERT_STREQ("str1", "str1");  // 判断字符串是否相等
  ASSERT_STRNE("str1", "str2");  // 判断字符串是否不相等
  ASSERT_STRCASEEQ("STR1", "str1");  // 判断字符串是否相等，忽视大小写
  ASSERT_STRCASENE("Str1", "sTr2");  // 判断字符串是否不相等，忽视大小写
}

TEST(TestFibo, test_fibo_1) {
  int res = fibo(0);
  EXPECT_EQ(res, 0);
}

TEST(TestFibo, test_fibo_2) {
  int res = fibo(1);
  EXPECT_EQ(res, 1);
}

TEST(TestFibo, test_fibo_3) {
  int res = fibo(2);
  EXPECT_EQ(res, 1);
}

TEST(TestFibo, test_fibo_4) {
  int res = fibo(3);
  EXPECT_EQ(res, 2);
}

TEST(TestFibo, test_fibo_5) {
  int res = fibo(4);
  EXPECT_EQ(res, 3);
}
