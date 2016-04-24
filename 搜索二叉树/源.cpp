#include <iostream>
using namespace std;
#include "BinarySerachTree.h"

void Test1()
{
	int a[10] = { 5,3,4,1,7,8,2,6,0,9 };
	BinarySearchTree<int, double> t;
	for (int i = 0; i < 10; i++)
	{
		//t.Insert_R(a[i],a[i]);
		t.Insert(a[i], a[i]);

	}
	for (int i = 0; i < 10; i++)
	{
		t.Remove(a[i]);
	}
	//t.Find(7);
	t.Find_R(6);
	t.inOrder();

}
int main()
{
	Test1();
	return 0;
}