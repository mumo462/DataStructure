//#include "HashTable.h"
#include "KeyValue.h"

//void Test1()
//{
//	HashTable<string> H1(10);
//	H1.Insert("�ֵ�");
//	H1.Insert("�ʵ�");
//	H1.Insert("�õ�");
//	H1.Insert("����");
//	H1.Insert("ˢ��");
//	H1.Insert("����");
//	H1.Insert("���");
//	H1.Insert("Ϧ��");
//	H1.Insert("����");
//	H1.Remove("�ֵ�");
//	H1.Print();
//	cout << H1.Find("�ֵ�") << endl;
//	cout << H1.Find("�ʵ�") << endl;
//}
void Test2()
{
	KeyValue<string,string> K1(10);
	K1.Insert("Ӣ��","English");
	K1.Insert("��ѧ", "math");
	K1.Insert("����", "chinese");
	K1.Insert("����", "wuli");
	KeyValueNode<string,string>* M=K1.Find("����");
	M->_value = "physic";
	K1.Remove("Ӣ��");
	M = K1.Find("����");
	K1.Print();


}
int main()
{
	Test2();
	return 0;
}