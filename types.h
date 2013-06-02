#ifndef _TYPES_H_
#define _TYPES_H_

#define BUF_SIZE 100000
#define CODE_BUF 15

typedef struct _chTable
{
	char ch;
	int  frequency;
} chTable;


typedef struct _TreeNode TreeNode;
struct _TreeNode
{
	chTable   table;
	TreeNode *left;
	TreeNode *right;
};

typedef struct _Tree
{
	TreeNode* root;
	int size;
} Tree;

typedef struct _ListNode ListNode;
struct _ListNode
{
	TreeNode *data;
	ListNode *next;
};

typedef struct _List
{
	int size;
	ListNode* front;
	ListNode* back;
} List;

#endif
