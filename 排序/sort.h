#pragma once
#include <iostream>
using namespace std;
#include <assert.h>
#include <stack>
void InsertSort(int *a,int size)
{
	assert(a);
	for (int i = 1; i < size; i++)
	{
		int index = i;
		int end = index - 1;
		int temp = a[index];
		while (end >= 0 && temp < a[end])
		{
			a[end + 1] = a[end];
			end--;
		}
		a[end + 1] = temp;
	}
}

void ShellSort(int *a, int size)
{
	assert(a);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < size; i++)
		{
			int index = i;
			int temp = a[index];
			int end = index - gap;
			while (end >= 0 && temp<a[end])
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = temp;
		}
	}
}
void BubSort(int* a,int size)
{
	for (int i = 0; i < size; i++)
	{
		int symbol = false;
		for (int j = 1; j < size - i ; j++)
		{
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
				symbol = true;
		}
		if (symbol == false)
			break;
	}
}
void SelectSort(int *a, int size)
{
	assert(a);
	/*for (int left = 0, right = size - 1;left<right;left++,right--)
	{
		int max = right, min = left;
		for (int i = left+1; i <= right; i++)
		{
			if (a[min] > a[i])
				min = i;
			if (a[max] < a[i])
				max = i;
		}
		if (min != left)
		{
			if (max == left)
			{
				swap(a[max], a[right]);
			}
			swap(a[min],a[left]);
		}
		if (max != right)
		{
			swap(a[max],a[right]);
		}
		
	}*/
	for (int left = 0, right = size - 1; left <= right; left++, right--)
	{
		int max = right, min = left;
		for (int i = left; i <= right; i++)
		{
			if (a[min] > a[i])
				swap(a[min], a[i]);
			if (a[max] < a[i])
				swap(a[max], a[i]);
		}
		swap(a[min], a[left]);
		swap(a[max], a[right]);
	}
}

void AdjustDown(int *a,int size,int parent)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size&&a[child + 1] > a[child])
		{
			child++;
		}
		if (a[parent] < a[child])
		{
			swap(a[parent],a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *a, int size)
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a,size,i);
	}
	for (int i = size - 1; i > 0; i--)
	{
		swap(a[0],a[i]);
		AdjustDown(a,i,0);
	}
}

void Combine(int* a, int* tmp, int begin1, int end1,int begin2, int end2)
{
	int index = 0;
	while (begin1 <= end1&&begin2 <= end2)
	{
		while (a[begin1] <= a[begin2]&&begin1<=end1)
		{
			tmp[index++] = a[begin1];
			begin1++;
		}
		while (a[begin1] > a[begin2] && begin2 <= end2)
		{
			tmp[index++] = a[begin2];
			begin2++;
		}
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
}
void _MergeSort(int* a, int* tmp, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		_MergeSort(a,tmp,left,mid);
		_MergeSort(a, tmp, mid+1, right);
		Combine(a,tmp,left,mid,mid+1,right);
		memcpy(a+left,tmp,(right-left+1)*sizeof(int));
	}
}

void MergeSort2(int *a, int size)
{
	assert(a);
	int gap = 0;
	int *temp = new int[size];
	int count = 0;
	//gap指begin1和end1每次的差值
	while (gap < size)
	{
		int begin1 = 0, end1 = gap, begin2 = end1 + 1, end2 = begin2 + gap;
		for (; end2 < size; begin1=end2+1,end1=begin1+gap,begin2=end1+1,end2=begin2+gap)
		{
			Combine(a,temp,begin1,end1,begin2,end2);
			memcpy(a+begin1,temp,(end2-begin1+1)*sizeof(int));
		}
		if (begin2 < size)
		{
			end2 = size - 1;
			Combine(a, temp, begin1, end1, begin2, size-1);
			memcpy(a + begin1, temp, (end2 - begin1 + 1)*sizeof(int));
		}
		count++;
		gap=pow(2,count)-1;
	}

}
void MergeSort(int *a, int size)
{
	assert(a);
	int *tmp = new int[size];
	int left = 0, right = size - 1;
	_MergeSort(a,tmp,left,right);
}

int _QuickSort(int* a,int left,int right,int key)
{
	while (left < right)
	{
		while (left < right&&a[left] <=a[key])
		{
			left++;
		}
		while (left < right&&a[right] >=a[key])
		{
			right--;
		}
		swap(a[left], a[right]);
	}
	if (a[left] > a[key])
	{
		swap(a[left],a[key]);
		return left;
	}
	return key;
}
int _QuickSort2(int* a, int left, int right, int key)
{
	int cur = left;
	int prev = left - 1;
	while (cur <= right)
	{
		if (a[cur] <= a[key])
		{
			prev++;
			if(prev!=cur)
				swap(a[prev], a[cur]);
		}
		cur++;
	}
	swap(a[prev+1],a[key]);
	return prev+1;
}
int FindMid(int* a, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (a[left] > a[right])
	{
		if (a[left] < a[mid])
			return left;
		else if (a[mid]>a[right])
			return mid;
		return right;
	}
	else
	{
		if (a[left] > a[mid])
			return left;
		else if (a[mid] < a[right])
			return mid;
		return right;
	}
}
void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left < right)
	{
		int mid = FindMid(a,left,right);
		swap(a[mid],a[right]);
		int key = right;
		int boundary=_QuickSort2(a,left,right-1,key);
		//int boundary=_QuickSort(a,left,right-1,key);
		QuickSort(a,left,boundary-1);
		QuickSort(a, boundary+1,right);
	}
} 

void NORQucikSort(int* a,int left,int right)
{
	stack<int> s1;
	s1.push(left);
	s1.push(right);
	while (!s1.empty())
	{
		int key = s1.top();
		int _right = s1.top();
		s1.pop();
		int _left = s1.top();
		s1.pop();
		if (_left >= _right)
			continue;
		int boundary = _QuickSort(a, _left, _right - 1, key);
		//int boundary = _QuickSort2(a, _left, _right - 1, key);
		s1.push(boundary + 1);
		s1.push(_right);

		s1.push(_left);
		s1.push(boundary-1);
	}
}

//计数排序
void CountSort(int *a, int size)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for (int i = 1; i < size; i++)
	{
		if (max < a[i])
			max = a[i];
		if (min > a[i])
			min = a[i];
	}
	int CountSize = max - min + 1;
	int *CountArray = new int[CountSize];
	memset(CountArray,0,CountSize*sizeof(int));
	for (int i = 0; i < size; i++)
	{
		CountArray[a[i]-min]++;
	}
	int index = 0;
	for (int i = 0; i <= CountSize; i++)
	{
		int count = CountArray[i];
		while (count-- > 0)
		{
			a[index++] = i+ min;
		}
	}
}

//基数排序

void DigitSort(int *a, int size)
{
	assert(a);
	int bit = 1, sum = 10;
	for (int i = 0; i < size; i++)
	{

		while (a[i] >= sum)
		{
			bit++;
			sum *= 10;
		}
	}
	int digit = 1;
	int *bucket = new int[size];
	while (digit <= bit)
	{
		int count[10] = { 0 };
		int position[10] = { 0 };
		for (int i = 0; i < size; i++)
		{
			int numbit = pow(10,digit-1);
			int bitvalue = (a[i] / numbit) % 10;
			count[bitvalue]++;
		}
		for (int i = 1; i < 10; i++)
		{
			position[i] = position[i - 1] + count[i - 1];
		}
		for (int i = 0; i < size; i++)
		{
			int numbit = pow(10, digit - 1);
			int bitvalue = (a[i] / numbit) % 10;
			bucket[position[bitvalue]++] = a[i];
		}
		digit++;
		memcpy(a,bucket,size*sizeof(int));
	}
}
