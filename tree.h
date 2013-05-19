#ifndef _TREE_H_
#define _TREE_H

struct chTable;

struct TreeNode
{
	chTable data;
	TreeNode* left;
	TreeNode* right;
};

struct Tree
{
	TreeNode* root;
	int size;
};


Tree* createTree ();
void destroyTree (Tree* tree);

TreeNode* getNode (Tree* tree);
TreeNode* getLeft (Tree* tree);
TreeNode* getRight (Tree* tree);

#endif

