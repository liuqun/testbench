#include "unity.h"
#include "pow_of_2.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_my_function(void)
{
    TEST_ASSERT_TRUE(is_pow_of_2(0));
    TEST_ASSERT_TRUE(is_pow_of_2(1));
    TEST_ASSERT_TRUE(is_pow_of_2(2));
    TEST_ASSERT_TRUE(is_pow_of_2(4));
    TEST_ASSERT_TRUE(is_pow_of_2(8));
    TEST_ASSERT_TRUE(is_pow_of_2(16));
}
