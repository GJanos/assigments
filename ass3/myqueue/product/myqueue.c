#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "mystack.h"
#include "myqueue.h"

QueueMeta_t *myqueue_create(int item_size)
{
	if (item_size < 0)
		return NULL;
	QueueMeta_t *new_queue = (QueueMeta_t *)malloc(sizeof(QueueMeta_t));
	if (new_queue == NULL)
		return NULL;
	new_queue->stack_in = mystack_create(item_size);
	new_queue->stack_out = mystack_create(item_size);
	new_queue->item_size = item_size;
	return new_queue;
}

void myqueue_delete(QueueMeta_t *queue)
{
	if (queue == NULL || queue->stack_in == NULL || queue->stack_out == NULL)
		return;
	mystack_destroy(queue->stack_in);
	mystack_destroy(queue->stack_out);
	free(queue);
}

int myqueue_enqueue(QueueMeta_t *que, void *obj)
{
	return 0;
}

int myqueue_dequeue(QueueMeta_t *queue, void *obj)
{
	return 0;
}
