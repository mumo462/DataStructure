#pragma once

enum Colour
{
	RED,
	BLACK,
};

template <class K,class V>
struct  RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	K _key;
	V _value;
	Colour _col;

	RBTreeNode(const K& key, const V& value, Colour col = RED)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		,_key(key)
		,_value(value)
		,_col(col)
	{}
};

template <class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key,const V& value)
	{
		bool _isRotate = false;
		if (_root == NULL)
		{
			_root = new Node(key,value,BLACK);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key,value);
		if (parent->_key > cur->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;

		}
		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			Node* uncle = NULL;
			if (grandfather)
			{
				Node* pgNode = grandfather->_parent;
				if (grandfather->_left == parent)
				{
					uncle = grandfather->_right;
				}
				else
				{
					uncle = grandfather->_left;
				}
				if (uncle&&uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					if(cur)
						parent = cur->_parent;
					continue;
				}
				else
				{
					_isRotate = true;
					if (grandfather->_left == parent)
					{
						if (parent->_right == cur)
						{
							_RotateL(parent);
						}
						grandfather->_left = parent;
						_RotateR(grandfather);
						grandfather->_col = BLACK;
						grandfather->_left->_col=grandfather->_right->_col = RED;
					}
					else if (grandfather->_right == parent)
					{
						if (parent->_left == cur)
						{
							_RotateR(parent);
						}
						grandfather->_right = parent;
						_RotateL(grandfather);
						grandfather->_col = BLACK;
						grandfather->_right->_col=grandfather->_left->_col = RED;
					}
				}
				if (_isRotate)
				{
					if (pgNode == NULL)
					{
						_root = grandfather;
					}
					else if (pgNode->_key > grandfather->_key)
					{
						pgNode->_left = grandfather;
					}
					else
					{
						pgNode->_right = grandfather;
					}
				}
			_root->_col = BLACK;
			}
			break;
		}
	
		return true;
	}

	bool isBlance()
	{
		bool three = _isNotCol(_root);
		bool four = _isSameBlack(_root);
		cout << "isBlance?" << (three&&four) << endl;
		return three&&four;
	}
	bool _isSameBlack(Node* root)
	{
		if (root == NULL)
			return true;
		
		int judge=_BlackHigh(root);
		if (judge == -1)
		{
			return false;
		}
		return true;
	}
	bool _isNotCol(Node* root)
	{
		if (root == NULL)
			return true;
		if (root->_parent == NULL&&root->_col==RED)
		{
			return false;
		}
		else if (root->_parent&&root->_parent->_col == RED&&root->_col == RED)
		{
			return false;
		}
		else
		{
			return _isNotCol(root->_left)&& _isNotCol(root->_right);
		}
	}
	int _BlackHigh(Node* root)
	{
		if (root == NULL)
			return 0;
		int count = 0;
		if (root->_col == BLACK)
		{
			count = 1;
		}
		int Lheight = _BlackHigh(root->_left) + count;
		int Rheight = _BlackHigh(root->_right) + count;
		if (Lheight == Rheight)
		{
			return Lheight;
		}
		return -1;
	}
	void inOrder()
	{
		_inOrder(_root);
		cout << endl;
	}
private:
	void _inOrder(Node* root)
	{
		if (root == NULL)
			return;
		_inOrder(root->_left);
		cout << root->_key << " ";
		_inOrder(root->_right);

	}
	void _RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;
		parent = subL;
	}

	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;
		parent = subR;
	}
	Node* _root;
};

void Test1()
{
	int a[9] = {16,3,7,11,9,26,18,14,15};
	int b[16] = {4,2,6,1,3,5,15,7,16,14,10,13,20,35,43,61};
	RBTree<int, double> tree1;
	RBTree<int, double> tree2;
	for (int i = 0; i < 9; i++)
	{
		tree1.Insert(a[i],i);
	}
	for (int i = 0; i < 100; i++)
	{
		tree2.Insert(i, i);
	}
	tree1.isBlance();
	tree1.inOrder();
	tree2.isBlance();
	tree2.inOrder();

}