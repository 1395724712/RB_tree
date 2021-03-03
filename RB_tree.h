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

extern RB_TreeNode* head;//这是指向根节点的指针


//左旋
void leftRotate(RB_TreeNode* curNode);

//右旋
void rightRotate(RB_TreeNode* curNode);

//插入
void insert(RB_TreeNode* root, nodeValType v);

//插入后的修正
void insertFixup(RB_TreeNode* root, RB_TreeNode *cur);

//删除
void erase(RB_TreeNode* root, nodeValType v);

//删除后的修正
void eraseFixup(RB_TreeNode* child);

