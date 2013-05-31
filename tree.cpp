#include <string>
#include <iostream>
#include <assert.h>
#include "list.h"
#include "tree.h"

using namespace std;


Tree* createTree ()
{
	Tree* tree = new Tree;
	assert (tree);

	tree->root = createTreeNode();
	tree->size = 0;

	return tree;
}

TreeNode* createTreeNode ()
{
	TreeNode* node = new TreeNode;
	assert (node);

	node->left = node->right = NULL;
	return node;
}

void _ProcDestroyTree (TreeNode* root)
{
	if (!root->left && !root->right)
		return;

	_ProcDestroyTree (root->left);
	_ProcDestroyTree (root->right);

	delete root;
}

void destroyTree (Tree* tree)
{
	assert (tree);

	_ProcDestroyTree (tree->root);
	delete tree;
	tree=NULL;
}
