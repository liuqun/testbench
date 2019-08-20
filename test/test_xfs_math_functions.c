#include <stdint.h> // C11标准定长整数类型uint32_t
#include <unity.h>
#include "xfs_math.h" // 新范式数学运算函数

void setUp(void)
{
	return;
}

void tearDown(void)
{
	return;
}

/**************************************************************************************************
 * test xmath_combine_32ms1b function - 得到任一整数的下一个2的整数幂-1的值
 *
 *************************************************************************************************/
void test_xmath_combine_32ms1b()
{
	uint32_t tested_num_series[]   = {0, 1, 2, 32767, 32768, 32769, 1073741823, 1073741824, 1073741825, 2147483647, 2147483648, 2147483649, 4294967295};
	uint32_t expected_num_series[] = {0, 1, 3, 32767, 65535, 65535, 1073741823, 2147483647, 2147483647, 2147483647, 4294967295, 4294967295, 4294967295};

	for (int var = 0; var < 13; ++var) {
		uint32_t ret = xmath_combine_32ms1b(tested_num_series[var]);
		TEST_ASSERT_EQUAL_UINT32(expected_num_series[var], ret);
	}
}

/**************************************************************************************************
 * test xmath_align32_power2 function - 得到任一整数的下一个2的整数幂的值
 *
 *************************************************************************************************/
void test_xmath_align32_power2()
{
	uint32_t tested_num_series[]   = {0, 1, 2, 32767, 32768, 32769, 1073741823, 1073741824, 1073741825, 2147483647, 2147483648, 2147483649, 4294967295};
	uint32_t expected_num_series[] = {0, 1, 2, 32768, 32768, 65536, 1073741824, 1073741824, 2147483648, 2147483648, 2147483648, 0, 0}; /**< 2147483648 = 0x80000000*/

	for (int var = 0; var < 13; ++var) {
		uint32_t ret = xmath_align32_power2(tested_num_series[var]);
		TEST_ASSERT_EQUAL_UINT32(expected_num_series[var], ret);
	}

}

/**************************************************************************************************
 * test xmath_is_power2 function - 判断任一整数是否是2的整数幂，true返回1，否则返回0
 *
 *************************************************************************************************/
void test_xmath_is_power2()
{
	uint32_t tested_num_series[] = {0, 1, 65500, 65536, 131072, 131073, 2147483647, 2147483648};
	int expected_num_series[]    = {0, 1, 0,     1,     1,      0,      0,          1};

	for (int var = 0; var < 8; ++var) {
		int ret = xmath_is_power2(tested_num_series[var]);
		TEST_ASSERT_EQUAL_INT(expected_num_series[var], ret);
	}
}
