/* ==================================================================
 * File:  /huffman/huffman.cpp
 *
 * Brief: Huffman code algorithm 
 * Desc:  I used ASCII code for distinct mark instead of parenthesis 
 *        '(' and ')' in tree representation
 *          -  0 : NULL
 *          -  1 : left, same as (
 *          -  2 : right, same as ,
 *          -  3 : end, same as )
 *
 * Author: Andrew Heebum Kwak (kh-1143@hanmail.net)
 * Date:   2013-06-06
 * ==================================================================
 */

#include <iostream>
#include <string>
#include <string.h>
#include <assert.h>
#include "huffman.h"
#include "list.h"
#include "tree.h"
using namespace std;

int ind;	// index

// swap function
static void _swap(TreeNode** first, TreeNode** second)
{
	TreeNode* temp = *first;
	*first = *second;
	*second = temp;

}

static void _SortTable (List* list)
{
	if (!list)
		return;
	
	// bubble sort
	for (ListNode* i = list->front; i != NULL; i = i->next)
		for (ListNode* j = list->front; j != NULL; j = j->next)
			if (i->data->table.frequency < j->data->table.frequency)
				_swap(&i->data, &j->data);
}

void MakeTable (List* list, char* str)
{
	assert(list);

	for (int i=0; i < strlen(str); i++)
	{
		bool exist = false;

		// to find same character in list.
		for(ListNode* n = list->front; n != NULL; n = n->next)
		{
			if (str[i] == n->data->table.ch)
			{
				n->data->table.frequency++;
				exist = true;
				break;
			}
		}
		
		// if do not find same character in list, create node and add list.
		if (!exist)
		{
			TreeNode* node = createTreeNode();
			node->table.ch = str[i];
			node->table.frequency = 1;
			addFront(list, node);
		}
	}
	
	_SortTable(list);
}

void MakeHuffmanTree(Tree* tree, List* list)
{
	while(!isEmpty(list))
	{		
		TreeNode *first_node, *second_node;
		TreeNode *root_node = createTreeNode();

		first_node = getFront(list);
		tree->size++;
		removeFront(list);
		
		second_node = getFront(list);
		tree->size++;
		removeFront(list);

		root_node->table.ch = 0;	//  flag(NULL)
		root_node->table.frequency = first_node->table.frequency +
									 second_node->table.frequency;
		root_node->left = first_node;
		root_node->right = second_node;
		tree->size++;

		if(!isEmpty(list))
		{
			addFront(list, root_node);
			_SortTable(list);
		}
		
		tree->root = root_node;	
	}
}

static void _ProcEncodingFile (TreeNode* node, char ch, char* code, char* pcode, char** ret)
{
	if(!node)
		return;
	else if (!node->left && !node->right)
	{
		if (node->table.ch == ch)
		{
			*pcode = '\0';
			*ret = new char[strlen(code+1)];
			assert (*ret);
			strncpy(*ret, code, strlen(code)+1);
		}
	}
	else
	{
		*pcode='0';
		_ProcEncodingFile (node->left, ch, code, pcode+1, ret);		// left
		*pcode='1';
		_ProcEncodingFile (node->right, ch, code, pcode+1, ret);	// right
	}
}

void EncodingFile (Tree* tree, char* str, char* ret)
{
	int index = 0;
	int len = 0;
	char *pcode;

	for(int i=0; i<strlen(str); i++)
	{
		char code[CODE_BUF] = {0,};
		ind = 0;
		pcode = NULL;
		
		_ProcEncodingFile(tree->root, str[i], code, code, &pcode);
		strncat(ret, pcode, strlen(pcode));
		len += strlen(pcode);
	}
	ret[len] = 0;

}

void DecodingFile(Tree* tree, char* code, char* ret)
{
	int index = 0;
	TreeNode* node = tree->root;

	for(int i=0; i<strlen(code); i++)
	{
		if (code[i] == '0')
			node = node->left;
		else if (code[i] == '1')
			node = node->right;

		if (!node->left && !node->right)
		{
			ret[index++] = node->table.ch;
			node = tree->root;
		}
	}
	ret[index] = 0;
}

int EncodingBit (char* code, char* ret)
{
	char bit = 0;
	int len  =0, index = 0;
	
	for (int i = 0; i < strlen(code); i++)
	{
		if (code[i] == '1')
		{
			bit <<= 1;
			bit |= 1;
			
			len++;
		}
		else 
		{
			bit <<= 1;
			len++;
		}
		
		if (len == 8)
		{
			ret[index++] = bit;
			len = 0;
			bit = 0;
		}
	}
	
    bit <<= 1;
    bit |= 1;	// End mark
    len++;

    for(; len != 8; len++)
    {
        bit <<= 1;
    }

    ret[index++] = bit;

	return index;
}

void DecodingBit (char* bitstr, int bit_len, char* ret)
{
	char bit=1, code;
	int index=0;
	
	for (int i=0; i<bit_len; i++)
	{
		for (int j=7; j>=0; j--)
		{
			if (bitstr[i] & (bit<<j))
				ret[index++] = '1';
			else
				ret[index++] = '0';
		}
	}
	for (index=index-1; ret[index]!='1'; index--)
		ret[index] = 0;		// remove surplus bit '0'
	ret[index] = 0;			// remove End mark '1'
}

static void _TreeConvertToParenthesisNotationProc(TreeNode* node, char* ret)
{
	if(!node)
		return;
	if(!node->left && !node->right)
	{
	    ret[ind++] = node->table.ch;
		return;
	}  

	ret[ind++] = 1;		// left mark
	_TreeConvertToParenthesisNotationProc(node->left, ret);
	ret[ind++] = 2;     // right mark
	_TreeConvertToParenthesisNotationProc(node->right, ret);
	ret[ind++] = 3;		// end mark
}

char* TreeConvertToParenthesisNotation(Tree* tree)
{
	assert(tree);
	ind = 0;
	char* str = new char[tree->size * 2];
	_TreeConvertToParenthesisNotationProc(tree->root, str);
	
	return str;
}


static void _ProcParenthesisNotationConvertToTree(Tree* tree, TreeNode* root, char* treeStr)
{
	if (ind >= strlen(treeStr))
		return;

	if (treeStr[ind] == 1)	//left
	{   
		TreeNode* node = createTreeNode();
		tree->size++;
		node->table.ch = 0;
		root->left = node;
		ind++;
		_ProcParenthesisNotationConvertToTree(tree, root->left, treeStr);
	}   
	else if (treeStr[ind] == 2)	//right
	{   
		TreeNode* node = createTreeNode();
		tree->size++;
		node->table.ch = 0;
		root->right = node;
		ind++;
		_ProcParenthesisNotationConvertToTree(tree, root->right, treeStr);
	}   
	else if (treeStr[ind] == 3)	//end
	{   
		ind++;
		return;
	}   
	else
	{   
		root->table.ch = treeStr[ind];
		ind++;
		return;
	}   
	_ProcParenthesisNotationConvertToTree(tree, root, treeStr);
}

void ParenthesisNotationConvertToTree(Tree* tree, char* treeStr)
{
	assert(tree);
	TreeNode* root = createTreeNode();
	tree->root = root;
	tree->size++;
	ind = 0;
	_ProcParenthesisNotationConvertToTree(tree, root, treeStr);
}
