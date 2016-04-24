#pragma once
#include <assert.h>
#include <vector>
template <class T>
struct Greater
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 > t2;
	}
};
template <class T>
struct Less
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 < t2;
	}
};

template <class T,class Compare=Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(const T* str, int size)
	{
		for (int i = 0; i < size; i++)
		{
			_array.push_back(str[i]);
		}
		for (int i = (size - 2) / 2; i >= 0; i--)
		{
			_AdjustDown(i);
		}
	}
	void Pop()
	{
		assert(!_array.empty());
		swap(_array[0],_array[_array.size()-1]);
		_array.pop_back();
		_AdjustDown(0);
	}
	T& Top()
	{
		assert(!_array.empty());
		return _array[0];
		
	}
	void Push(const T& x)
	{
		_array.push_back(x);
		_AdjustUp(_array.size()-1);
	}
	int Size()
	{
		return _array.size();
	}
	~Heap()
	{
	}
private:
	void _AdjustDown(int size)
	{
		int parent = size;
		int child = parent * 2 + 1;
		while (child<_array.size())
		{
			if (child + 1 < _array.size() && Compare()(_array[child + 1] , _array[child]))
			{
				child++;
			}
			if (Compare()( _array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdjustUp(int child)
	{
		int parent = (child-1)/2;
		while (child > 0)
		{
			if (Compare()( _array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
	vector<T> _array;
};