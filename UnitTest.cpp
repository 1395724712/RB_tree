/*
 * Copyright@wh
 * Author:wh
 * Date:20210303
 * Description:��������ܲ���
 * Resolution��1 ��α������ܣ�ע�������ɫ
 * 2 ����ڵ㹦��
 * 3 ɾ���ڵ㹦��
 */

#include <iostream>
#include<stdlib.h>
#include"RB_tree.h"
#include<vector>
#include<queue>

using namespace std;


void traversal(RB_TreeNode *root);
void insertTest( vector<nodeValType> data);


int main()
{
	
	vector<int> data = { 2,12,54,23,1,7,5,0 };
	insertTest(data);
	traversal(head);

	cout << endl;
	
	erase(head, 12);
	traversal(head);

	cout << endl;
	
	erase(head, 2);
	traversal(head);
	
	system("pause");
	return 0;
}

void traversal(RB_TreeNode *root)
{
	/*
	 * ���ܣ������������
	 * ��������α���
	 * ע��Ҫ�����ɫ
	 */
	queue<RB_TreeNode*> que;
	if (root != nullptr)
	{
		que.push(root);
		int len = que.size();
		while (!que.empty())
		{
			len = que.size();
			for (int i = 0; i < len; i++)
			{
				RB_TreeNode* cur = que.front();
				que.pop();
				cout << cur->val;
				if (cur->col == BLACK)
				{
					cout << "B" << "\t";
				}
				else cout << "R" << "\t";
				if (cur->left != nullptr) que.push(cur->left);
				if (cur->right != nullptr) que.push(cur->right);
			}
			cout << endl;
		}
	}
	cout << "�������" << endl;
}

void insertTest(vector<nodeValType> data)
{
	/*
	 * ���ܣ��������в���ڵ�
	 */
	for(auto elem:data)
	{
		insert(head, elem);
	}
	return;
}
