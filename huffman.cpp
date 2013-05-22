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

void SortTable (List* list)
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
	
	SortTable(list);
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
			SortTable(list);
		}
		
		tree->root = root_node;	
	}
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
