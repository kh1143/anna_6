#ifndef _LIST_H_
#define _LIST_H_

struct chTable;

struct ListNode
{
	chTable* data;
	ListNode* next;
};

struct List
{
	int size;
	ListNode* front;
	ListNode* back;
};

List* createList ();
void destroyList (List* list);
bool isEmpty (List* list);
int getSize (List* list);
chTable* getFront (List* list);
void addBack (List* list, chTable node);
void addFront (List* list, chTable node);
void insert (List* list, chTable node, int position);
void removeFront (List* list);
void removeBack(List* list);

#endif
