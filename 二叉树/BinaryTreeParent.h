#pragma once
#include <iostream>
using namespace std;
#include <assert.h>
template <class T>
struct BinaryTreeParentNode
{
	T _data;
	BinaryTreeParentNode<T>* _left;
	BinaryTreeParentNode<T>* _right;
	BinaryTreeParentNode<T>* _parent;
	BinaryTreeParentNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		,_parent(NULL)
	{}
};
template <class T>
class BinaryTreeParent
{
public:
	BinaryTreeParent(const T* str,int size)
	{
		int index = 0;
		_root=_CreateTree(str,size,index);
	}
private:
	BinaryTreeParentNode<T>* _CreateTree(const T* str,int size,int& index)
	{
		BinaryTreeParentNode<T>* root=NULL;
		if (index<size&&str[index] != '#')
		{
			root = new BinaryTreeParentNode<T>(str[index]);
			root->_left = _CreateTree(str,size,++index);
			if (root->_left)
			{
				root->_left->_parent = root;
			}
			root->_right = _CreateTree(str, size, ++index);
			if (root->_right)
			{
				root->_right->_parent = root;
			}
		}
		return root;
	}

	BinaryTreeParentNode<T>* _root;
};