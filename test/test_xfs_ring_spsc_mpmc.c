#include <stdint.h> // C11标准定长整数类型uint32_t
#include <unity.h>
// 无锁环状队列相关头文件 xfs_ring
#include "ring/xfs_ring.h"
#include "ring/lockfree/xfs_ring_c11model.h"
#include "ring/lockfree/xfs_ring_impl.h"
#include "ring/lockfree/xfs_ring_share.h"
#include "ring/lockfree/xfs_ring_utils.h"
#include "xfs_math.h" // 自定义数学运算函数
#include "xfs_mem.h" // 自定义内存分配函数


void setUp(void)
{
	return;
}

void tearDown(void)
{
	return;
}

/**************************************************************************************************
 * test new_ring function - 创建一个ring_queue，有4种类型：
 *  sole_producer_sole_comsumer
 *  sole_producer_mult_comsumer
 *  mult_producer_sole_comsumer
 *  mult_producer_mult_comsumer
 *
 * new_ring函数中需要使用xmath_align32_power2函数计算cell_size、memory_size(aligned_cell_size*cell_capacity)的下一个2的整数幂的值，
 * 因此，cell_size、memory_size(aligned_cell_size*cell_capacity)的正确的取值范围是[1, 0x80000000]。
 *************************************************************************************************/
void test_new_ring_sole_producer_sole_comsumer()
{
	unsigned int capacity=0;
	unsigned int cell_size=0;

	//------------------------------------------------------------------------------------------
	// TestCase-5: capacity = 1; cell_size = 1
	//------------------------------------------------------------------------------------------
	capacity = 1;
	cell_size = 1;
	xfs_ring * ring1 = NULL;
	ring1 = new_ring("xfs_ring_sole_producer_sole_comsumer_5", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring1);
	xfs_ring_info * info1 = ring1->info;
	TEST_ASSERT_NOT_NULL(info1);
	TEST_ASSERT_EQUAL(1, info1->capacity);
	TEST_ASSERT_EQUAL(0, info1->mask);
	TEST_ASSERT_EQUAL(0, info1->alignment);
	TEST_ASSERT_EQUAL(1, info1->increment);
	TEST_ASSERT_EQUAL(1, info1->size);
	free_ring(ring1);

	//------------------------------------------------------------------------------------------
	// TestCase-6: capacity = 2; cell_size = 1
	//------------------------------------------------------------------------------------------
	capacity = 2;
	cell_size = 1;
	xfs_ring * ring2 = NULL;
	ring2 = new_ring("xfs_ring_sole_producer_sole_comsumer_6", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring2);
	xfs_ring_info * info2 = ring2->info;
	TEST_ASSERT_NOT_NULL(info2);
	TEST_ASSERT_EQUAL(2, info2->capacity);
	TEST_ASSERT_EQUAL(1, info2->mask);
	TEST_ASSERT_EQUAL(0, info2->alignment);
	TEST_ASSERT_EQUAL(1, info2->increment);
	TEST_ASSERT_EQUAL(2, info2->size);
	free_ring(ring2);

	//------------------------------------------------------------------------------------------
	// TestCase-7: capacity = 0x80000000; cell_size = 1
	//------------------------------------------------------------------------------------------
	capacity = 0x80000000;
	cell_size = 1;
	xfs_ring * ring3 = NULL;
	ring3 = new_ring("xfs_ring_sole_producer_sole_comsumer_7", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring3);
	xfs_ring_info * info3 = ring3->info;
	TEST_ASSERT_NOT_NULL(info3);
	TEST_ASSERT_EQUAL(0x80000000, info3->capacity);
	TEST_ASSERT_EQUAL(0x7FFFFFFF, info3->mask);
	TEST_ASSERT_EQUAL(0, info3->alignment);
	TEST_ASSERT_EQUAL(1, info3->increment);
	TEST_ASSERT_EQUAL(0x80000000, info3->size);
	free_ring(ring3);

	//------------------------------------------------------------------------------------------
	// TestCase-8: capacity = 1; cell_size = 0x80000000
	//------------------------------------------------------------------------------------------
	capacity = 1;
	cell_size = 0x80000000;
	xfs_ring * ring4 = NULL;
	ring4 = new_ring("xfs_ring_sole_producer_sole_comsumer_8", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring4);
	xfs_ring_info * info4 = ring4->info;
	TEST_ASSERT_NOT_NULL(info4);
	TEST_ASSERT_EQUAL(1, info4->capacity);
	TEST_ASSERT_EQUAL(0, info4->mask);
	TEST_ASSERT_EQUAL(31, info4->alignment);
	TEST_ASSERT_EQUAL(0x80000000, info4->increment);
	TEST_ASSERT_EQUAL(0x80000000, info4->size);
	free_ring(ring4);

	//------------------------------------------------------------------------------------------
	// TestCase-9: capacity = 2; cell_size = 0x40000000
	//------------------------------------------------------------------------------------------
	capacity = 2;
	cell_size = 0x40000000;
	xfs_ring * ring5 = NULL;
	ring5 = new_ring("xfs_ring_sole_producer_sole_comsumer_9", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring5);
	xfs_ring_info * info5 = ring5->info;
	TEST_ASSERT_NOT_NULL(info5);
	TEST_ASSERT_EQUAL(2, info5->capacity);
	TEST_ASSERT_EQUAL(1, info5->mask);
	TEST_ASSERT_EQUAL(30, info5->alignment);
	TEST_ASSERT_EQUAL(0x40000000, info5->increment);
	TEST_ASSERT_EQUAL(0x80000000, info5->size);
	free_ring(ring5);

	//------------------------------------------------------------------------------------------
	// TestCase-10: capacity = 16; cell_size = 0x08000000
	//------------------------------------------------------------------------------------------
	capacity = 16;
	cell_size = 0x08000000;
	xfs_ring * ring6 = NULL;
	ring6 = new_ring("xfs_ring_sole_producer_sole_comsumer_10", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring6);
	xfs_ring_info * info6 = ring6->info;
	TEST_ASSERT_NOT_NULL(info6);
	TEST_ASSERT_EQUAL(16, info6->capacity);
	TEST_ASSERT_EQUAL(15, info6->mask);
	TEST_ASSERT_EQUAL(27, info6->alignment);
	TEST_ASSERT_EQUAL(0x08000000, info6->increment);
	TEST_ASSERT_EQUAL(0x80000000, info6->size);
	free_ring(ring6);

	//------------------------------------------------------------------------------------------
	// TestCase-11: capacity = 256; cell_size = 0x00800000
	//------------------------------------------------------------------------------------------
	capacity = 256;
	cell_size = 0x00800000;
	xfs_ring * ring7 = NULL;
	ring7 = new_ring("xfs_ring_sole_producer_sole_comsumer_11", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring7);
	xfs_ring_info * info7 = ring7->info;
	TEST_ASSERT_NOT_NULL(info7);
	TEST_ASSERT_EQUAL(256, info7->capacity);
	TEST_ASSERT_EQUAL(255, info7->mask);
	TEST_ASSERT_EQUAL(23, info7->alignment);
	TEST_ASSERT_EQUAL(0x00800000, info7->increment);
	TEST_ASSERT_EQUAL(0x80000000, info7->size);
	free_ring(ring7);

	//------------------------------------------------------------------------------------------
	// TestCase-12: capacity = 65536; cell_size = 0x00008000
	//------------------------------------------------------------------------------------------
	capacity = 65536;
	cell_size = 0x00008000;
	xfs_ring * ring8 = NULL;
	ring8 = new_ring("xfs_ring_sole_producer_sole_comsumer_12", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring8);
	xfs_ring_info * info8 = ring8->info;
	TEST_ASSERT_NOT_NULL(info8);
	TEST_ASSERT_EQUAL(65536, info8->capacity);
	TEST_ASSERT_EQUAL(65535, info8->mask);
	TEST_ASSERT_EQUAL(15, info8->alignment);
	TEST_ASSERT_EQUAL(0x00008000, info8->increment);
	TEST_ASSERT_EQUAL(0x80000000, info8->size);
	free_ring(ring8);
}

void test_new_ring_sole_producer_mult_comsumer()
{
	//------------------------------------------------------------------------------------------
	// TestCase-1: capacity = 2; cell_size = 1
	//------------------------------------------------------------------------------------------
	unsigned int capacity = 2;
	unsigned int cell_size = 1;
	xfs_ring * ring9 = NULL;
	ring9 = new_ring("xfs_ring_sole_producer_mult_comsumer_1", sole_producer_mult_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring9);
	xfs_ring_info * info9 = ring9->info;
	TEST_ASSERT_NOT_NULL(info9);
	TEST_ASSERT_EQUAL(2, info9->capacity);
	TEST_ASSERT_EQUAL(1, info9->mask);
	TEST_ASSERT_EQUAL(0, info9->alignment);
	TEST_ASSERT_EQUAL(1, info9->increment);
	TEST_ASSERT_EQUAL(2, info9->size);
	/* TODO: SPSC模式测试用例 */
	free_ring(ring9);
}

/* TODO: 待实现另外2种配置选项MPSC/MPMC */
//
//void test_new_ring_mult_producer_sole_comsumer()
//{
//}
//
//void test_new_ring_mult_producer_mult_comsumer()
//{
//}

/**************************************************************************************************
 * test _xfs_ring_enqueue function - ring_queue入队列
 *
 * 入队列时保证始终有一个空闲单元(cell)不使用，用于区分队列空与满的条件：
 *  - 队列空：product_pointer == consumer_pointer
 *  - 队列满：(product_pointer + 1) mod size == consumer_pointer
 *
 * 允许入队列的条件是：
 *  - 入队列前，队列至少还有一个可用的空闲单元(availables >= 1)
 *  - 入队列后，product_pointer.head位置与consumer_pointer.head位置重合
 *  - 队列空间(queue)的读取位置偏移(offset)不能超过队列总空间大小(size)
 *
 * 如果入队列元素的字节空间大小大于cell_size长度，应该截断入队列。
 *************************************************************************************************/
void test_xfs_ring_sole_producer_sole_comsumer_enqueue(void)
{
	uint32_t capacity = 2;
	uint32_t cell_size = 8;
	xfs_ring * ring = NULL;
	ring = new_ring("xfs_ring_sole_producer_sole_comsumer_00", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring);
	xfs_ring_info * info = ring->info;
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(2, info->capacity);
	TEST_ASSERT_EQUAL(1, info->mask);
	TEST_ASSERT_EQUAL(3, info->alignment);
	TEST_ASSERT_EQUAL(8, info->increment);
	TEST_ASSERT_EQUAL(16, info->size);

	//------------------------------------------------------------------------------------------
	// TestCase-1: 队列空时入队列1个元素，并且入队列元素字节大小小于或等于cell_size
	//------------------------------------------------------------------------------------------
	char * _object = "!!!AB!!!";
	unsigned int ret = ring->enqueue(ring, _object);
	TEST_ASSERT_EQUAL(true, ret);
	TEST_ASSERT_EQUAL(0, ring->info->consume_pointer.head);
	TEST_ASSERT_EQUAL(0, ring->info->consume_pointer.tail);
	TEST_ASSERT_EQUAL(1, ring->info->consume_pointer.sole);
	TEST_ASSERT_EQUAL(1, ring->info->product_pointer.head);
	TEST_ASSERT_EQUAL(1, ring->info->product_pointer.tail);
	TEST_ASSERT_EQUAL(1, ring->info->product_pointer.sole);
	TEST_ASSERT_EQUAL_STRING_LEN(_object, ring->info->queue, 8);
	//------------------------------------------------------------------------------------------
	// TestCase-2: 队列满时不允许入队列
	//------------------------------------------------------------------------------------------
	ret = ring->enqueue(ring, _object);
	TEST_ASSERT_EQUAL(false, ret);
	TEST_ASSERT_EQUAL(ring->info->consume_pointer.head, (ring->info->product_pointer.head + 1) & ring->info->mask);

}

void test_xfs_ring_sole_producer_sole_comsumer_enqueue0(void)
{
	uint32_t capacity = 2;
	uint32_t cell_size = 8;
	xfs_ring * ring = NULL;
	ring = new_ring("xfs_ring_sole_producer_sole_comsumer_01", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring);
	xfs_ring_info * info = ring->info;
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(2, info->capacity);
	TEST_ASSERT_EQUAL(1, info->mask);
	TEST_ASSERT_EQUAL(3, info->alignment);
	TEST_ASSERT_EQUAL(8, info->increment);
	TEST_ASSERT_EQUAL(16, info->size);

	//------------------------------------------------------------------------------------------
	// TestCase-3: 准备入队列的元素的字节空间大小大于cell_size
	//------------------------------------------------------------------------------------------
	char * _object = "!!!hello world!!!!!!hello world!!!!!!hello world!!!";
	unsigned int ret = ring->enqueue(ring, _object);
	TEST_ASSERT_EQUAL(true, ret);
	TEST_ASSERT_EQUAL(0, ring->info->consume_pointer.head);
	TEST_ASSERT_EQUAL(0, ring->info->consume_pointer.tail);
	TEST_ASSERT_EQUAL(1, ring->info->consume_pointer.sole);
	TEST_ASSERT_EQUAL(1, ring->info->product_pointer.head);
	TEST_ASSERT_EQUAL(1, ring->info->product_pointer.tail);
	TEST_ASSERT_EQUAL(1, ring->info->product_pointer.sole);
	TEST_ASSERT_EQUAL_STRING_LEN(_object, ring->info->queue, 8); /* 当前测试结果是: !!!hello, 将原字符串截断存储的。 */
	free_ring(ring);
}

void test_xfs_ring_sole_producer_sole_comsumer_enqueue1(void)
{
	uint32_t capacity = 2;
	uint32_t cell_size = 8;
	xfs_ring * ring = NULL;
	ring = new_ring("xfs_ring_sole_producer_sole_comsumer_02", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring);
	xfs_ring_info * info = ring->info;
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(2, info->capacity);
	TEST_ASSERT_EQUAL(1, info->mask);
	TEST_ASSERT_EQUAL(3, info->alignment);
	TEST_ASSERT_EQUAL(8, info->increment);
	TEST_ASSERT_EQUAL(16, info->size);
	//------------------------------------------------------------------------------------------
	// TestCase-4: 准备入队列的元素为NULL
	//------------------------------------------------------------------------------------------
// FIXME: 由于API函数内部的NULL空指针防御不完善, 暂时无法测试enqueue一个NULL指针主动触发该bug
//	char * _object = NULL;
//	unsigned int ret = ring->enqueue(ring, _object);
//	TEST_ASSERT_EQUAL(0, ret);

	free_ring(ring);
}

/* TODO: 待实现另外三种配置选项SPMC/MPSC/MPMC */
//
//void test_xfs_ring_sole_producer_mult_comsumer_enqueue(void)
//{
//}
//
//void test_xfs_ring_mult_producer_sole_comsumer_enqueue(void)
//{
//}
//
//void test_xfs_ring_mult_producer_mult_comsumer_enqueue(void)
//{
//}

/**************************************************************************************************
 * test _xfs_ring_dequeue function - ring_queue出队列
 *
 * 允许出队列的条件是：
 *  - 出队列前，队列至少还有一个元素，不能为空队列(availables != capacity - 1)
 *  - 出队列后，consumer_pointer:head位置不能超过product_pointer:head
 *  - 队列空间(queue)的读取位置偏移(offset)不能超过队列总空间大小(size)
 *
 * 如果出队列元素的字节空间大小仅能等于cell_size长度。
 *************************************************************************************************/
void test_xfs_ring_sole_producer_sole_comsumer_dequeue(void)
{
	unsigned int ret;
	uint32_t capacity = 2;
	uint32_t cell_size = 8;
	xfs_ring * ring = NULL;
	ring = new_ring("xfs_ring_sole_producer_sole_comsumer_000", sole_producer_sole_comsumer, capacity, cell_size);
	TEST_ASSERT_NOT_NULL(ring);
	xfs_ring_info * info = ring->info;
	TEST_ASSERT_NOT_NULL(info);
	TEST_ASSERT_EQUAL(2, info->capacity);
	TEST_ASSERT_EQUAL(1, info->mask);
	TEST_ASSERT_EQUAL(3, info->alignment);
	TEST_ASSERT_EQUAL(8, info->increment);
	TEST_ASSERT_EQUAL(16, info->size);
	//------------------------------------------------------------------------------------------
	// TestCase-1: 队列空时不允许出队列
	//------------------------------------------------------------------------------------------
// FIXME: 由于API函数内部的NULL空指针防御不完善, 暂时无法测试dequeue(ring,NULL)指针主动触发该bug
//	char * _object = NULL;
//	unsigned int ret = ring->dequeue(ring, _object);
//	TEST_ASSERT_EQUAL(false, ret);
//	TEST_ASSERT_EQUAL(ring->info->consume_pointer.head, ring->info->product_pointer.head);

	//------------------------------------------------------------------------------------------
	// TestCase-2: 队列不为空时出队列1个元素，并且出队列元素字节大小仅能等于cell_size
	//------------------------------------------------------------------------------------------
	char * _en_object = "a1b2c3d4xxx";
	ring->enqueue(ring, _en_object); /* 先入队1个元素。 */

	unsigned int aligned_cell_size = ring->cell_size(ring);
	char * _de_object = xfs_malloc("", aligned_cell_size, 64);
	ret = ring->dequeue(ring, _de_object);
	TEST_ASSERT_EQUAL(true, ret);
	TEST_ASSERT_EQUAL(ring->info->consume_pointer.head, ring->info->product_pointer.head);
	TEST_ASSERT_EQUAL_STRING_LEN(_en_object, _de_object, aligned_cell_size);
	free_ring(ring);
}

/* TODO: 待实现另外三种配置选项SPMC/MPSC/MPMC */
//
//void test_xfs_ring_sole_producer_mult_comsumer_dequeue(void)
//{
//}
//
//void test_xfs_ring_mult_producer_sole_comsumer_dequeue(void)
//{
//}
//
//void test_xfs_ring_mult_producer_mult_comsumer_dequeue(void)
//{
//}
