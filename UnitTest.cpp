/*
 * Copyright@wh
 * Author:wh
 * Date:20210303
 * Description:红黑树功能测试
 * Resolution：1 层次遍历功能，注意输出颜色
 * 2 加入节点功能
 * 3 删除节点功能
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
	 * 功能：遍历检查红黑树
	 * 描述：层次遍历
	 * 注意要输出颜色
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
	cout << "输出结束" << endl;
}

void insertTest(vector<nodeValType> data)
{
	/*
	 * 功能：向红黑树中插入节点
	 */
	for(auto elem:data)
	{
		insert(head, elem);
	}
	return;
}
