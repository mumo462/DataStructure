#pragma once
#include <iostream>	
using namespace std;
#include <vector>

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}
	BitMap(size_t size)
		:_size(0)
	{
		_data.resize((size>>5)+1);
	}
	bool Set(size_t num)
	{
		size_t index = num / 32;
		size_t n = num % 32;
		if (_data[index] & (1 << n))
		{
			return false;
		}
		_data[index] |= (1<<n);
		_size++;
		return true;
	}
	bool ReSet(size_t num)
	{
		size_t index = num / 32;
		size_t n = num % 32;
		if (_data[index] & (1 << n))
		{
			_data[index] &= ~(1<<n);
			_size--;
			return true;
		}
		return false;
	}
	bool Test(size_t num)
	{
		size_t index = num / 32;
		size_t n = num % 32;
		if (_data[index] & (1 << n))
		{
			return true;
		}
		return false;
	}
private:
	vector<int> _data;
	size_t _size;
};