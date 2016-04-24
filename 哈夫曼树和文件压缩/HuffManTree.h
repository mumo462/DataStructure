#pragma once
#include "Heap.h"
template <class T>
struct HuffManTreeNode
{
	HuffManTreeNode<T>* _left;
	HuffManTreeNode<T>* _right;
	HuffManTreeNode<T>* _parent;
	T _weight;

	HuffManTreeNode(const T& x) 
		:_weight(x), _left(NULL), _right(NULL), _parent(NULL)
	{}

	
};

template <class T>
struct NodeCompare
{
	bool operator()(const HuffManTreeNode<T>* l, const HuffManTreeNode<T>* r)
	{
		return (l->_weight) <= (r->_weight);
	}

};

template <class T>
class HuffManTree
{
	typedef HuffManTreeNode<T> Node;
public:
	HuffManTree()
		:_root(NULL)
	{}
	void CreateTree(const T* a, int size,T invalid)
	{
		Heap<Node*, NodeCompare<T>> minHeap;
		for (int i = 0; i < size; i++)
		{
			if (a[i] != invalid)
			{
				Node* tmp = new Node(a[i]);
				minHeap.Push(tmp);
			}
		}
		Node* parent= minHeap.Top();
		while (minHeap.Size() > 1)
		{
			Node* left=minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			parent = new Node(left->_weight+right->_weight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
			
			minHeap.Push(parent);
		}
		_root = parent;
	}

	Node* _root;
};