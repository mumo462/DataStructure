//#include <algorithm>
//#include "PriorityQueue.h"
#include "Heap.h"
//void _AdjustDown(int *a, int size, int parent)
//{
//	int child = parent * 2 + 1;
//	while (child < size)
//	{
//		if (child + 1 < size&&a[child + 1] > a[child])
//		{
//			child++;
//		}
//		if (a[child] > a[parent])
//		{
//			swap(a[child], a[parent]);
//			parent = child;
//			child = parent * 2 + 1;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//}
//void HeapSort(int *a,int size)
//{
//	
//	for (int i = (size - 2) / 2; i >= 0; i--)
//	{
//		_AdjustDown(a,size,i);
//	}
//	for (int i = size - 1; i > 0; i--)
//	{
//		swap(a[0],a[i]);
//		_AdjustDown(a,i,0);
//	}
//}
//
//void Test3()
//{
//	int a[10] = {1,3,4,5,7,6,8,9,10,2};
//	HeapSort(a, 10);
//
//}
void Test1()
{
	int a[] = { 10,16,18,12,11,13,15,17,14,19 };
	Heap<int, Greater<int>> h(a, 10);
	h.Pop();
	h.Push(10);
}
//void Test2()
//{
//	PriorityQueue<int> p;
//	p.Push(33);
//	p.Push(3);
//	p.Push(7);
//	p.Push(9);
//	p.Push(13);
//	p.Push(32);
//	p.Push(38);
//	p.Pop();
//	
//
//}
int main()
{
	Test1();
	return 0;
}