#ifndef _LIST_H_
#define _LIST_H_

#include "types.h"


List* createList ();
void destroyList (List* list);

bool isEmpty (List* list);
int getSize (List* list);
TreeNode* getFront (List* list);

void addBack (List* list, TreeNode* node);
void addFront (List* list, TreeNode* node);
void insert (List* list, TreeNode* node, int position);

void removeFront (List* list);
void removeBack(List* list);

#endif
