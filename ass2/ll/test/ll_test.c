#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"
#include "unity.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void print_List(ITEM *list)
{
  if (list == NULL)
  {
    printf("NULL");
    return;
  }
  ITEM *move = list;
  while (move != NULL)
  {
    printf("%d ", move->value);
    move = move->next;
  }
}

void setUp(void)
{
  // This is run before EACH test
}

void tearDown(void)
{
  // This is run after EACH test
}
// add some bad use cases as well
void test_add_first_empty(void)
{
  int ret;
  ITEM *list = NULL;
  ret = add_first(&list, 1);
  TEST_ASSERT_EQUAL(0, ret);
  clean(&list);
}

void test_add_first_second(void)
{
  int ret1, ret2;
  ITEM *list = NULL;
  ret1 = add_first(&list, 1);
  ret2 = add_first(&list, 2);
  TEST_ASSERT_EQUAL(0, ret1);
  TEST_ASSERT_EQUAL(0, ret2);
  clean(&list);
}

void test_add_last_empty(void)
{
  int ret;
  ITEM *list = NULL;
  ret = add_last(&list, 1);
  TEST_ASSERT_EQUAL(0, ret);
  clean(&list);
}

void test_add_last_second(void)
{
  int ret1, ret2;
  ITEM *list = NULL;
  ret1 = add_last(&list, 1);
  ret2 = add_last(&list, 2);
  TEST_ASSERT_EQUAL(0, ret1);
  TEST_ASSERT_EQUAL(0, ret2);
  clean(&list);
}

void test_add_after_list_null(void)
{
  int ret1;
  ITEM *list = NULL;
  ITEM *after = NULL;
  ret1 = add_after(list, after, 1);
  TEST_ASSERT_EQUAL(-1, ret1);
  clean(&list);
}

void test_add_after_c_item_null(void)
{
  int ret1;
  ITEM *list = (ITEM *)malloc(sizeof(ITEM));
  list->next = NULL;
  list->value = 0;
  ITEM *after = NULL;
  ret1 = add_after(list, after, 1);
  TEST_ASSERT_EQUAL(-1, ret1);
  clean(&list);
}

void test_add_after_not_found(void)
{
  int ret1;
  ITEM *list = NULL;
  ITEM *after = (ITEM *)malloc(sizeof(ITEM));
  add_first(&list, 0);
  add_first(&list, 1);
  ret1 = add_after(list, after, 2);
  TEST_ASSERT_EQUAL(-1, ret1);
  free(after);
  clean(&list);
}

void test_add_after_found(void)
{
  int ret1;
  ITEM *list = NULL;
  add_first(&list, 0);
  add_first(&list, 1);
  ITEM *after = list->next;
  ret1 = add_after(list, after, 2);
  TEST_ASSERT_EQUAL(0, ret1);
  TEST_ASSERT_EQUAL(1, list->value);
  TEST_ASSERT_EQUAL(0, list->next->value);
  TEST_ASSERT_EQUAL(2, list->next->next->value);
  clean(&list);
}

void test_rem_first_list_null(void)
{
  int ret1;
  ITEM *list = NULL;
  ret1 = rem_first(&list);
  TEST_ASSERT_EQUAL(-1, ret1);
  clean(&list);
}

void test_rem_first_removed(void)
{
  int ret1;
  ITEM *list = NULL;
  add_first(&list, 0);
  add_first(&list, 1);
  add_first(&list, 2);
  ret1 = rem_first(&list);
  TEST_ASSERT_EQUAL(0, ret1);
  TEST_ASSERT_EQUAL(1, list->value);
  clean(&list);
}

void test_rem_last_removed(void)
{
  int ret1;
  ITEM *list = NULL;
  add_last(&list, 0);
  add_last(&list, 1);
  add_last(&list, 2);
  ret1 = rem_last(&list);
  TEST_ASSERT_EQUAL(0, ret1);
  TEST_ASSERT_EQUAL(0, list->value);
  TEST_ASSERT_EQUAL(1, list->next->value);
  clean(&list);
}

void test_rem_after_removed(void)
{
  int ret1;
  ITEM *list = NULL;
  add_last(&list, 0);
  add_last(&list, 1);
  add_last(&list, 2);
  add_first(&list, 3);
  add_first(&list, 4);
  ret1 = rem_after(list, list->next->next);
  ret1 = rem_after(list, list);
  TEST_ASSERT_EQUAL(0, ret1);
  TEST_ASSERT_EQUAL(4, list->value);
  TEST_ASSERT_EQUAL(0, list->next->value);
  TEST_ASSERT_EQUAL(2, list->next->next->value);
  clean(&list);
}

void test_all_functions(void)
{
  ITEM *list = NULL;
  add_last(&list, 0);
  // 0
  add_last(&list, 1);
  // 0 1
  add_last(&list, 2);
  // 0 1 2
  add_first(&list, 3);
  // 3 0 1 2
  add_first(&list, 4);
  // 4 3 0 1 2
  add_after(list, list->next, 5);
  // 4 3 5 0 1 2
  add_after(list, list->next, 6);
  // 4 3 5 6 0 1 2
  rem_first(&list);
  // 3 5 6 0 1 2
  rem_last(&list);
  // 3 5 6 0 1
  rem_after(list, list->next);
  // 3 5 0 1
  rem_after(list, list);
  // 3 0 1
  TEST_ASSERT_EQUAL(3, list->value);
  TEST_ASSERT_EQUAL(0, list->next->value);
  TEST_ASSERT_EQUAL(1, list->next->next->value);
  clean(&list);
}

int main(int argc, char *argv[])
{
  UnityBegin();

  /* Put your UTs here */
  MY_RUN_TEST(test_add_first_empty);
  MY_RUN_TEST(test_add_first_second);
  MY_RUN_TEST(test_add_last_empty);
  MY_RUN_TEST(test_add_last_second);
  MY_RUN_TEST(test_add_after_list_null);
  MY_RUN_TEST(test_add_after_c_item_null);
  MY_RUN_TEST(test_add_after_not_found);
  MY_RUN_TEST(test_add_after_found);
  MY_RUN_TEST(test_rem_first_list_null);
  MY_RUN_TEST(test_rem_first_removed);
  MY_RUN_TEST(test_rem_last_removed);
  MY_RUN_TEST(test_rem_after_removed);
  MY_RUN_TEST(test_all_functions);

  return UnityEnd();
}
