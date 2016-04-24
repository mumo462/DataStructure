#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <vector>
static size_t BKDRHash(const char * str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
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
		return  BKDRHash(key.c_str());
	}
};

template <class K, class V>
struct KeyValueNode
{
	K _key;
	V _value;
	KeyValueNode<K, V>* _next;
	KeyValueNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template <class K,class V,class GetKey = GetKeyValue<K>>
class HashTableBucket
{
	typedef KeyValueNode<K, V> KVNode;
public:
	HashTableBucket()
		:_size(0)
	{}
	HashTableBucket(const HashTableBucket<K,V>& ht)
	{
		_table.resize(ht._table.size());
		for (int i = 0; i < _table.size(); i++)
		{
			KVNode* cur =ht._table[i];
			if (cur == NULL)
			{
				_table[i] = NULL;
				continue;
			}
			while (cur)
			{
				KVNode* tmp = new KVNode(ht._table[i]->_key, ht._table[i]->_value);
				tmp->_next = _table[i];
				_table[i] = tmp;
				_size++;
				cur = cur->_next;
			}
		}
	}
	HashTableBucket operator=(HashTableBucket ht)
	{
		swap(_table,ht._table);
		_size = ht._size;
		return *this;
	}
	~HashTableBucket()
	{
		for (int i = 0; i < _table.size(); i++)
		{
			KVNode* cur = _table[i];
			while (cur)
			{
				KVNode* next = cur->_next;
				delete cur;
				cur = next;
			}
		}
	}
	bool Insert(const K& key,const V& value)
	{
		CheckCapacity();
		int index = HashGetIndex(key,_table.size());
		KVNode* tmp = new KVNode(key,value);
		tmp->_next = _table[index];
		_table[index] = tmp;
		_size++;
		return true;
	}
	KVNode* Find(const K& key)
	{
		int index = HashGetIndex(key,_table.size());
		KVNode* cur = _table[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}
	bool Delete(const K& key)
	{
		int index = HashGetIndex(key,_table.size());
		KVNode* cur = _table[index];
		if (cur == NULL)
			return false;
		if (cur->_key == key)
		{
			_table[index] =cur->_next;
			delete cur;
			return true;
		}
		KVNode* prev = cur;
		while (cur)
		{
			cur = cur->_next;
			if (cur->_key == key)
			{
				prev->_next = cur->_next;
				delete cur;
				return true;
			}
			prev = cur;
		}
		return false;
	}
	void Print()
	{
		for (int i = 0; i < _table.size(); i++)
		{
			printf("_table[%d]->",i);
			KVNode* cur = _table[i];
			while (cur)
			{
				cout << cur->_key << ":" << cur->_value<<"->";
				cur = cur->_next;
			}
			cout << "NULL"<<endl;
		}
		cout << endl;
	}
private:
	void CheckCapacity()
	{
		if (_size == _table.size())
		{
			vector<KVNode*> newTable;
			newTable.resize(GetCapacity(_size));
			for (int i = 0; i < newTable.size(); i++)
			{
				newTable[i] = NULL;
			}
			for (int i = 0; i < _table.size(); i++)
			{
				KVNode* cur = _table[i];
				KVNode* newcur = NULL;
				while (cur)
				{
					KVNode* next = cur->_next;
					if (newTable[i] == NULL)
					{
						newTable[i] = cur;
						newcur = cur;
					}
					newcur->_next = cur;
					newcur = newcur->_next;

					cur = cur->_next;
				}
			}
			swap(_table,newTable);
		}
	}
	int GetCapacity(int _size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (int i = 0; i < _PrimeSize; i++)
		{
			if (_PrimeList[i] > _size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize-1];
	}
	int HashGetIndex(const K& key,int capacity)
	{
		return GetKey()(key) % capacity;
	}
	vector<KVNode*> _table;
	int _size;
};