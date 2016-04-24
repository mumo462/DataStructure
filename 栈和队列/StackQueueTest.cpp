#include "StackQueue.h"
#include <string>
void Test1()
{
	Stack<string> t3;
	t3.Push("asd1");
	t3.Push("2asda");
	t3.Push("asd");
	t3.Push("asd");
	Stack<string> t4;
	t4=t3;
	t4.Pop();
	string i1=t3.Top();
	
}

void Test2()
{

}
int main()
{
	Test1();
	//Test2();
	return 0;
}