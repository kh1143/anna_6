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

void destroyTree (Tree* tree)
{
	assert (tree);

	delete tree;
}

TreeNode* getTreeNode (Tree* tree)
{
	assert (tree);
	return tree->root;
}

TreeNode* getTreeLeft (Tree* tree)
{
	assert (tree);
	return tree->root->left;
}

TreeNode* getTreeRight (Tree* tree)
{
	assert (tree);
	return tree->root->right;
}

