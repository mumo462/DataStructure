#pragma once
#include <iostream>
using namespace std;

enum PointTag
{
	THREAD,
	LINK,
};
template <class T>
struct BinaryTreeThreadNode
{
	T _data;
	BinaryTreeThreadNode<T>* _left;
	BinaryTreeThreadNode<T>* _right;
	PointTag _lefttag;
	PointTag _righttag;
	BinaryTreeThreadNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_lefttag(LINK)
		,_righttag(LINK)

	{}
};

template <class T>
class BinaryTreeThread
{
public:
	BinaryTreeThread(const T* str,int size)
	{
		int index = 0;
		_root=_CreateTree(str,size,index);
	}
	void InOrderThread()
	{
		BinaryTreeThreadNode<T>* prev=NULL;
		_InOrderThread(_root,prev);
	}
	void InOrder()
	{
		BinaryTreeThreadNode<T>* cur = _root;
		while (cur)
		{
			while (cur->_lefttag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_righttag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
	}
	void PrevOrderThread()
	{
		BinaryTreeThreadNode<T>* prev = NULL;
		_PrevOrderThread(_root, prev);
	}
	void PrevOrder()
	{
		BinaryTreeThreadNode<T>* cur = _root;
		while(cur)
		{
			while (cur->_lefttag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			cur = cur->_right;
			/*if(cur->_righttag == THREAD)
			{
				while(cur->_righttag == THREAD)
					cur = cur->_right;
			}
			else if(cur->_lefttag==LINK)
			{
				cur = cur->_left;
			}
			else 
			{
				cur = cur->_right;
			}*/
		}
	}
	void PostOrderThread()
	{
		BinaryTreeThreadNode<T>* prev = NULL;
		_PostOrderThread(_root,prev);
	}
	void PostOrder()
	{
		stack<T> s;
		BinaryTreeThreadNode<T>* cur = _root;
		while (cur)
		{
			while (cur->_righttag == LINK)
			{
				s.push(cur->_data);
				cur = cur->_right;
			}
			s.push(cur->_data);
			cur = cur->_left;
		}
		while(!s.empty())
		{
			cout << s.top() << " ";
			s.pop();
		}
	}
private:
	void _PostOrderThread(BinaryTreeThreadNode<T>* root, BinaryTreeThreadNode<T>*& prev)
	{
		if (root == NULL)
			return;
		_PostOrderThread(root->_left,prev);
		_PostOrderThread(root->_right, prev);
		if(root->_left==NULL)
		{
			root->_lefttag = THREAD;
			root->_left = prev;
		}
		if (prev&&prev->_right == NULL)
		{
			prev->_righttag = THREAD;
			prev->_right = root;
		}
		prev = root;

	}
	void _PrevOrderThread(BinaryTreeThreadNode<T>* root, BinaryTreeThreadNode<T>*& prev)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL)
		{
			root->_lefttag = THREAD;
			root->_left = prev;
		}
		if (prev&&prev->_right == NULL)
		{
			prev->_right = root;
			prev->_righttag = THREAD;
		}
		prev = root;
		if (root->_lefttag == LINK)
			_PrevOrderThread(root->_left,prev);
		if (root->_righttag == LINK)
			_PrevOrderThread(root->_right,prev);
	}
	void _InOrderThread(BinaryTreeThreadNode<T>* root,BinaryTreeThreadNode<T>*& prev)
	{
		if (root == NULL)
			return;
		_InOrderThread(root->_left,prev);
		if(root->_left==NULL)
		{
			root->_lefttag = THREAD;
			root->_left = prev;
		}
		if (prev&&prev->_right ==NULL)
		{
			prev->_righttag = THREAD;
			prev->_right = root;
		}
		prev = root;
		_InOrderThread(root->_right,prev);
	}
	BinaryTreeThreadNode<T>* _CreateTree(const T* str,int size,int &index)
	{
		BinaryTreeThreadNode<T>* root = NULL;
		if (index < size&&str[index] != '#')
		{
			root = new BinaryTreeThreadNode<T>(str[index]);
			root->_left = _CreateTree(str, size, ++index);
			root->_right = _CreateTree(str, size, ++index);
		}
		return root;
	}
	BinaryTreeThreadNode<T>* _root;
};