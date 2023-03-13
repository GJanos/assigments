#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
// #include <unistd.h>

#include "mystack.h"
#include "myqueue.h"

QueueMeta_t *myqueue_create(int item_size)
{
	if (item_size < 0)
		return NULL;
	QueueMeta_t *new_queue = (QueueMeta_t *)malloc(sizeof(QueueMeta_t));
	if (new_queue == NULL)
		return NULL;
	new_queue->stack_in = (StackMeta_t *)malloc(sizeof(StackMeta_t));
	if (new_queue->stack_in == NULL)
		return NULL;
	new_queue->stack_out = (StackMeta_t *)malloc(sizeof(StackMeta_t));
	if (new_queue->stack_out == NULL)
		return NULL;
	new_queue->item_size = item_size;

	new_queue->stack_in->numelem = 0;
	new_queue->stack_in->objsize = item_size;
	new_queue->stack_in->stack = NULL;
	new_queue->stack_out->numelem = 0;
	new_queue->stack_out->objsize = item_size;
	new_queue->stack_out->stack = NULL;

	return new_queue;
}

void myqueue_delete(QueueMeta_t *queue)
{
	return;
}

int myqueue_enqueue(QueueMeta_t *que, void *obj)
{
	return 0;
}

int myqueue_dequeue(QueueMeta_t *queue, void *obj)
{
	return 0;
}
