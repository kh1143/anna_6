#include <string>
#include <iostream>
#include "list.h"

using namespace std;

List* createList ()
{
	List* list = new List;
	list->size = 0;
	list->front = list->back = NULL;
	
	return list;
}

void destroyList (List* list)
{
	if (!list) return;

	while(!isEmpty(list))
		removeFront(list);

	delete list;		
}

bool isEmpty (List* list)
{
	if (!list) return false;
	return list->size == 0;
}

int getSize (List* list)
{
	if (!list) return -1;
	return list->size;
}

chTable* getFront (List* list)
{
	if (!list) return NULL;
	return list->front->data;
}

void addBack (List* list, chTable* node)
{
	if (!list) return;
	listNode* n = new listNode;
	n->data = node;
	n->next = NULL;

	if (isEmpty(list))
	{
		list->front = n;
		list->back = n;
	}
	else
	{
		list->back->next = n;
		list->back = list->back->next;
	}
	list->size++;
}

void addFront (List* list, chTable* node)
{
	if (!list) return;
	listNode* n = new listNode;
	n->data = node;

	if (isEmpty(list))
	{
		list->front = n;
		list->back = n;
	}
	else
	{
		n->next = list->front;
		list->front = n;
	}
	list->size++;
}

void insert (List* list, chTable* node, int position)
{
	if (!list) return;
	if (isEmpty(list) || position == 0)
	{
		addFront (list, node);
	}
	else if (position >= list->size)
	{
		addBack (list, node);
	}
	else
	{
		listNode* n = new listNode;
		listNode* tmp = list->front;

		n->data = node;
		
		for (int i = 0; i < position - 1; i++, tmp=tmp->next);

		n->next = tmp->next;
		tmp->next = n;
		list->size++;
	}	
}

void removeFront (List* list)
{
	if (!list) return;
	listNode* tmp = list->front;
	tmp = tmp->next;
	delete list->front;
	list->front = tmp;
	list->size--;
}

void removeBack(List* list)
{
	if (!list) return;
	listNode* tmp = list->front;

	if (tmp == list->back)
	{
		removeFront(list);
		return;
	}

	while (tmp->next != list->back)
		tmp = tmp->next;

	delete list->back;
	list->back = tmp;
	list->back->next = NULL;
	list->size--;
}

