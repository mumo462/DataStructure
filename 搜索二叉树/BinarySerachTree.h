#pragma once
#include <assert.h>

template <class K,class V>
struct BinarySearchTreeNode
{
	K _key;
	V _value;

	BinarySearchTreeNode<K,V>* _left;
	BinarySearchTreeNode<K,V>* _right;

	BinarySearchTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> BSTNode;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	bool Insert_R(const K& key, const V& value)
	{
		return _Insert(_root,key,value);
	}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new BSTNode(key,value);
			return true;
		}
		BSTNode* cur = _root;
		BSTNode* prev = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		if (prev->_key > key)
		{
			prev->_left = new BSTNode(key,value);
		}
		else
		{
			prev->_right = new BSTNode(key, value);
		}
		return true;
	}

	BSTNode* Find(const K& key)
	{
		BSTNode* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
				return cur;
		}
		return NULL;
	}

	BSTNode* Find_R(const K& key)
	{
		return _Find_R(_root,key);
	}

	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		if (_root->_left == NULL&&_root->_right == NULL)
		{
			delete _root;
			_root = NULL;
			return true;
		}
		BSTNode* cur = _root;
		BSTNode* prev = NULL;

		while (cur)
		{
			if (cur->_key > key)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				if (prev == NULL&&!(cur->_left&&cur->_right))
				{
					if (cur->_left == NULL)
						_root = cur->_right;
					else
						_root = cur->_left;
					delete cur;
					return true;
				}
				if (cur->_left == NULL)
				{
					if (prev->_key > key)
					{
						prev->_left = cur->_right;
					}
					else
					{
						prev->_right = cur->_right;
					}
					delete cur;
					return true;
				}
				else if (cur->_right == NULL)
				{
					if (prev->_key > key)
					{
						prev->_left = cur->_left;
					}
					else
					{
						prev->_right = cur->_left;
					}
					delete cur;
					return true;
				}
				else if (cur->_right&&cur->_left)
				{
					//如果左右都不为空，找右子树中最小的和该节点交换，再删除
					BSTNode* RTMin = cur->_right;
					BSTNode* PrevMin = cur;

					if (RTMin->_left != NULL)
					{
						PrevMin = RTMin;
						RTMin = RTMin->_left;
					}
					swap(RTMin->_key,cur->_key);
					swap(RTMin->_value, cur->_value);
					delete RTMin;
					if(PrevMin == cur)
						PrevMin->_right = NULL;
					else
						PrevMin->_left = NULL;
					return true;
				}
			}
		}
	}
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root,key);
	}
	void inOrder()
	{
		_inOrder(_root);
	}
private:
	bool _Remove_R(BSTNode*& root,const K& key)
	{
		if (root == NULL)
			return false;
		if (root->_key > key)
		{
			return _Remove_R(root->_left,key);
		}
		else if(root->_key < key)
		{
			return _Remove_R(root->_right, key);
		}
		else
		{
			BSTNode* temp = root;
			if (root->_left == NULL)
			{
				root = root->_right;
				delete temp;
				return true;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
				delete temp;
				return true;

			}
			else
			{
				BSTNode* RTMin = root->_right;
				if (RTMin->_left != NULL)
				{
					RTMin = RTMin->_left;
				}
				swap(RTMin->_key,root->_key);
				swap(RTMin->_value, root->_value);

				_Remove_R(root->_right,key);
				
			}
		}
	}
	BSTNode* _Find_R(BSTNode* root, const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key > key)
		{
			return _Find_R(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Find_R(root->_right, key);
		}
		else
			return root;
	}
	void _inOrder(BSTNode* root)
	{
		if (_root == NULL)
			return;
		if(root->_left!=NULL)
			_inOrder(root->_left);
		cout << root->_key << " ";
		if(root->_right!=NULL)
			_inOrder(root->_right);
	}
	bool _Insert(BSTNode*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new BSTNode(key, value);
			return true;
		}
		if (root->_key > key)
		{
			return _Insert(root->_left,key,value);
		}
		else if (root->_key < key)
		{
			return _Insert(root->_right, key, value);
		}
		else
			return false;
	}
	BSTNode* _root;
};