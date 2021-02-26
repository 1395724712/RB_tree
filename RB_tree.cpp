#include "RB_tree.h"

void leftRotate(RB_TreeNode* curNode)
{
	/*
	 * ���ܣ���curNode�ڵ�Ϊ֧������
	 * ���裺1����curNode�ڵ������������������ֲ��curNode�ڵ����������
	 * 2���޸�curNode�ĸ��ڵ��ָ����curNode����ĸ��ڵ�ָ��
	 */

	RB_TreeNode *newRoot = curNode->right;
	if (newRoot == nullptr) return;
	//����curNode�ڵ����µ�������
	curNode->right = newRoot->left;
	newRoot->left = curNode;
	curNode->right->par = curNode;

	//�����޸�curNode�ĸ��ڵ�
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
	 * ���ܣ���curNode�ڵ�Ϊ֧������
	 */
	RB_TreeNode *newRoot = curNode->left;
	if (newRoot == nullptr) return;
	//����curNode�ڵ����µ�������
	curNode->left = newRoot->right;
	newRoot->right = curNode;
	curNode->left->par = curNode;
	
	
	// �����޸�curNode�ĸ��ڵ�
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
	 * ����:�ں�����в���ֵΪv�Ľڵ�
	 * ����:1 �����½ڵ�,���ҵ�����λ��
	 * 2 �޸�ָ��ָ��
	 * 3 ������������
	 */
	
	//�����½ڵ�
	RB_TreeNode* curNode = new RB_TreeNode(v);
	curNode->col = RED;
	RB_TreeNode* curPar = root;
	RB_TreeNode* cur = root;
	
	//Ѱ�Ҳ���λ��
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
	
	//�޸�ָ��ָ��
	if (curPar->val < v) curPar->left = curNode;
	else curPar->right = curNode;

	//������������
	insertFixup(root, curNode);
}
