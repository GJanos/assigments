
#include "mystack.h"
#include "logging.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

StackMeta_t *mystack_create(size_t objsize)
{
	StackMeta_t *new_stack = (StackMeta_t *)malloc(sizeof(StackMeta_t));
	if (new_stack == NULL)
		return NULL;
	new_stack->numelem = 0;
	new_stack->objsize = objsize;
	new_stack->stack = NULL;
	return new_stack;
}

int mystack_push(StackMeta_t *stack, void *obj)
{
	StackObject_t *new_obj = (StackObject_t *)malloc(sizeof(StackObject_t));
	if (new_obj == NULL)
		return -1;

	new_obj->obj = malloc(stack->objsize);
	memcpy(new_obj->obj, obj, stack->objsize);
	new_obj->next = NULL;
	free(obj);

	if (stack->numelem != 0)
		new_obj->next = stack->stack;

	stack->stack = new_obj;
	stack->numelem++;
	return 0;
}

int mystack_pop(StackMeta_t *stack, void *obj)
{
	if (stack == NULL || stack->numelem == 0)
		return -1;

	StackObject_t *second = stack->stack->next;

	if (obj != NULL)
		memcpy(obj, stack->stack->obj, stack->objsize);

	if (stack->stack->obj != NULL)
		free(stack->stack->obj);
	if (stack->stack != NULL)
		free(stack->stack);
	stack->stack = second;
	stack->numelem--;
	return 0;
}

void mystack_destroy(StackMeta_t *stack)
{
	if (stack == NULL)
		return;
	StackObject_t *iter = stack->stack;
	while (iter != NULL)
	{
		StackObject_t *next = iter->next;
		free(iter->obj);
		free(iter);
		iter = next;
	}
	stack->stack = iter;
	free(stack);
}

int mystack_nofelem(StackMeta_t *stack)
{
	return stack == NULL ? -1 : stack->numelem;
}
