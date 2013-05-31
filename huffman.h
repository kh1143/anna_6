#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_


#include "types.h"

void MakeTable(List* list, char* str);
void MakeHuffmanTree(Tree* tree, List* list);

void HuffmanEncode(Tree* tree, CodeTable* ct);
void EncodingFile (CodeTable* ct, int table_size, char* str, char* ret);
void DecodingFile(CodeTable* ct, int table_size, char* code, char* ret);
int EncodingBit (char* code, char* ret);
void DecodingBit (char* bitstr, int bit_len, char* ret);


char* TreeConvertToParenthesisNotation(Tree* tree);
void ParenthesisNotationConvertToTree(Tree* tree, char* treeStr);

/*
	testing code
*/
void displayCode(CodeTable* ct, int size);
void displayNode(TreeNode* node);
void displayList(List* list);
 

#endif
