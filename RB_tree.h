#pragma once

typedef int nodeValType;
enum COL{RED,BLACK};
struct RB_TreeNode
{
	nodeValType val;
	RB_TreeNode *left;
	RB_TreeNode *right;
	RB_TreeNode *par=nullptr;
	COL col;
	RB_TreeNode():val(0),left(nullptr),right(nullptr){}
	RB_TreeNode(nodeValType x):val(x),left(nullptr),right(nullptr){}
	RB_TreeNode(nodeValType x,RB_TreeNode *l,RB_TreeNode *r):val(x),left(l),right(r){}
};

RB_TreeNode* head(0);//����ָ����ڵ��ָ��


//����
void leftRotate(RB_TreeNode* curNode);

//����
void rightRotate(RB_TreeNode* curNode);

//����
void insert(RB_TreeNode* root, nodeValType v);

//����������
void insertFixup(RB_TreeNode* root, RB_TreeNode *cur);

//ɾ��
void earse(RB_TreeNode* root, nodeValType v);

//ɾ���������
void earseFixup(RB_TreeNode* root, RB_TreeNode* child,RB_TreeNode *father);

