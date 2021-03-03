#include "RB_tree.h"

#include <cstdlib>

RB_TreeNode* head = nullptr;
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
	if(curNode->right!=nullptr)curNode->right->par = curNode;

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
	if(curNode->left!=nullptr) curNode->left->par = curNode;
	
	
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
	if (curPar->val < v) curPar->right = curNode;
	else curPar->left = curNode;

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
			else
			{
				//case 3 ����ڵ�Ϊ��ɫ,��ǰ�ڵ�Ϊ�丸�ڵ������
				//����ʽ: ���ڵ�ĳɺ�ɫ,�游�ڵ�ĳɺ�ɫ,���游�ڵ�Ϊ֧������
				//�ػᵼ������,���ڵ�ض�Ϊ��ɫ,���ڵ㷢���仯,��Ϊ���ڵ�
				Far->col = BLACK;
				Gar->col = RED;
				rightRotate(Gar);
			}

			

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
			else
			{
				Far->col = BLACK;
				Gar->col = RED;
				leftRotate(Gar);
			}
		}
		
	}

	//���������������,����Ը��ڵ�Ϊ��ɫ����(case 3),����ڵ���ܷ����仯,���ⲿ������תʱ���Ѿ�����޸�
	//����Ը��ڵ�Ϊ������(case 1),����ڵ㲢δ�����仯,�޸ĸ��ڵ�Ϊ��ɫ
	head->col = BLACK;
	
}

void erase(RB_TreeNode* root, nodeValType v)
{
	/*
	 * ���ܣ�ɾ��ֵΪv�Ľڵ�
	 * ����������ʵ���Ǹ��ӣ�û��ô�����ף��Ҵ��붼�챳�����ˣ���û������ԭ��
	 * ���̣�1 ����ֵΪv�Ľڵ�
	 * 2 Ѱ���滻�ڵ㣺���������ɾ���ڵ��������ǿ��ӽڵ㣬ɾ���ڵ���һ����û�зǿ��ӽڵ�
	 * 3 �滻���޸�ָ��ָ��
	 * 4 ����ȡ��ָ���ָ����Ϊ����
	 * 5 ��ø��ڵ�ָ����ӽڵ�ָ�봫���������
	 */

	//1 Ѱ�ұ�ɾ���ڵ�
	RB_TreeNode* delNode = root;
	while(delNode!=nullptr&&delNode->val!=v)
	{
		if (delNode->val > v) delNode = delNode->left;
		else delNode = delNode->right;
	}

	if(delNode==nullptr)
	{//�ڵ㲻����
		return;
	}

	RB_TreeNode* repNode;
	RB_TreeNode* father;
	COL color;
	RB_TreeNode* child;
	
	//case 1 ɾ���ڵ���һ����û�зǿսڵ�
	//����������£��ӽڵ�Ϊ�滻�ڵ�
	//��ɫΪɾ���ڵ����ɫ
	//���ڵ�Ϊɾ���ڵ�ĸ��ڵ�
	if(delNode->left==nullptr||delNode->right==nullptr)
	{
		//2 Ѱ���滻�ڵ�
		if (delNode->left != nullptr) repNode = delNode->left;
		else repNode = delNode->right;

		//3 ���������Ϣ
		color = delNode->col;
		father = delNode->par;
		child = repNode;
		
		//��ʼ�滻
		if(father == nullptr)
		{
			//�����ɾ���ڵ��Ǹ��ڵ�
			head = repNode;
		}
		else
		{
			if (delNode == father->left) father->left = repNode;
			else father->right = repNode;
		}

		if(repNode!=nullptr) repNode->par = father;//ע������ڵ�Ϊ�յ����

		//4 ����
		if (color == BLACK) eraseFixup(child);

		free(delNode);
	}
	else
	{
		// case 2 ��ɾ���ڵ��������ǿ��ӽڵ�
		//�ӽڵ�Ϊ�滻�ڵ���Һ���
		//���ڵ�Ϊ�滻�ڵ�ĸ��ڵ�
		//��ɫΪ�滻�ڵ����ɫ
		//���裺1 Ѱ���滻�ڵ�
		// 2 ����������Ϣ
		//3 �滻
		//4 ��������

		// 1 Ѱ���滻�ڵ�
		repNode = delNode->right;
		while (repNode->left != nullptr)
			repNode = repNode->left;

		//2 ����������Ϣ
		father = repNode->par;
		color = repNode->col;
		child = repNode->right;

		// 3 �滻
		//�����޸�child�ڵ��ָ��
		if(father!=delNode)
		{
			//�滻�ڵ㲻��ɾ���ڵ���ӽڵ㣬�޸�child�ڵ�ָ��
			if (child != nullptr) child->par = father;
			father->left = child;
		}
		else
		{//�滻�ڵ���ɾ���ڵ���ӽڵ㣬�޸�fatherָ��
			father = repNode;
		}

		//�޸��滻�ڵ�
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

		//�޸��滻�ڵ���Ϣ
		repNode->col = delNode->col;
		repNode->left = delNode->left;
		delNode->left->par = repNode;
		if(delNode->right!=repNode)
		{//��һ��֮���Բ���ǰ��ĺϲ���Ϊ����߿ɶ���
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
	 * ���ܣ�ִ��ɾ�������������
	 * ���������ݵ�ǰ�ڵ�����ֵܽڵ����ɫ���ж�ִ�к��ֲ���
	 * *���Ѿ���Ҫ����ȥ���Ϊʲô��*
	 */

	while((child==nullptr||child->col == BLACK) &&head!=child)
	{
		RB_TreeNode* brother;
		if(child == child->par->left)
		{
			//�����ǰ�ڵ�Ϊ��ɫ����ȴ����ֵܽڵ�
			//����Υ��������
			brother = child->par->right;

			if(brother->col == RED)
			{
				/*
				 * case 1:����ֵܽڵ��Ǻ�ɫ
				 * ���������ֵܽڵ�Ϊ��ɫ�����ڵ�Ϊ��ɫ������������case 2
				 */
				brother->col = BLACK;
				child->par->col = RED;
				leftRotate(child->par);
			}
			else if((brother->left==nullptr||brother->left->col == BLACK)
				&&(brother->right==nullptr||brother->right->col == BLACK))
			 {
				 /*
				  * case 2: �ֵܽڵ�Ϊ��ɫ�����ֵܽڵ���ӽڵ��Ϊ��ɫ
				  * �������ֵܽڵ�ĺ�ɫ���Ը��ڵ�Ϊ�µĵ�ǰ�ڵ�
				  */

				brother->col = RED;
				child = child->par;
			 }
			else if((brother->left!=nullptr&&brother->left->col == RED)
				&&(brother->right==nullptr||brother->right->col==BLACK))
			{
				/*
				 * case 3:�ֵܽڵ����ڵ�Ϊ��ɫ���ҽڵ�Ϊ��ɫ
				 * �����������ֵܽڵ���ֵ����ӽڵ����ɫ�����ֵܽڵ�Ϊ֧������
				 */
				brother->col = RED;
				brother->left->col = BLACK;
				rightRotate(brother);
			}
			else
			{
				/*
				 * case 4:�ֵܽڵ���Һ���Ϊ��ɫ
				 * ��������ⲻ�ˣ�������
				 * �ֵܽڵ�ĳɸ��ڵ����ɫ
				 * ���ڵ�ĺ�ɫ
				 * �ֵܽڵ���ҽڵ�ĺ�ɫ
				 * �Ը��ڵ�Ϊ֧������
				 * �Ը��ڵ�Ϊ��ǰ�ڵ�
				 * ����ѭ��
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
			//��ǰ�ڵ�������ڵ���Һ���
			//���һ���
			brother = child->par->left;
			if(brother->col == RED)
			{
				//case 1 �ֵܽڵ��Ǻ�ɫ
				//�ֵܽڵ�ĺ�ɫ
				//���ڵ�ĺ�ɫ
				//����
				brother->col = BLACK;
				child->par->col = RED;
				rightRotate(child->par);
			}
			else if((brother->left==nullptr||brother->left->col==BLACK)
				&&(brother->right==nullptr||brother->right->col==BLACK))
			{
				//case 2 �ֵܽڵ��ɫ�����Һ��ӽڵ�Ҳ��Ϊ��ɫ
				//���ֵܽڵ�Ϊ�죬�Ը��ڵ�Ϊ��ǰ�ڵ�
				brother->col = RED;
				child = child->par;
			}
			else if((brother->right!=nullptr||brother->right->col == RED)&&(brother->left==nullptr||brother->left->col == BLACK))
			{
				//todo:����ô�о�Ӧ�����Һ���Ϊ��ɫ������Ϊ��ɫ��Ȼ������
				//case 3 �ֵܽڵ�Ϊ��ɫ������Ϊ��ɫ���Һ���Ϊ��ɫ
				//�����ֵܽڵ�������ӵ���ɫ�����ֵܽڵ�Ϊ֧������
				brother->col = RED;
				brother->right->col = BLACK;
				leftRotate(brother);
			}
			else
			{
				//case 4 �ֵܽڵ�Ϊ��ɫ������Ϊ��ɫ
				brother->col = child->par->col;
				child->par->col = BLACK;
				brother->left->col = BLACK;
				rightRotate(child->par);
				child = head;
			}
		}
	}

	if (child != nullptr) child->col = BLACK;//ֻҪ�ڵ���ھ͸�Ϊ��ɫ
}

