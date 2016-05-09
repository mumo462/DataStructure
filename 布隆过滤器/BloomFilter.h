#pragma once
#include "BitMap.h"
#include <string>

#define M  249997   
#define M1 1000001   
#define M2 0xF0000000  
unsigned int RSHash(char*str)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash*a + (*str++);
		a *= b;
	}
	return(hash % M);
}
template<class K>
struct _HashFun1
{
	unsigned int operator()(const K& key)
	{
		return RSHash((char *)key.c_str());
	}
};

unsigned int JSHash(char*str)
{
	unsigned int hash = 1315423911;
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	return(hash % M);
}
template<class K>
struct _HashFun2
{
	unsigned int operator()(const K& key)
	{
		return JSHash((char *)key.c_str());
	}
};

unsigned int PJWHash(char*str)
{
	unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters = (unsigned int)((BitsInUnignedInt * 3) / 4);
	unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
	unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	while (*str)
	{
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash&HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters))&(~HighBits));
		}
	}
	return(hash % M);
}
template<class K>
struct _HashFun3
{
	unsigned int operator()(const K& key)
	{
		return PJWHash((char *)key.c_str());
	}
};

unsigned int ELFHash(char*str)
{
	unsigned int hash = 0;
	unsigned int x = 0;
	while (*str)
	{
		hash = (hash << 4) + (*str++);
		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}
	return(hash % M);
}
template<class K>
struct _HashFun4
{
	unsigned int operator()(const K& key)
	{
		return  ELFHash((char *)key.c_str());
	}
};

unsigned int BKDRHash(char*str)
{
	unsigned int seed = 131;// 31 131 1313 13131 131313 etc..    
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash*seed + (*str++);
	}
	return(hash % M);
}
template<class K>
struct _HashFun5
{
	unsigned int operator()(const K& key)
	{
		return BKDRHash((char*)key.c_str());
	}
};
template <class K=string,
class HashFun1= _HashFun1<K>,
class HashFun2=_HashFun2<K>,
class HashFun3 = _HashFun3<K>,
class HashFun4 = _HashFun4<K>,
class HashFun5 = _HashFun5<K >>
class BloomFilter
{
public:
	BloomFilter(size_t size)
		:_capacity(size)
		,_BitMap(_capacity)
	{}
	void Set(const K& key)
	{
		_BitMap.Set(HashFun1()(key)%_capacity);
		_BitMap.Set(HashFun2()(key) % _capacity);
		_BitMap.Set(HashFun3()(key) % _capacity);
		_BitMap.Set(HashFun4()(key) % _capacity);
		_BitMap.Set(HashFun5()(key) % _capacity);
	}
	bool IsIn(const K& key)
	{
		bool isin=_BitMap.Test(HashFun1()(key) % _capacity);
		if (isin == false)
			return false;
		isin = _BitMap.Test(HashFun2()(key) % _capacity);
		if (isin == false)
			return false;
		isin = _BitMap.Test(HashFun3()(key) % _capacity);
		if (isin == false)
			return false;
		isin = _BitMap.Test(HashFun4()(key) % _capacity);
		if (isin == false)
			return false; 
		isin = _BitMap.Test(HashFun5()(key) % _capacity);
		if (isin == false)
			return false;
		return true;
	}
private:
	size_t _capacity;
	BitMap _BitMap;
};

void Test()
{
	BloomFilter<> bf(40);
	bf.Set("德玛西亚");
	bf.Set("诺克萨斯");
	bf.Set("艾欧尼亚");
	bf.Set("暗影岛");

	cout << bf.IsIn("德玛西亚") << endl;;
	cout << bf.IsIn("诺克萨斯") << endl;
	cout << bf.IsIn("艾欧尼亚") << endl;
	cout << bf.IsIn("暗影岛") << endl;
	cout << bf.IsIn("啦啦啦德玛西亚") << endl;
	cout << bf.IsIn("诺克萨") << endl;
	cout << bf.IsIn("人在塔在") << endl;

}