//#include "HashTable.h"
#include "KeyValue.h"

//void Test1()
//{
//	HashTable<string> H1(10);
//	H1.Insert("字典");
//	H1.Insert("词典");
//	H1.Insert("得到");
//	H1.Insert("无语");
//	H1.Insert("刷单");
//	H1.Insert("害人");
//	H1.Insert("如何");
//	H1.Insert("夕阳");
//	H1.Insert("怕死");
//	H1.Remove("字典");
//	H1.Print();
//	cout << H1.Find("字典") << endl;
//	cout << H1.Find("词典") << endl;
//}
void Test2()
{
	KeyValue<string,string> K1(10);
	K1.Insert("英语","English");
	K1.Insert("数学", "math");
	K1.Insert("语文", "chinese");
	K1.Insert("物理", "wuli");
	KeyValueNode<string,string>* M=K1.Find("物理");
	M->_value = "physic";
	K1.Remove("英语");
	M = K1.Find("物理");
	K1.Print();


}
int main()
{
	Test2();
	return 0;
}