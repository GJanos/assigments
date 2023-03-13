#include <string.h>
#include <stdio.h>

#include "mystack.h"
#include "unity.h"
#include "testrunner.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)
StackMeta_t *stack = NULL;
void setUp(void)
{
}

void tearDown(void)
{
	mystack_destroy(stack);
}

void test_create_stack()
{
	StackMeta_t *stack = mystack_create(10);
	TEST_ASSERT_NOT_EQUAL(NULL, stack);
	TEST_ASSERT_EQUAL(0, stack->numelem);
	TEST_ASSERT_EQUAL(10, stack->objsize);
	TEST_ASSERT_NULL(stack->stack);
}

void test_push_once()
{
	StackMeta_t *stack = mystack_create(sizeof(int));
	TEST_ASSERT_NOT_EQUAL(NULL, stack);
	int *int_obj = (int *)malloc(sizeof(int));
	*int_obj = 10;
	int ret1 = mystack_push(stack, int_obj);
	TEST_ASSERT_EQUAL(0, ret1);
	TEST_ASSERT_EQUAL(1, stack->numelem);
	TEST_ASSERT_EQUAL(sizeof(int), stack->objsize);
	TEST_ASSERT_EQUAL(10, *((int *)stack->stack->obj));
	TEST_ASSERT_NULL(stack->stack->next);
}

void test_push_twice()
{
	StackMeta_t *stack = mystack_create(sizeof(double));
	TEST_ASSERT_NOT_EQUAL(NULL, stack);
	double *double_obj = (double *)malloc(sizeof(double));
	*double_obj = 10.23;
	double *double_obj2 = (double *)malloc(sizeof(double));
	*double_obj2 = -1.24;
	int ret1 = mystack_push(stack, double_obj);
	int ret2 = mystack_push(stack, double_obj2);
	TEST_ASSERT_EQUAL(0, ret1);
	TEST_ASSERT_EQUAL(0, ret2);
	TEST_ASSERT_EQUAL(2, stack->numelem);
	TEST_ASSERT_EQUAL(sizeof(double), stack->objsize);
	TEST_ASSERT_EQUAL_FLOAT(-1.24, *((double *)stack->stack->obj));
	TEST_ASSERT_EQUAL_FLOAT(10.23, *((double *)stack->stack->next->obj));
	TEST_ASSERT_NULL(stack->stack->next->next);
}

void test_pop_empty_stack()
{
	StackMeta_t *stack = mystack_create(10);
	TEST_ASSERT_NOT_EQUAL(NULL, stack);
	void *placeholder = NULL;
	int ret1 = mystack_pop(stack, placeholder);
	TEST_ASSERT_EQUAL(-1, ret1);
}

void test_pop_stack_twice()
{
	StackMeta_t *stack = mystack_create(sizeof(double));
	TEST_ASSERT_NOT_EQUAL(NULL, stack);
	double *double_obj = (double *)malloc(sizeof(double));
	*double_obj = 10.23;
	double *double_obj2 = (double *)malloc(sizeof(double));
	*double_obj2 = -1.24;
	mystack_push(stack, double_obj);
	mystack_push(stack, double_obj2);
	void *placeholder = NULL;
	int ret1 = mystack_pop(stack, placeholder);
	int ret2 = mystack_pop(stack, placeholder);
	TEST_ASSERT_EQUAL(0, ret1);
	TEST_ASSERT_EQUAL(0, ret2);
	TEST_ASSERT_EQUAL(0, stack->numelem);
	TEST_ASSERT_EQUAL(sizeof(double), stack->objsize);
	TEST_ASSERT_NULL(stack->stack);
}

int main(int argc, char *argv[])
{
	UnityBegin();
	MY_RUN_TEST(test_create_stack);
	MY_RUN_TEST(test_push_once);
	MY_RUN_TEST(test_push_twice);
	MY_RUN_TEST(test_pop_empty_stack);
	MY_RUN_TEST(test_pop_stack_twice);
	return UnityEnd();
}
