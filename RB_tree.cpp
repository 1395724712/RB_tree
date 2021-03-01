#include "RB_tree.h"

#include <cstdlib>

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

void erase(RB_TreeNode* root, nodeValType v)
{
	/*
	 * 功能：删除值为v的节点
	 * 描述：过程实在是复杂，没怎么看明白，我代码都快背下来了，还没看明白原理
	 * 过程：1 查找值为v的节点
	 * 2 寻找替换节点：两种情况，删除节点有两个非空子节点，删除节点有一个或没有非空子节点
	 * 3 替换，修改指针指向
	 * 4 保存取代指针的指向作为依据
	 * 5 获得父节点指针和子节点指针传入进行修正
	 */

	//1 寻找被删除节点
	RB_TreeNode* delNode = root;
	while(delNode!=nullptr&&delNode->val!=v)
	{
		if (delNode->val > v) delNode = delNode->left;
		else delNode = delNode->right;
	}

	if(delNode==nullptr)
	{//节点不存在
		return;
	}

	RB_TreeNode* repNode;
	RB_TreeNode* father;
	COL color;
	RB_TreeNode* child;
	
	//case 1 删除节点有一个或没有非空节点
	//在这种情况下，子节点为替换节点
	//颜色为删除节点的颜色
	//父节点为删除节点的父节点
	if(delNode->left==nullptr||delNode->right==nullptr)
	{
		//2 寻找替换节点
		if (delNode->left != nullptr) repNode = delNode->left;
		else repNode = delNode->right;

		//3 保存纠正信息
		color = delNode->col;
		father = delNode->par;
		child = repNode;
		
		//开始替换
		if(father == nullptr)
		{
			//如果被删除节点是根节点
			head = repNode;
		}
		else
		{
			if (delNode == father->left) father->left = repNode;
			else father->right = repNode;
		}

		if(repNode!=nullptr) repNode->par = father;//注意替代节点为空的情况

		//4 修正
		if (color == BLACK) earseFixup(root, child, father);

		free(delNode);
	}
	else
	{
		// case 2 被删除节点有两个非空子节点
		//子节点为替换节点的右孩子
		//父节点为替换节点的父节点
		//颜色为替换节点的颜色
		//步骤：1 寻找替换节点
		// 2 保存修正信息
		//3 替换
		//4 运行修正

		// 1 寻找替换节点
		repNode = delNode->right;
		while (repNode->left != nullptr)
			repNode = repNode->left;

		//2 保存修正信息
		father = repNode->par;
		color = repNode->col;
		child = repNode->right;

		// 3 替换
		//首先修改child节点的指向
		if(father!=delNode)
		{
			//替换节点不是删除节点的子节点，修改child节点指向
			if (child != nullptr) child->par = father;
			father->left = child;
		}
		else
		{//替换节点是删除节点的子节点，修改father指针
			father = repNode;
		}

		//修改替换节点
		if(delNode->par==nullptr)
		{
			head = repNode;
			repNode->par = nullptr;
		}
		else
		{
			repNode->par = delNode->par;
			if (delNode == delNode->par->left) delNode->par->left = repNode;
			else delNode->par->right = repNode;
		}

		//修改替换节点信息
		repNode->col = delNode->col;
		repNode->left = delNode->left;
		delNode->left->par = repNode;
		if(delNode->right!=repNode)
		{//这一步之所以不和前面的合并是为了提高可读性
			repNode->right = delNode->right;
			delNode->right->par = repNode;
		}

		if(color==BLACK)
		{
			eraseFixup(child);
		}
		free(delNode);
	}
}

void eraseFixup(RB_TreeNode * child)
{
	/*
	 * 功能：执行删除后的修正功能
	 * 描述：根据当前节点和其兄弟节点的颜色来判断执行何种操作
	 * *我已经快要放弃去理解为什么了*
	 */

	while((child==nullptr||child->col == BLACK) &&head!=child)
	{
		RB_TreeNode* brother;
		if(child == child->par->left)
		{
			//如果当前节点为黑色，则比存在兄弟节点
			//否则违反性质五
			brother = child->par->right;

			if(brother->col == RED)
			{
				/*
				 * case 1:如果兄弟节点是红色
				 * 操作，改兄弟节点为黑色，父节点为红色，左旋，进入case 2
				 */
				brother->col = BLACK;
				child->par->col = RED;
				leftRotate(child->par);
			}
			else if((brother->left==nullptr||brother->left->col == BLACK)
				&&(brother->right==nullptr||brother->right->col == BLACK))
			 {
				 /*
				  * case 2: 兄弟节点为黑色，且兄弟节点的子节点均为黑色
				  * 操作：兄弟节点改红色，以父节点为新的当前节点
				  */

				brother->col = RED;
				child = child->par;
			 }
			else if((brother->left!=nullptr&&brother->left->col == RED)
				&&(brother->right==nullptr||brother->right->col==BLACK))
			{
				/*
				 * case 3:兄弟节点的左节点为红色，右节点为黑色
				 * 操作：交换兄弟节点和兄弟左孩子节点的颜色，以兄弟节点为支点右旋
				 */
				brother->col = RED;
				brother->left->col = BLACK;
				rightRotate(brother);
			}
			else
			{
				/*
				 * case 4:兄弟节点的右孩子为红色
				 * 操作：理解不了，放弃了
				 * 兄弟节点改成父节点的颜色
				 * 父节点改黑色
				 * 兄弟节点的右节点改黑色
				 * 以父节点为支点左旋
				 * 以根节点为当前节点
				 * 跳出循环
				 */
				brother->col = child->par->col;
				child->par->col = BLACK;
				brother->right->col = BLACK;
				leftRotate(child->par);
				child = head;
			}
		}
		else
		{
			//当前节点是其根节点的右孩子
			//左右互换
			brother = child->par->left;
			if(brother->col == RED)
			{
				//case 1 兄弟节点是红色
				//兄弟节点改黑色
				//父节点改红色
				//右旋
				brother->col = BLACK;
				child->par->col = RED;
				rightRotate(child->par);
			}
			else if((brother->left==nullptr||brother->left->col==BLACK)
				&&(brother->right==nullptr||brother->right->col==BLACK))
			{
				//case 2 兄弟节点黑色，左右孩子节点也均为黑色
				//改兄弟节点为红，以父节点为当前节点
				brother->col = RED;
				child = child->par;
			}
			else if((brother->right!=nullptr||brother->right->col == RED)&&(brother->left==nullptr||brother->left->col == BLACK))
			{
				//todo:我怎么感觉应该是右孩子为红色，左孩子为黑色，然后左旋
				//case 3 兄弟节点为黑色，左孩子为红色，右孩子为黑色
				//交换兄弟节点和其左孩子的颜色，以兄弟节点为支点左旋
				brother->col = RED;
				brother->right->col = BLACK;
				leftRotate(brother);
			}
			else
			{
				//case 4 兄弟节点为黑色，左孩子为红色
				brother->col = child->par->col;
				child->par->col = BLACK;
				brother->left->col = BLACK;
				rightRotate(child->par);
				child = head;
			}
		}
	}

	if (child != nullptr) child->col = BLACK;//只要节点存在就改为黑色
}

