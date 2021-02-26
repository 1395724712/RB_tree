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
