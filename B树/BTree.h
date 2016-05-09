#pragma once

template <class K,int M>
struct BTreeNode
{
	K _key[M];   //关键字数组
	BTreeNode<K, M>* _subs[M+1]; //孩子个数
	BTreeNode<K, M>* _parent;	
	size_t _size;           //关键字个数
	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (int i = 0; i < M; i++)
		{
			_key[i] = K();
		}
		for (int i = 0; i < M + 1; i++)
		{
			_subs[i] = NULL;
		}
	}
};

template <class K, class V>
struct Pair
{
	K _first;
	V _second;

	Pair(const K& k=K(),const V& v=V())
		:_first(k)
		,_second(v)
	{}
};

template <class K, int M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	Pair<Node*,int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			int i = 0;
			while (i < cur->_size&&cur->_key[i] < key)
			{
				i++;
			}
			if (cur->_key[i] == key)
			{
				return Pair<Node*, int>(cur,i);
			}
			parent = cur;
			cur=cur->_subs[i];
		}
		return Pair<Node*, int>(parent,-1);
	}
	
	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node();
			_root->_key[0] = key;
			_root->_size++;
			return true;
		}
		Pair<Node*, int> ret = Find(key);
		if (ret._second == -1)
		{
			_InsertKey(ret._first,key);
			Node* cur = ret._first;
			if (cur->_size < M)
			{
				return true;
			}
			else
			{
				while (cur&&cur->_size==M)
				{
					int boundary = cur->_size / 2;
					int size = cur->_size;
					Node* temp = new Node();
					Node* parent = cur->_parent;
					int count = 0;
					int i = boundary + 1;
					for (; i < size; i++)
					{
						temp->_key[count] = cur->_key[i];
						temp->_subs[count] = cur->_subs[i];
						if (temp->_subs[count])
						{
							temp->_subs[count]->_parent = temp;
						}
						temp->_parent = parent;
						temp->_size++;
						count++;
						cur->_size--;
					}
					temp->_subs[count] = cur->_subs[i];
					if (temp->_subs[count])
					{
						temp->_subs[count]->_parent = temp;
					}
					
					if (parent == NULL)
					{
						_root = new Node();
						_root->_key[0] = cur->_key[boundary];
						cur->_size--;
						_root->_subs[0] = cur;
						_root->_subs[1] = temp;
						cur->_parent = _root;
						temp->_parent = _root;
						_root->_size++;
					}
					else
					{
						cur->_size--;
						_InsertKey(parent, cur->_key[boundary], temp);
					}
					cur = parent;
				}
			}
		}
	}
	void inOrder()
	{
		_inOrder(_root);
		cout << endl;
	}
	void _inOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		for (int i = 0; i < root->_size; i++)
		{
			_inOrder(root->_subs[i]);
			cout << root->_key[i] << " ";
		}
		_inOrder(root->_subs[root->_size]);
	}
private:
	void _InsertKey(Node* root, const K& key,Node* sub=NULL)
	{
		int size = root->_size;
		int i = size - 1;
		for (; i >= 0; i--)
		{
			if (root->_key[i] > key)
			{
				root->_key[i + 1] = root->_key[i];
				root->_subs[i + 2] = root->_subs[i + 1];
			}
			else
				break;
		}
		root->_key[i + 1] = key;
		root->_subs[i + 2] = sub;
		root->_size++;
	}
	BTreeNode<K, M>* _root;
};


void Test1()
{
	int a[7] = { 53,75,139,49,145,36,101 };
	BTree<int, 3> b;
	BTree<int, 6> c;
	for (int i = 0; i < 7; i++)
	{
		b.Insert(a[i]);
	}
	b.inOrder();
	for (int i = 0; i < 100; i++)
	{
		c.Insert(i);
	}
	c.inOrder();

}
