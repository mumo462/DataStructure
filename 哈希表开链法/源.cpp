#include "HashTableBucket.h"

void Test1()
{
	HashTableBucket<string, string> h1;
	h1.Insert("数学","math");
	h1.Insert("语文", "chinese");
	h1.Insert("英语", "English");
	h1.Insert("化学", "huaxue");
	h1.Insert("生物", "shengwu");
	KeyValueNode<string,string>* Node= h1.Find("生物");
	Node->_value = "bigology";
	Node->_next = new KeyValueNode<string, string>("物理","wuli");
	h1.Delete("生物");
	h1.Print();
	HashTableBucket<string, string> h2;
	h2 = h1;
	h2.Print(); 
}
int main()
{
	Test1();
	return 0;
}