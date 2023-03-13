#include <string.h>
#include <stdio.h>
#include "mystack.h"
#include "myqueue.h"
#include "unity.h"
#include "testrunner.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

QueueMeta_t *queue;
void setUp(void)
{
	queue = NULL;
}

void tearDown(void)
{
	// This is run after EACH test
}

void test_queue_create_delete(void)
{
	queue = myqueue_create(sizeof(int));
	TEST_ASSERT_NOT_EQUAL(NULL, queue);
	TEST_ASSERT_NOT_EQUAL(NULL, queue->stack_in);
	TEST_ASSERT_NOT_EQUAL(NULL, queue->stack_out);
	TEST_ASSERT_EQUAL(0, queue->stack_in->numelem + queue->stack_out->numelem);
	TEST_ASSERT_EQUAL(sizeof(int), queue->item_size);
}

void test_enqueue_dequeue(void)
{
}

int main()
{
	UnityBegin();
	MY_RUN_TEST(test_queue_create_delete);
	MY_RUN_TEST(test_enqueue_dequeue);
	return UnityEnd();
}
