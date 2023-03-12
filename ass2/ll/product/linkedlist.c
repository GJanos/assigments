/* SD exercise 1: simple linked list API */
/* Author : R. Frenken                   */
/* Version : 1.0			 */
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise prepend a new ITEM with value value   */
/* to the existing list                            */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_first(ITEM **list, int value)
{
	ITEM *newItem = (ITEM *)malloc(sizeof(ITEM));
	if (newItem == NULL)
		return -1;
	newItem->next = NULL;
	newItem->value = value;

	if (*list != NULL)
	{
		newItem->next = *list;
	}
	*list = newItem;
	return 0;
}

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise append a new ITEM with value value to */
/* the existing list                               */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_last(ITEM **list, int value)
{
	ITEM *newItem = (ITEM *)malloc(sizeof(ITEM));
	if (newItem == NULL)
		return -1;
	newItem->next = NULL;
	newItem->value = value;

	if (*list == NULL)
	{
		*list = newItem;
	}
	else
	{
		ITEM *move = *list;
		while (move->next != NULL)
			move = move->next;
		move->next = newItem;
	}
	return 0;
}

/****************************************************/
/* Insert a new item after current item c_item      */
/* Returns -1 if not enough memory, c_item == NULL, */
/* *list == NULL or c_item not found, otherwise 0   */
/****************************************************/

int add_after(ITEM *list, ITEM *c_item, int value)
{
	if (c_item == NULL || list == NULL)
		return -1;

	ITEM *move = list;
	while (move != c_item && move != NULL)
		move = move->next;

	if (move == NULL)
		return -1;

	ITEM *newItem = (ITEM *)malloc(sizeof(ITEM));
	if (newItem == NULL)
		return -1;
	newItem->next = c_item->next;
	newItem->value = value;
	c_item->next = newItem;

	return 0;
}

/***************************************************/
/* Remove first item of the list                   */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_first(ITEM **list)
{
	if (*list == NULL)
		return -1;
	ITEM *second = (*list)->next;
	free(*list);
	*list = second;
	return 0;
}

/***************************************************/
/* Remove last item of the list                    */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_last(ITEM **list)
{
	if (*list == NULL)
		return -1;
	ITEM *move = *list;
	while (move->next->next != NULL)
		move = move->next;
	free(move->next);
	move->next = NULL;
	return 0;
}

/***************************************************/
/* Remove item after c_item of the list            */
/* Returns -1 list==NULL, c_item not found or      */
/* c_item is the last_element                      */
/***************************************************/

int rem_after(ITEM *list, ITEM *c_item)
{
	if (c_item == NULL || list == NULL)
		return -1;

	ITEM *move = list;
	while (move != c_item && move != NULL)
		move = move->next;

	if (move == NULL || move->next == NULL)
		return -1;

	ITEM *second_from_remove = c_item->next->next;
	free(c_item->next);
	c_item->next = second_from_remove;

	return 0;
}

/*********************************************************/
/* All dynamic memory allocated to the list is freed     */
/* Empty list should point to NULL                       */
/*********************************************************/

void clean(ITEM **list)
{
	ITEM *iter = *list;
	while (iter != NULL)
	{
		ITEM *next = iter->next;
		free(iter);
		iter = next;
	}
	*list = iter;
	return;
}
