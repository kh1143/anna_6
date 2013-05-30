#include <iostream>
#include <string>
#include <string.h>
#include <assert.h>
#include "huffman.h"
#include "list.h"
#include "tree.h"

using namespace std;

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

int ind;
void _HuffmanEncodeProc(TreeNode* node, CodeTable* ct, char* code, char* pcode)
{
	if (!node)
		return;
	else if (!node->left && !node->right)
	{
		*pcode = '\0';
		ct[ind].ch = node->table.ch;
		ct[ind].code = new char[strlen(code)+1];
		assert(ct[ind].code);
		strncpy(ct[ind++].code, code, strlen(code)+1);
	}
	else
	{
		*pcode='0';
		_HuffmanEncodeProc(node->left, ct, code, pcode+1);
		*pcode='1';
		_HuffmanEncodeProc(node->right, ct, code, pcode+1);
	}
}

void HuffmanEncode(Tree* tree, CodeTable* ct)
{
	assert(tree);
	assert(ct);

	char code[CODE_BUF] = {0,};
	ind = 0;

	_HuffmanEncodeProc(tree->root, ct, code, code);
}

void EncodingFile (CodeTable* ct, int size, char* str, char* ret)
{
	for(int i=0; i<strlen(str); i++)
		for(int j=0; j<size; j++)
			if(str[i] == ct[j].ch)
				strncat(ret, ct[j].code, strlen(ct[j].code));
}

void DecodingFile(CodeTable* ct, int size, char* code, char* ret)
{
	int k=0;
	char cmp[CODE_BUF] ={0,};
	
	for(int i=0; i<strlen(code); i++)
	{
		cmp[k++] = code[i];
		 
		for(int j=0; j<size; j++)
		{
			if(strcmp(cmp, ct[j].code) == 0)
			{
				*ret = ct[j].ch;
				ret++;
				memset(cmp, 0, sizeof(cmp));
				k=0;
			}
		}
	}
	*ret = 0;
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
	
	if (len != 0)
	{
		bit <<= 1;
		bit |= 1;	// End mark
		len++;
		for(; len != 8; len++)
		{
			bit <<= 1;
		}
		ret[index++] = bit;
	}
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

static char str[BUF_SIZE]={0,};
static int i=0;
void _TreeConvertToParenthesisNotaitonProc(TreeNode* node, char* ret)
{
	if(node->table.ch != 0)
		return;

	if(node->left->table.ch != 0 && node->right->table.ch != 0)
	{
		str[i++] = node->left->table.ch;
		str[i++] = ',';
		str[i++] = node->right->table.ch;
		return;
	}
	else if(node->left->table.ch != 0 && node->right->table.ch == 0)
	{
		str[i++] = node->left->table.ch;
		str[i++] = ',';
		_TreeConvertToParenthesisNotaitonProc(node->right, ret);
		str[i++] = ')';
		return;
	}
	else
	{
		str[i++] = '(';
		_TreeConvertToParenthesisNotaitonProc(node->left, ret);
		return;
	}
}

void TreeConvertToParenthesisNotaiton(Tree* tree, char* ret)
{
	assert(tree);
	_TreeConvertToParenthesisNotaitonProc(tree->root, ret);
	strcpy(ret, str);	
}

void ParenthesisNotaitonConvertToTree(Tree* tree, char* ret)
{
	
}


// display code
void displayCode(CodeTable* ct, int size)
{
	for (int i=0; i<size; i++)
		cout << "ch : " << ct[i].ch << " "<< ct[i].code << endl;

}

// display node
void displayNode(TreeNode* node)
{
	assert(node);
	cout << "ch : " << node->table.ch <<
				" frequency : " << node->table.frequency << endl;
}

// display all list node
void displayList(List* list)
{
	assert(list);
	for(ListNode* n = list->front; n != NULL; n = n->next)
	{
		displayNode(n->data);
	}
	cout <<"List Size : "<<list->size<<endl;
}
