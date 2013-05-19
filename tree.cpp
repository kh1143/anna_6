#include <string>
#include <iostream>
#include <assert.h>
#include "list.h"

using namespace std;


Tree* createTree ()
{
	Tree* tree = new Tree;
	assert (tree);

	tree->root = new TreeNode;
	assert (tree->node);
	
	tree->root->left = tree->root->right = NULL;
	tree->size = 0;
}

void destroyTree (Tree* tree)
{
	assert (tree);

	delete tree;
}

TreeNode* getNode (Tree* tree)
{
	assert (tree);
	return tree->root;
}

TreeNode* getLeft (Tree* tree)
{
	assert (tree);
	return getNode (tree->root->left);
}

TreeNode* getRight (Tree* tree)
{
	assert (tree);
	return getNode (tree->root->right);
}

