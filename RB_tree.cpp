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
