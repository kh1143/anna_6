#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_


#include "types.h"

void MakeTable(List* list, char* str);
void MakeHuffmanTree(Tree* tree, List* list);

void EncodingFile (Tree* tree, char* str, char* ret);
void DecodingFile(Tree* tree, char* code, char* ret);

int EncodingBit (char* code, char* ret);
void DecodingBit (char* bitstr, int bit_len, char* ret);

char* TreeConvertToParenthesisNotation(Tree* tree);
void ParenthesisNotationConvertToTree(Tree* tree, char* treeStr);


#endif
