#include <string>
#include <iostream>
#include <assert.h>
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
	assert (list);

	while(!isEmpty(list))
		removeFront(list);

	delete list;
	list=NULL;
}

bool isEmpty (List* list)
{
	assert (list);
	return list->size == 0;
}

int getListSize (List* list)
{
	assert (list);
	return list->size;
}

TreeNode* getFront (List* list)
{
	assert (list);
	return list->front->data;
}

void addBack (List* list, TreeNode* node)
{
	assert (list);
	ListNode* n = new ListNode;
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

void addFront (List* list, TreeNode* node)
{
	assert (list);
	ListNode* n = new ListNode;
	n->data = node;
	n->next = NULL;
	
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

void insert (List* list, TreeNode* node, int position)
{
	assert (list);
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
		ListNode* n = new ListNode;
		ListNode* tmp = list->front;

		n->data = node;
		n->next = NULL;
		
		for (int i = 0; i < position - 1; i++, tmp=tmp->next);

		n->next = tmp->next;
		tmp->next = n;
		list->size++;
	}	
}

void removeFront (List* list)
{
	assert (list);
	ListNode* tmp = list->front;
	tmp = tmp->next;
	delete list->front;
	list->front = tmp;
	list->size--;
}

void removeBack(List* list)
{
	assert (list);
	ListNode* tmp = list->front;

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

