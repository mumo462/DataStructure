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
template <class K,class GetKey=GetKeyValue<K>>
class HashTable
{
public:
	HashTable()
		:_data(NULL)
		,_size(0)
		,_capacity(0)
		,_status(NULL)
	{}
	HashTable(const int& capacity)
		:_data(new K[capacity])
		,_size(0)
		,_capacity(capacity)
		,_status(new State[capacity])
	{
		for (int i = 0; i < capacity; i++)
		{
			_status[i] = EMPTY;
		}
	}
	bool Insert(const K& key)
	{
		if (_size * 10 / _capacity == 8)
		{
			HashTable newHash(_capacity*2);
			for (int i = 0; i < _capacity; i++)
			{
				if (_status[i] == EXITS)
				{
					newHash.Insert(_data[i]);
				}
			}
			Swap(newHash);
		}
		int index = HashGetIndex(key);
		while (_status[index] == EXITS)
		{
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		_data[index] = key;
		_status[index] = EXITS;
		_size++;
		return true;
	}
	bool Remove(const K& key)
	{
		int index = HashGetIndex(key);
		while (_status[index] == EXITS)
		{
			if (_data[index] == key)
			{
				_status[index] = DEL;
				_size--;
				return true;
			}
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}
	bool Find(const K& key)
	{
		int index = HashGetIndex(key);
		while (_status[index] == EXITS)
		{
			if (_data[index] == key)
			{
				return true;
			}
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}
	void Swap(HashTable& h)
	{
		swap(_data,h._data);
		swap(_size,h._size);
		swap(_capacity,h._capacity);
		swap(_status,h._status);
	}
	void Print()
	{
		for (int i = 0; i < _capacity; i++)
		{
			cout << _status[i] << ":";
			cout << _data[i] << endl;
		}
	}
	~HashTable()
	{
		if (_data)
		{
			delete[]_data;
			delete[]_status;
		}
	}
private:
	int HashGetIndex(const K& key)
	{
		return GetKey()(key) % _capacity;
	}
	
	K* _data;
	size_t _size;
	size_t _capacity;
	State* _status;
};