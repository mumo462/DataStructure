#include "HashTableBucket.h"

void Test1()
{
	HashTableBucket<string, string> h1;
	h1.Insert("��ѧ","math");
	h1.Insert("����", "chinese");
	h1.Insert("Ӣ��", "English");
	h1.Insert("��ѧ", "huaxue");
	h1.Insert("����", "shengwu");
	KeyValueNode<string,string>* Node= h1.Find("����");
	Node->_value = "bigology";
	Node->_next = new KeyValueNode<string, string>("����","wuli");
	h1.Delete("����");
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