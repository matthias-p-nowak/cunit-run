/**
 * \file
 * \author Matthias P. Nowak
 * \date 2018-04-19
 *
 */

#include <stdbool.h>
#include "queue.h"
#include "run_cunit.h"

CUNIT_SUITE("Test Suite",init_suiteQ1,clean_suiteQ1)

int init_suiteQ1() {
/**
 * initializing the test suite
 */
  printf ("suite Q1 initialized\n");
  return 0;
}

int clean_suiteQ1() {
/**
 * clean up the test suite
 */
	printf("\nsuite Q1 clean up\n");
  return 0;
}

// ##########################################################################
// ######################## All the tests ###################################
// ##########################################################################

void test_succeed() {

	CU_ASSERT(true);
}
CUNIT_TEST("always succeed",test_succeed)

void test_structure() {
	queue_t q1; // not initialized
	CU_ASSERT_TRUE(sizeof(q1) > 0);
}
CUNIT_TEST("basic test of structure queue_t",test_structure)

void test_initialization() {
	queue_t q;
	q.size = 8;
	init(&q);
	CU_ASSERT_EQUAL(q.count, 0);
	CU_ASSERT_EQUAL(q.posOut, 0);
	CU_ASSERT_PTR_NOT_EQUAL(q.buffer, 0);
	CU_ASSERT_NOT_EQUAL(q.size, 0);
}
CUNIT_TEST("testing initialization",test_initialization)

void test_empty() {
	queue_t q;
	q.size = 8;
	init(&q);
	CU_ASSERT_PTR_NOT_EQUAL(q.buffer, 0);
	CU_ASSERT_NOT_EQUAL(q.size, 0);
	CU_ASSERT_TRUE(is_empty(&q));
}
CUNIT_TEST("Testing empty first", test_empty)

void test_runQueue() {
	queue_t q;
	q.size = 7; // something not 2^n
	init(&q);
	int retVal; // space
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7 };
	int i;
	int err;
	for (i = 0; i < 3; ++i) {

		CU_ASSERT_EQUAL(enqueue(&q, 42), QUEUE_NO_ERROR);
	}
	i = 0;
	while (!is_empty(&q)) {
		++i;
		CU_ASSERT_EQUAL(dequeue(&q, &retVal), QUEUE_NO_ERROR);
		CU_ASSERT_EQUAL(retVal, 42);
	}
	CU_ASSERT_EQUAL(i, 3);
	// now posOut is somewhere else
	for (int i = 0; i < 7; ++i) {
		// at i==3 the position to store returns to 0
		CU_ASSERT_EQUAL(enqueue(&q, numbers[i]), QUEUE_NO_ERROR);
	}
	// filled to the brink
	for (int i = 0; i < 5; i++) {
		CU_ASSERT_EQUAL(enqueue(&q, 4711), QUEUE_IS_FULL);
	}
	//
	for (int i = 0; i < 7; ++i) {
		// at i==3, the retrieval position gets to 0
		CU_ASSERT_EQUAL(dequeue(&q, &retVal), QUEUE_NO_ERROR);
		CU_ASSERT_EQUAL(retVal, numbers[i]);
	}
	CU_ASSERT_TRUE(is_empty(&q));
}
CUNIT_TEST("running the queue", test_runQueue)
  
