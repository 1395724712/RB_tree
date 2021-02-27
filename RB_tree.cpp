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
	if (curGar == nullptr)
	{
		//如果祖父节点为空,说明支点现在是根节点了
		head = newRoot;
		return ;
	}
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
	RB_TreeNode *newFar = curNode->left;
	if (newFar == nullptr) return;
	//首先curNode节点获得新的左子树
	curNode->left = newFar->right;
	newFar->right = curNode;
	curNode->left->par = curNode;
	
	
	// 接着修改curNode的父节点
	RB_TreeNode* curGar = curNode->par;
	newFar->par = curGar;
	curNode->par = newFar;
	if (curGar == nullptr)
	{
		head = newFar;
		return;
	}
	if (curGar->right == curNode)
	{
		curGar->right = newFar;
	}
	else
	{
		curGar->left = newFar;
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
	{//插入节点是根节点
		head = curNode;
		curNode->col = BLACK;
		return;
	}
	
	curNode->par = curPar;
	
	//修改指针指向
	if (curPar->val < v) curPar->left = curNode;
	else curPar->right = curNode;

	//运行修正函数
	insertFixup(root, curNode);
}

void insertFixup(RB_TreeNode * root, RB_TreeNode * cur)
{
	/*
	 * 功能:对加入新节点的红黑树进行修正
	 * 描述:从算法原理上对父节点为红色的情况分为了三种处理
	 * 步骤:1 叔叔节点为红色
	 * 2 叔叔节点为黑色,当前节点为右孩子(空节点视为黑色)
	 * 3 叔叔节点为黑色,当前节点为左孩子
	 * 原因:为了保证黑色节点的数量满足要求
	 * 思想:将破坏红黑树性质的红色节点尽量上移,直到变为根节点改黑色
	 */
	while(cur->par!=nullptr&&cur->par->col == RED)
	{
		RB_TreeNode* Uncle;
		RB_TreeNode* Far = cur->par;
		RB_TreeNode* Gar = cur->par->par;
		
		if(Far==Gar->left)
		{
			Uncle = Gar->right;
			if (Uncle != nullptr&&Uncle->col == RED)
			{
				//case 1 叔叔节点为红色
				//处理方式为:父节点和叔叔节点均改黑色,祖父节点改红色,以祖父节点为当前节点,开始下一次处理
				//会导致父节点为空跳出,此时根节点为红色,但根节点并未发生变化
				Far->col = BLACK;
				Uncle->col = BLACK;
				Gar->col = RED;
				cur = Gar;
			}
			else if (cur == Far->right && (Uncle == nullptr || Uncle->col == BLACK))
			{
				//case 2 叔叔节点为黑色,且当前节点为其父节点的右孩子
				//处理方式: 以父节点为新的当前节点,以新的当前节点左旋
				//不会导致跳出,根节点未发生变化
				cur = Far;
				leftRotate(cur);
			}

			//case 3 叔叔节点为黑色,当前节点为其父节点的左孩子
			//处理方式: 父节点改成黑色,祖父节点改成红色,以祖父节点为支点右旋
			//必会导致跳出,父节点必定为黑色,根节点发生变化,变为父节点
			Far->col = BLACK;
			Gar->col = RED;
			rightRotate(Gar);

		}
		else
		{
			//如果父节点使其祖父节点的右孩子
			//上述内容,左右互换,即判断条件里左右互换,旋转方向左右互换
			Uncle = Gar->left;
			if(Uncle!=nullptr&&Uncle->col==RED)
			{
				Far->col = BLACK;
				Uncle->col = BLACK;
				Gar->col = RED;
				cur = Gar;
			}
			else if (cur==Far->left&&(Uncle==nullptr||Uncle->col==RED))
			{
				cur = Far;
				rightRotate(cur);
			}
			Far->col = BLACK;
			Gar->col = RED;
			leftRotate(Gar);
			
		}
		
	}

	//根据以上种种情况,如果以父节点为黑色跳出(case 3),则根节点可能发生变化,但这部分在旋转时就已经完成修改
	//如果以父节点为空跳出(case 1),则根节点并未发生变化,修改根节点为黑色
	head->col = BLACK;
	
}

