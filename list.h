#ifndef _LIST_H_
#define _LIST_H_

struct chTable;

struct listNode
{
	chTable   data;
	listNode* next;
}

struct List
{
	int size;
	listNode* front;
	listNode* back;
}

#endif
