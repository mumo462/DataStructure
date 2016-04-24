#include <iostream>
#include <assert.h>
#include "TypeTraits.h"
using namespace std;

template <class T>
class Stack
{
public:
	Stack()
		:_data(NULL)
		,_size(0)
		,_capacity(0)
	{}
	Stack& operator=(const Stack& sta)
	{
		if(this!=&sta)
		{
			if(_data==NULL)
			{
				delete []_data;
			}
			_data=new T[sta._capacity];
			_size=sta._size;
			_capacity=sta._capacity;
			Copy(_data,sta._data,TypeTraits <T>:: IsPODType());
		}
		return *this;
	}
	void Push(const T& t)
	{
		ExamineCapacity();
		_data[_size++]=t;
	}
	void Pop()
	{
		assert(_size!=0);
		_size--;
	}
	T& Top()
	{
		assert(_size!=0);
		return _data[_size-1];
	}
	~Stack()
	{
		if(_data)
			delete []_data;
	}
private:
	void Copy(T* t1,T* t2,_TrueType)
	{
		memcpy(t1,t2,_size*sizeof(T));
	}
	void Copy(T* t1,T* t2,_FalseType)
	{
		for(size_t i=0;i<_size;i++)
		{
			t1[i]=t2[i];
		}
	}
	/*void Copy(T* t1,T* t2,bool judge)
	{
		if(judge)
		{
			memcpy(t1,t2,_size*sizeof(T));
			return;
		}
		else
		{
			for(size_t i=0;i<_size;i++)
			{
				t1[i]=t2[i];
			}
		}
	}*/
	void ExamineCapacity()
	{
		T* temp;
		if(_size>=_capacity)
		{
			if(_data!=NULL)
			{
				temp=new T[_capacity*2+1];
				Copy(temp,_data,TypeTraits <T>:: IsPODType());
				_data=temp;
			}
			else
			{
				_data=new T[_capacity*2+1];
			}
			_capacity=_capacity*2+1;
		}
	}
	T* _data;
	size_t _size;
	size_t _capacity;
};

template <class T>
struct ListNode
{
	ListNode(const T& t)
		:_data(t)
		,_next(NULL)
	{}
	T _data;
	ListNode* _next;
};
template <class T>
class Queue
{
public:
	Queue()
		:_head(NULL)
	{}
	Queue(const Queue& q)
		:_head(NULL)
	{
		ListNode<T>* cur1=q._head;
		ListNode<T>* newHead=NULL;
		while(cur1)
		{
			ListNode<T>* temp=new ListNode<T>(cur1->_data);
			cur1=cur1->_next;
			if(_head==NULL)
			{
				_head=temp;
				newHead=_head;
			}
			else
			{
			  newHead->_next=temp;
			  newHead=temp;
			}
		}
	}
	Queue& operator=(const Queue& q)
	{
		if(this!=&q)
		{
			if(_head!=NULL)
			{
				ListNode<T>* cur=_head;
				while(cur)
				{
					ListNode<T>* temp=cur;
					cur=cur->_next;
					delete temp;
				}
			}
			ListNode<T>* cur1=q._head;
			ListNode<T>* newHead=NULL;
			while(cur1)
			{
				ListNode<T>* temp=new ListNode<T>(cur1->_data);
				cur1=cur1->_next;
				if(_head==NULL)
				{
					_head=temp;
					newHead=_head;
				}
				newHead->_next=temp;
				newHead=temp;
			}
		}
		return *this;
	}
	size_t Size()
	{
		size_t size=0;
		ListNode<T>* cur=_head;
		while(cur)
		{
			size++;
			cur=cur->_next;
		}
		return size;
	}
	void Push(const T& t)
	{
		if(_head==NULL)
		{
			_head=new ListNode<T>(t);
		}
		else 
		{
			ListNode<T>* cur=_head;
			while(cur->_next!=NULL)
			{
				cur=cur->_next;
			}
			ListNode<T>* temp=new ListNode<T>(t);
			cur->_next=temp;
		}
	}
	void Pop()
	{
		assert(_head);
		ListNode<T>* temp=_head;
		_head=_head->_next;
		delete temp;
	}
	~Queue()
	{
		ListNode<T>* cur=_head;
		if(cur)
		{
			delete _head;
			cur=cur->_next;
			_head=cur;
		}
	}
private:
	ListNode<T>* _head;
};

