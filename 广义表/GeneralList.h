#pragma once
#include <assert.h>
#include <iostream>
using namespace std;
enum Type
{
	HEAD,
	SUB,
	VALUE,
};

struct GeneralListNode
{
	Type _type;
	GeneralListNode* _next;
	union
	{
		char _value;
		GeneralListNode* _SubLink;
	};
	GeneralListNode(Type type=HEAD, char value = 0)
		:_type(type)
		, _next(NULL)
	{
		if(type==SUB)
		{
			_SubLink = NULL;
		}
		else if (type == VALUE)
		{
			_value = value;
		}
	}
};

class GeneralList
{
public:
	GeneralList()
	{}
	GeneralList(char* str)
	{
		_head = _GeneralList(str);
	}
	GeneralList(const GeneralList& g1)
	{
		_head=_Copy(g1._head);
	}
	GeneralList operator=(GeneralList q1)
	{
		swap(_head, q1._head);
		return *this;
	}
	int Size()
	{
		return _Size(_head);
	}
	int Depth()
	{
		return _Depth(_head);
	}
	void PrintGeneralList()
	{
		_Print(_head);
	}
	~GeneralList()
	{
		if (_head)
		{
			_Delete(_head);
		}
	}
private:
	void _Delete(GeneralListNode* head)
	{
		GeneralListNode* cur = head->_next;
		delete head;
	
		while (cur)
		{
			GeneralListNode* DeleteCur = cur;
			cur = cur->_next;
			if (DeleteCur->_type == SUB)
			{
				_Delete(DeleteCur->_SubLink);
			}
			else
			{
				delete DeleteCur;
			}

		}
	}

	GeneralListNode* _Copy( GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		GeneralListNode* newHead = new GeneralListNode(HEAD);
		GeneralListNode* newcur = newHead;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				newcur->_next = new GeneralListNode(VALUE,cur->_value);
				newcur = newcur->_next;
			}
			else if (cur->_type == SUB)
			{
				newcur->_next = new GeneralListNode(SUB);
				newcur = newcur->_next;
				newcur->_SubLink = _Copy(cur->_SubLink);
			}
			cur = cur->_next;
		}
		return newHead;

	}
	GeneralListNode* _Print(GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)
			{
				cout << "(";
			}
			else if (cur->_type == VALUE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ",";
				}
				else
				{
					cout << ")";
				}
			}
			else if (cur->_type == SUB)
			{
				_Print(cur->_SubLink);
				if (cur->_next)
				{
					cout << ",";
				}
				else
				{
					cout << ")";
				}
			}
			cur = cur->_next;
		}
		return head;
	}
	int _Depth(GeneralListNode*& head)
	{
		GeneralListNode* cur = head;
		int depth = 1;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				int temp = _Depth(cur->_SubLink);
				if (depth  < temp+1)
				{
					depth = temp + 1;
				}
			}
			cur = cur->_next;
		}
		return depth;
	}
	int _Size(GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		int size = 0;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				size++;
			}
			else if (cur->_type == SUB)
			{

				size += _Size(cur->_SubLink);
			}
			cur = cur->_next;
		}
		return size;
	}
	bool IsValue(char ch)
	{
		if ((ch >= '0' && ch <= '9') || \
			(ch >= 'a' && ch <= 'z') || \
			(ch >= 'A' && ch <= 'Z'))
		{
			return true;
		}
		return false;
	}
	GeneralListNode* _GeneralList(char*& str)
	{
		assert(*str=='(');
		str++;
		GeneralListNode* head = new GeneralListNode(HEAD);
		GeneralListNode* cur = head;
		while (*str!=')')
		{
			if(*str=='(')
			{
				cur->_next=new GeneralListNode(SUB);
				cur = cur->_next;
				cur->_SubLink = _GeneralList(str);
				
			}
			else if (IsValue(*str))
			{
				cur->_next = new GeneralListNode(VALUE,*str);
				str++;
				cur = cur->_next;
			}
			else
			{
				str++;
			}
		}
		++str;
		return head;
	}
private:
	GeneralListNode* _head;
};