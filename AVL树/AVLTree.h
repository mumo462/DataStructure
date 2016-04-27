#pragma once
template <class K, class V>
struct  AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	K _key;
	V _value;

	//平衡因子
	int _bf;
	AVLTreeNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		bool IsRotate = false;
		return _Insert(_root, key, value, IsRotate);
	}
	bool _Insert(Node*& _root, const K& key, const V& value, bool IsRotate)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
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
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		Node* ppNode = NULL;
		while (parent)
		{
			if (parent->_key > key)
			{
				parent->_bf--;
			}
			else
				parent->_bf++;
			if (parent&&parent->_bf == 2)
			{
				ppNode = parent->_parent;
				IsRotate = true;
				if (cur->_bf == 1)
				{
					_RotateL(parent);
				}
				else if (cur->_bf == -1)
				{
					_RotateRL(parent);
				}
				break;
			}
			else if (parent&&parent->_bf == -2)
			{
				ppNode = parent->_parent;
				IsRotate = true;
				if (cur->_bf == 1)
				{
					_RotateLR(parent);
				}
				else if (cur->_bf == -1)
				{
					_RotateR(parent);
				}
				break;
			}
			cur = parent;
			parent = cur->_parent;
			if (cur->_bf == 0)
			{
				break;
			}
		}


		if (IsRotate == true)
		{
			if (ppNode == NULL)
			{
				_root = parent;
			}
			if (ppNode)
			{
				if (ppNode->_key > parent->_key)
				{
					ppNode->_left = parent;
				}
				else
				{
					ppNode->_right = parent;
				}
			}
		}	
	    return true;
	}
	bool isBlanceTree()
	{
		bool b= _isBlanceTree(_root);
		cout << "isBlance?" << b<<endl;
		return b;
		
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
	bool _isBlanceTree(Node* root)
	{
		if (root == NULL)
			return true;
		if (abs(_high(root->_left) - _high(root->_right)) > 1)
		{
			return false;
		}
		if (_high(root->_right) - _high(root->_left) != root->_bf)
		{
			cout << root->_key << "的载荷因子有问题";
			return false;
		}
		return _isBlanceTree(root->_left) && _isBlanceTree(root->_right);
	}
	int _high(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int Lhigh = _high(root->_left)+1;
		int Rhigh = _high(root->_right)+1;
		return Lhigh > Rhigh ? Lhigh: Rhigh;
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
		parent->_bf = subR->_bf = 0;

		parent = subR;
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
		parent->_bf = subL->_bf = 0;
		parent = subL;
	}
	//void _RotateRL(Node*& parent)
	//{
	//	_RotateR(parent->_right);
	//	_RotateL(parent);
	//}
	void _RotateRL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		subR->_left = subRL->_right;
		if (subRL->_right)
		{
			subRL->_right->_parent = subR;
		}
		subRL->_right = subR;
		subRL->_parent = subR->_parent;
		subR->_parent = subRL;
		
		if (subRL->_bf == 0 || subRL->_bf == 1)
		{
			subR->_bf = 0;
		}
		else
		{
			subR->_bf = 1;
		}

		parent->_right = subRL->_left;
		if (subRL->_left)
		{
			subRL->_left->_parent = parent;
		}
		subRL->_left = parent;
		subRL->_parent = parent->_parent;
		parent->_parent = subRL;

		if (subRL->_bf == 0 || subRL->_bf == -1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
		}
		subRL->_bf = 0;
		parent = subRL;
	}

	void _RotateLR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = subLR->_left;
		if (subLR->_left)
		{
			subLR->_left->_parent = subL;
		}

		subLR->_left = subL;
		subLR->_parent = subL->_parent;
		subL->_parent = subLR;

		if (subLR->_bf == 0 || subLR->_bf == -1)
		{
			subL->_bf = 0;
		}
		else
		{
			subL->_bf = -1;
		}

	    parent->_left= subLR->_right;
		if (subLR->_right)
		{
			subLR->_right->_parent = parent;
		}

		subLR->_right = parent;
		subLR->_parent = parent->_parent;
		parent->_parent = subLR;
		if (subLR->_bf == 0 || subLR->_bf == 1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
		}
		subLR->_bf = 0;
		parent = subLR;
	}
	Node* _root;
};