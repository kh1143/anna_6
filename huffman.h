#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_


#include "types.h"

void SortTable (List* list);
void MakeTable(List* list, char* str);
void MakeHuffmanTree(Tree* tree, List* list);

void displayNode(TreeNode* node);
void displayList(List* list);


#endif
