#pragma once

#include "BinaryTreeParent.h"
#include "BinaryTree.h"
#include <queue>
/////////////////////////////////////////////////////////////////////
//判断一个二叉树是不是完全二叉树
//1.利用每个节点的兄弟节点来判断是否是完全二叉树
template <class T>
bool _isCompleteBT(BinaryTreeNode<T>* root, BinaryTreeNode<T>*& prev,bool& judge)
{
	typedef BinaryTreeNode<T> Node;
	if (root == NULL)
	{
		return true;
	}
	if (root->_left == NULL&&root->_right)
	{
		return false;
	}
	else if (prev&&root->_left&&root->_right)
	{
		BinaryTreeNode<T>* uncle = NULL;
		if (prev->_left == root)
		{
			uncle = prev->_right;
			if (uncle == NULL)
				return false;
		}
	}
	else if (prev&&root->_left&&root->_right == NULL)
	{
		if (judge == false)
		{
			judge = true;
			BinaryTreeNode<T>* uncle = NULL;
			if (prev->_left == root)
			{
				uncle = prev->_right;
				if (uncle == NULL)
					return false;
				if (uncle && (uncle->_left || uncle->_right))
				{
					return false;
				}
			}
		}
		else
			return false;
	}	
	prev = root;
	return _isCompleteBT(root->_left,prev,judge) && _isCompleteBT(root->_right, prev,judge);
}
template <class T>
bool isCompleteBT(BinaryTreeNode<T>* root)
{
	BinaryTreeNode<T>* prev = NULL;
	bool judge = false;
	//return _isCompleteBT(root,prev,judge);
	return _IsCompleteBT(root,judge);
}
///////////////////////////////////////////////////////////////////
//2利用高度差判断这颗二叉树的左树，右树
template <class T>
int height(BinaryTreeNode<T>* root)
{
	if (root == NULL)
		return 0;
	int Lhigh = height(root->_left) + 1;
	int Rhigh = height(root->_right) + 1;
	return Lhigh > Rhigh ? Lhigh : Rhigh;
}
template <class T>
bool _IsCompleteBT(BinaryTreeNode<T>* root,bool& judge)
{
	if (root == NULL)
		return true;
	int Lheight = height(root->_left);
	int Rheight = height(root->_right);
	if (Lheight == Rheight)
	{
		return _IsCompleteBT(root->_left,judge)&& _IsCompleteBT(root->_right,judge);
	}
	else if (Lheight == Rheight + 1)
	{
		if (judge == true)
		{
			return false;
		}
		judge = true;
		return _IsCompleteBT(root->_left, judge) && _IsCompleteBT(root->_right, judge);
	}
	else
		return false;
}
//3利用队列层序遍历这棵树
template <class T>
bool ComplateTree(BinaryTreeNode<T>* root)
{
	queue<BinaryTreeNode<T>*> q;
	int flag = 0;
	if (root == NULL)
		return 1;
	q.push(root);
	while (!q.empty())
	{
		BinaryTreeNode<T>* temp=q.front();
		q.pop();
		if (temp->_left && !flag)
		{
			q.push(temp->_left);
		}
		else if (temp->_left)
		{
			return 0;
		}
		else
		{
			flag = 1;
		}
		if (temp->_right && !flag)
		{
			q.push(temp->_right);
		}
		else if (temp->_right)
		{
			return 0;
		}
		
	}
	return 1;
}
/////////////////////////////////////////////////////////////////////
//求两个节点的最近公共祖先
//1利用2个栈来存2个结点的线路，然后出栈到两个节点值相同，则是最近公共祖先
//template <class T>
//void _PublicGrandpa(BinaryTreeNode<T>* root, BinaryTreeNode<T>* node, stack<BinaryTreeNode<T>*>& s,bool& is)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	if (is == false)
//		s.push(root);
//	else
//		return;
//	if (root->_data == node->_data)
//	{
//		is = true;
//		return;
//	}
//	_PublicGrandpa(root->_left, node, s, is);
//	_PublicGrandpa(root->_right, node, s, is);
//	if (is == false)
//	{
//		s.pop();
//	}
//	
//}
//template <class T>
//BinaryTreeNode<T>* PublicGrandpa( BinaryTreeNode<T>* _root,BinaryTreeNode<T>* node1, BinaryTreeNode<T>* node2)
//{
//	if (node1 == NULL || node2 == NULL)
//	{
//		return NULL;
//	}
//	stack<BinaryTreeNode<T>*> s1;
//	stack<BinaryTreeNode<T>*> s2;
//	bool is = false;
//	_PublicGrandpa(_root,node1,s1,is);
//	is = false;
//	_PublicGrandpa(_root,node2,s2,is);
//	if (s1.size() > s2.size())
//	{
//		swap(s1,s2);
//	}
//	while (s2.size() > s1.size())
//	{
//		s2.pop();
//	}
//	while (s1.top() != s2.top())
//	{
//		s1.pop();
//		s2.pop();
//	}
//	return s1.top();
//}
/////////////////////////////////////////////////////////////////////
//2利用递归来实现
template <class T>
BinaryTreeNode<T>* IsSameGrandPa(BinaryTreeNode<T>* root, BinaryTreeNode<T>* node1, BinaryTreeNode<T>* node2)
{
	if (node1 == NULL || node2 == NULL)
	{
		return NULL;
	}
	if (root == NULL || root == node1 || root == node2)
		return root;
	BinaryTreeNode<T>* left = IsSameGrandPa(root->_left, node1, node2);
	BinaryTreeNode<T>* right = IsSameGrandPa(root->_right, node1, node2);
	if (left&&right)
		return root;
	return left ? left : right;
}

//判断一颗二叉树是否是平衡二叉树
template <class T>
bool IsAVLTree(BinaryTreeNode<T>* root)
{
	if (root == NULL)
		return true;
	if (abs(_height(root->_left) - _height(root->_right)) > 1)
	{
		return false;
	}
	if ((root->_left&&(root->_data < root->_left->_data))||
		(root->_right&&(root->_data > root->_right->_data)))

	{
		return false;
	}
	return IsAVLTree(root->_left) && IsAVLTree(root->_right);
}
//////////////////////////////////////////////////////////
//求二叉树中最远两个结点的距离
//1 O(N^2)
 template <class T>
 int FindFarthest(BinaryTreeNode<T>* root)
 {
	 if (root == NULL)
		 return 0;
	 int max = height(root->_left)+height(root->_right)+1;
	 int left = FindFarthest(root->_left);
	 int right = FindFarthest(root->_right);
	 int temp = left > right ? left : right;
	 return max > temp ? max : temp;
 }
 ///////////////////////////////////////////////////////
 //2. O(N)
 template <class T>
 int fFindFarthest(BinaryTreeNode<T>* root)
 {
	 int* record = new int(0);
	 return _FindFarthest(root,record);
 }
 template <class T>
 int _FindFarthest(BinaryTreeNode<T>* root,int*& record)
 {
	 if (root == NULL)
	 {
		 record[0] = 0;
		 return 0;
	 }
	 int left = _FindFarthest(root->_left,record);
	 int maxleft = record[0];
	 int right = _FindFarthest(root->_right,record);
	 int maxright = record[0];
	 int max = maxleft+maxright+1;
	 record[0] = (maxleft > maxright ? maxleft : maxright)+1;
	 int temp = (left > right ? left : right);
	 return max > temp ? max : temp;
 }
 //////////////////////////////////////////////////////////////
 //由前序遍历和中序遍历重建二叉树
 template <class T>
 BinaryTreeNode<T>* ReCreate(vector<int> PrevOrder, vector<int> InOrder)
 {
	 BinaryTreeNode<T>* root = NULL;
	 return  _ReCreate(root, PrevOrder, InOrder);
	
 }
template <class T>
BinaryTreeNode<T>* _ReCreate(BinaryTreeNode<T>*& root, vector<int> PrevOrder, vector<int> InOrder)
{
	if (!PrevOrder.size() || !InOrder.size())
	{
		return NULL;
	}
	vector<int> PrevLeft, PrevRight, InLeft, InRight;
	int i = 0;
	while (PrevOrder[0] != InOrder[i])
	{
		i++;
	}
	for (int j = 1; j <=i; j++)
	{
		PrevLeft.push_back(PrevOrder[j]);
		InLeft.push_back(InOrder[j-1]);
	}
	for (int j = i + 1; j < PrevOrder.size(); j++)
	{
		PrevRight.push_back(PrevOrder[j]);
		InRight.push_back(InOrder[j]);
	}
	root = new BinaryTreeNode<T>(PrevOrder[0]);
	root->_left = _ReCreate(root->_left,PrevLeft,InLeft);
	root->_right = _ReCreate(root->_right,PrevRight,InRight);
	return root;
}
//////////////////////////////////////////////////////////////////
//将二叉搜索树转换成双向链表，不能创建新结点
template <class T>
BinaryTreeNode<T>* TreeToList(BinaryTreeNode<T>* root)
{
	BinaryTreeNode<T>* prev = NULL;
	_TreeToList(root,prev);
	while (root->_left != NULL)
	{
		root = root->_left;
	}
	return root;
	 
}
template <class T>
void _TreeToList(BinaryTreeNode<T>* root,BinaryTreeNode<T>*& prev)
{
	if (root == NULL)
	{
		return;
	}
	_TreeToList(root->_left, prev);
	root->_left = prev;
	if (prev)
	{
		prev->_right = root;
	}
	prev = root;
	_TreeToList(root->_right, prev);
}