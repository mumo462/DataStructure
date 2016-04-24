#pragma once
#include <iostream>
using namespace std;
#include <string>

enum State
{
	EXITS,
	DEL,
	EMPTY,
};
size_t BKDRhash(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash*seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}
template <class K>
struct GetKeyValue
{
	int operator()(const K& key)
	{
		return key;
	}
};
template <>
struct GetKeyValue<string>
{
	int operator()(const string& key)
	{
		return BKDRhash(key.c_str());
	}
};
template <class K, class V>
struct KeyValueNode
{
	K _key;
	V _value;
	KeyValueNode()
	{}
	KeyValueNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
	{}
};
template <class K,class V, class GetKey = GetKeyValue<K>>
class KeyValue
{
	typedef KeyValueNode<K,V> KVNode;
public:
	KeyValue()
		:_data(NULL)
		,_size(0)
		,_capacity(0)
		,_status(NULL)
	{}
	KeyValue(int capacity)
		:_data(new KVNode[capacity])
		,_size(0)
		,_capacity(capacity)
		,_status(new State[capacity])
	{
		for (int i = 0; i < capacity; i++)
		{
			_status[i] = EMPTY;
		}
	}
	bool Insert(const K& key, const V& value)
	{
		if (_size * 10 / _capacity == 8)
		{
			KeyValue newKey(_capacity * 2);
			for (int i = 0; i < _capacity; i++)
			{
				if (_status[i] == EXITS)
				{
					newKey.Insert(_data[i]._key,_data[i]._value);
				}
			}
			Swap(newKey);
		}
		int i = 1;
		int index = HashGetIndex(key,0);
		while (_status[index] == EXITS)
		{
			index = (index + (2 * i - 1))%_capacity;
			i++;
		}
		_data[index]._key = key;
		_data[index]._value = value;
		_status[index] = EXITS;
		_size++;
		return true;
	}
	KVNode* Find(const K& key)
	{
		int index = HashGetIndex(key,0);
		int i = 1;
		while (_status[index] == EXITS)
		{
			if (_data[index]._key == key)
			{
				return &_data[index];
			}
			index = (index + 2 * i - 1) % _capacity;
			i++;
		}
		return NULL;
	}
	bool Remove(const K& key)
	{
		int i = 1;
		int index = HashGetIndex(key,0);
		while (_status[index] == EXITS)
		{
			if (_data[index]._key == key)
			{
				_status[index] = DEL;
				_size--;
				return true;
			}
			index = (index + 2 * i - 1) % _capacity;
			i++;
		}
		return false;
	}
	void Swap(KeyValue& k)
	{
		swap(_data, k._data);
		swap(_size, k._size);
		swap(_capacity, k._capacity);
		swap(_status, k._status);
	}
	void Print()
	{
		for (int i = 0; i < _capacity; i++)
		{
			cout << _status[i] << " ";
			cout << _data[i]._key << ":";
			cout << _data[i]._value << endl;
		}
	}
	~KeyValue()
	{
		if (_data)
		{
			delete[] _data;
			delete[] _status;
		}
	}
private:
	int HashGetIndex(const K& key, int i)
	{
		return (GetKey()(key) + i ^ 2) % _capacity;
	}
	KVNode* _data;
	int _size;
	int _capacity;
	State* _status;
};

