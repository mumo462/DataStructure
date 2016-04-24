#pragma once
#include <iostream>
#include "Heap.h"
using namespace std;

template <class T>
class PriorityQueue
{
public:
	PriorityQueue()
	{}
	void Push(const T& x)
	{
		h.Push(x);
	}
	void Pop()
	{
		h.Pop();
	}
private:
	Heap<T,Greater<T>> h;
};