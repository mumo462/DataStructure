#pragma once
#include <iostream>
using namespace std;
#include <queue>
#include <assert.h>
#include <stack>
template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;


	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* str, int size)
	{
		int index = 0;
		_root = _BinaryTree(str, size, index);
	}
	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}
	BinaryTree<T>& operator=(BinaryTree<T> t)
	{
		swap(_root, t._root);
		return *this;
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void PrevOrder_NOR()
	{
		stack<BinaryTreeNode<T>*> s;
		s.push(_root);
		while (!s.empty())
		{
			BinaryTreeNode<T>* top = s.top();
			s.pop();
			cout << top->_data << " ";
			if (top->_right)
			{
				s.push(top->_right);
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
		cout << endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void InOrder_NOR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode<T>* top = s.top();
			s.pop();
			cout << top->_data << " ";
			if (top->_right)
				cur = top->_right;
		}
		cout << endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}
	void PostOrder_NOR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		BinaryTreeNode<T>* Prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			BinaryTreeNode<T>* top = s.top();
			if(top->_right==NULL||Prev==top->_right)
			{
				cout << top->_data << " ";
				Prev = s.top();
				s.pop();
			}
			else if (top->_right)
			{
				cur = top->_right;
			}
		}
		cout << endl;

	}
	void LevelOrder()
	{
		queue<BinaryTreeNode<T>*> q;
		if (_root == NULL)
			return;
		q.push(_root);
		while (!q.empty())
		{
			BinaryTreeNode<T>* temp = q.front();
			cout << temp->_data << " ";
			q.pop();
			if (temp->_left)
			{
				q.push(temp->_left);
			}
			if (temp->_right)
			{
				q.push(temp->_right);
			}
		}
		cout << endl;
	}
	int Size()
	{
		return _Size(_root);
	}
	int Depth()
	{
		return _Depth(_root);
	}
	BinaryTreeNode<T>* Find(const T& x)
	{
		return _Find(_root, x);
	}
	~BinaryTree()
	{
		_Destory(_root);
	}
	int GetLeafNum()
	{
		return _GetLeafNum(_root);
	}
private:
	int _GetLeafNum(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL&&root->_right == NULL)
			return 1;
		return _GetLeafNum(root->_left)+ _GetLeafNum(root->_right);
	}
	void _Destory(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->_left == NULL&&root->_right == NULL)
		{
			delete root;
			root = NULL;
		}
		if(root!=NULL)
			_Destory(root->_left);
		if (root != NULL)
			_Destory(root->_right);
		delete root;

	}
	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (root != NULL)
		{
			BinaryTreeNode<T>* temp=new BinaryTreeNode<T>(root->_data);
			temp->_left = _Copy(root->_left);
			temp->_right = _Copy(root->_right);
			return temp;
		}
		return NULL;
	}
	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* root,const T& x)
	{
		if (root != NULL)
		{
			if (root->_data == x)
			{
				return root;
			}
			BinaryTreeNode<T>* btn = _Find(root->_left,x);
			if (btn == NULL)
			{
				return _Find(root->_right,x);
			}
			return btn;
		}
		return NULL;
	}
	int _Depth(BinaryTreeNode<T>* root)
	{
		int Depth = 0;
		if (root == NULL)
		{
			return 0;
		}
		int left=_Depth(root->_left);
		int right = _Depth(root->_right);
		return left>right?left+1:right+1;
	}
	int  _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}
	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	BinaryTreeNode<T>* _BinaryTree(const T* str, int size, int& index)
	{
		assert(str);
		BinaryTreeNode<T>* root = NULL;
		while (index < size&&str[index] != '#')
		{
			root = new BinaryTreeNode<T>(str[index]);
			root->_left = _BinaryTree(str,size,++index);
			root->_right = _BinaryTree(str, size, ++index);
		}
		return root;
	}
	BinaryTreeNode<T>* _root;
};