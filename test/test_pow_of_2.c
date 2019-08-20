/*
代码风格要求:
1. 为了与Qt开发环境风格一致, 要求调整eclipse代码对齐方式, 将所有tab展开并替换为4个空格.
2. (待定)
*/

#include "unity.h"
#include "pow_of_2.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_math_func_(void)
{
    TEST_ASSERT_FALSE_MESSAGE(is_pow_of_2(0), "注意:0不是2的整数幂次方!!");
    TEST_ASSERT_TRUE(is_pow_of_2(1));
    TEST_ASSERT_TRUE(is_pow_of_2(2));
    TEST_ASSERT_TRUE(is_pow_of_2(4));
    TEST_ASSERT_TRUE(is_pow_of_2(8));
    TEST_ASSERT_TRUE(is_pow_of_2(16));
    TEST_ASSERT_TRUE(is_pow_of_2(0x40000000U));
    TEST_ASSERT_TRUE(is_pow_of_2(0x80000000U));
    TEST_ASSERT_FALSE(is_pow_of_2(0x7FFFFFFFU));
}
