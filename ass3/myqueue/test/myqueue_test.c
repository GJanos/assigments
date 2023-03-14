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
	myqueue_delete(queue);
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

void test_enqueue(void)
{
	queue = myqueue_create(sizeof(double));
	double *double_obj = (double *)malloc(sizeof(double));
	*double_obj = 10.23;
	myqueue_enqueue(queue, double_obj);
	TEST_ASSERT_EQUAL(1, queue->stack_in->numelem + queue->stack_out->numelem);
	TEST_ASSERT_EQUAL(10.23, *((double *)queue->stack_in->stack->obj));
}

void test_dequeue(void)
{
	queue = myqueue_create(sizeof(double));
	double *double_obj = (double *)malloc(sizeof(double));
	*double_obj = 10.23;
	double *double_obj2 = (double *)malloc(sizeof(double));
	*double_obj2 = -1.24;
	myqueue_enqueue(queue, double_obj);
	myqueue_enqueue(queue, double_obj2);
	void *ret_obj = malloc(sizeof(double));
	myqueue_dequeue(queue, ret_obj);
	TEST_ASSERT_EQUAL_FLOAT(10.23, *((double *)ret_obj));
	free(ret_obj);
	TEST_ASSERT_EQUAL(1, queue->stack_in->numelem + queue->stack_out->numelem);
	TEST_ASSERT_EQUAL_FLOAT(-1.24, *((double *)queue->stack_out->stack->obj));
}

void test_dequeue_empty(void)
{
	int ret1 = myqueue_dequeue(queue, NULL);
	TEST_ASSERT_EQUAL(-1, ret1);

	queue = myqueue_create(sizeof(double));
	int ret2 = myqueue_dequeue(queue, NULL);
	TEST_ASSERT_EQUAL(-1, ret2);
}

int main()
{
	UnityBegin();
	MY_RUN_TEST(test_queue_create_delete);
	MY_RUN_TEST(test_enqueue);
	MY_RUN_TEST(test_dequeue);
	MY_RUN_TEST(test_dequeue_empty);
	return UnityEnd();
}
