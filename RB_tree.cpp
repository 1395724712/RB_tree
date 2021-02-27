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
	if (curGar == nullptr)
	{
		//����游�ڵ�Ϊ��,˵��֧�������Ǹ��ڵ���
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
	 * ���ܣ���curNode�ڵ�Ϊ֧������
	 */
	RB_TreeNode *newFar = curNode->left;
	if (newFar == nullptr) return;
	//����curNode�ڵ����µ�������
	curNode->left = newFar->right;
	newFar->right = curNode;
	curNode->left->par = curNode;
	
	
	// �����޸�curNode�ĸ��ڵ�
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
	{//����ڵ��Ǹ��ڵ�
		head = curNode;
		curNode->col = BLACK;
		return;
	}
	
	curNode->par = curPar;
	
	//�޸�ָ��ָ��
	if (curPar->val < v) curPar->left = curNode;
	else curPar->right = curNode;

	//������������
	insertFixup(root, curNode);
}

void insertFixup(RB_TreeNode * root, RB_TreeNode * cur)
{
	/*
	 * ����:�Լ����½ڵ�ĺ������������
	 * ����:���㷨ԭ���϶Ը��ڵ�Ϊ��ɫ�������Ϊ�����ִ���
	 * ����:1 ����ڵ�Ϊ��ɫ
	 * 2 ����ڵ�Ϊ��ɫ,��ǰ�ڵ�Ϊ�Һ���(�սڵ���Ϊ��ɫ)
	 * 3 ����ڵ�Ϊ��ɫ,��ǰ�ڵ�Ϊ����
	 * ԭ��:Ϊ�˱�֤��ɫ�ڵ����������Ҫ��
	 * ˼��:���ƻ���������ʵĺ�ɫ�ڵ㾡������,ֱ����Ϊ���ڵ�ĺ�ɫ
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
				//case 1 ����ڵ�Ϊ��ɫ
				//����ʽΪ:���ڵ������ڵ���ĺ�ɫ,�游�ڵ�ĺ�ɫ,���游�ڵ�Ϊ��ǰ�ڵ�,��ʼ��һ�δ���
				//�ᵼ�¸��ڵ�Ϊ������,��ʱ���ڵ�Ϊ��ɫ,�����ڵ㲢δ�����仯
				Far->col = BLACK;
				Uncle->col = BLACK;
				Gar->col = RED;
				cur = Gar;
			}
			else if (cur == Far->right && (Uncle == nullptr || Uncle->col == BLACK))
			{
				//case 2 ����ڵ�Ϊ��ɫ,�ҵ�ǰ�ڵ�Ϊ�丸�ڵ���Һ���
				//����ʽ: �Ը��ڵ�Ϊ�µĵ�ǰ�ڵ�,���µĵ�ǰ�ڵ�����
				//���ᵼ������,���ڵ�δ�����仯
				cur = Far;
				leftRotate(cur);
			}

			//case 3 ����ڵ�Ϊ��ɫ,��ǰ�ڵ�Ϊ�丸�ڵ������
			//����ʽ: ���ڵ�ĳɺ�ɫ,�游�ڵ�ĳɺ�ɫ,���游�ڵ�Ϊ֧������
			//�ػᵼ������,���ڵ�ض�Ϊ��ɫ,���ڵ㷢���仯,��Ϊ���ڵ�
			Far->col = BLACK;
			Gar->col = RED;
			rightRotate(Gar);

		}
		else
		{
			//������ڵ�ʹ���游�ڵ���Һ���
			//��������,���һ���,���ж����������һ���,��ת�������һ���
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

	//���������������,����Ը��ڵ�Ϊ��ɫ����(case 3),����ڵ���ܷ����仯,���ⲿ������תʱ���Ѿ�����޸�
	//����Ը��ڵ�Ϊ������(case 1),����ڵ㲢δ�����仯,�޸ĸ��ڵ�Ϊ��ɫ
	head->col = BLACK;
	
}

