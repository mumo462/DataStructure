#include "BinaryTree.h"
#include "BinaryTreeParent.h"
#include "BinaryTreeThread.h"
void Test1()
{
	int a[] = { 1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8 };
	BinaryTree<int> b1(a, 15);
	/*BinaryTree<int> b2;
	b2 = b1;*/
	b1.PrevOrder();
	b1.PrevOrder_NOR();
	b1.InOrder();
	b1.InOrder_NOR();
	b1.PostOrder();
	b1.PostOrder_NOR();
	b1.LevelOrder();
	BinaryTreeNode<int>* s = b1.Find(5);
	cout << b1.Size() << endl;
	cout << b1.Depth() << endl;
	cout << b1.GetLeafNum() << endl;
}

void Test2()
{
	int a[] = { 1,2,3,'#','#',4,'#','#',5,6 };
	BinaryTreeParent<int> b1(a, 10);
}
void Test3()
{
	int a[] = { 1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8 };
	BinaryTreeThread<int> b(a,15);
	b.InOrderThread();
	b.InOrder();
	/*b.PrevOrderThread();
	b.PrevOrder();*/
	//b.PostOrderThread();
	//b.PostOrder();
}
int main()
{
	Test3();
	return 0;
}