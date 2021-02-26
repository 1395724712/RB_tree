#include "RB_tree.h"

void leftRotate(RB_TreeNode* curNode)
{
	/*
	 * 功能：以curNode节点为支点左旋
	 * 步骤：1、将curNode节点的右子树的左子树移植到curNode节点的右子树上
	 * 2、修改curNode的父节点的指向，与curNode自身的父节点指针
	 */

	RB_TreeNode *newRoot = curNode->right;
	if (newRoot == nullptr) return;
	//首先curNode节点获得新的右子树
	curNode->right = newRoot->left;
	newRoot->left = curNode;
	curNode->right->par = curNode;

	//接着修改curNode的父节点
	RB_TreeNode* curGar = curNode->par;
	newRoot->par = curGar;
	curNode->par = newRoot;
	if (curGar == nullptr) return;
	if(curGar->right==curNode)
	{ curGar->right = newRoot; }
	else
	{ curGar->left = newRoot; }

}

void rightRotate(RB_TreeNode* curNode)
{
	/*
	 * 功能：以curNode节点为支点左旋
	 */
	RB_TreeNode *newRoot = curNode->left;
	if (newRoot == nullptr) return;
	//首先curNode节点获得新的左子树
	curNode->left = newRoot->right;
	newRoot->right = curNode;
	curNode->left->par = curNode;
	
	
	// 接着修改curNode的父节点
	RB_TreeNode* curGar = curNode->par;
	newRoot->par = curGar;
	curNode->par = newRoot;
	if (curGar == nullptr) return;
	if (curGar->right == curNode)
	{
		curGar->right = newRoot;
	}
	else
	{
		curGar->left = newRoot;
	}
}

void insert(RB_TreeNode * root, nodeValType v)
{
	/*
	 * 功能:在红黑树中插入值为v的节点
	 * 步骤:1 声明新节点,并找到插入位置
	 * 2 修改指针指向
	 * 3 运行修正函数
	 */
	
	//声明新节点
	RB_TreeNode* curNode = new RB_TreeNode(v);
	curNode->col = RED;
	RB_TreeNode* curPar = root;
	RB_TreeNode* cur = root;
	
	//寻找插入位置
	while(cur!=nullptr)
	{
		curPar = cur;
		if (cur->val > v) cur = cur->left;
		else cur = cur->right;
	}

	if(curPar==nullptr)
	{
		head.left = curNode;
		curNode->par = &head;
	}
	
	curNode->par = curPar;
	
	//修改指针指向
	if (curPar->val < v) curPar->left = curNode;
	else curPar->right = curNode;

	//运行修正函数
	insertFixup(root, curNode);
}
