#include "GeneralList.h"

void Test1()
{
	char* str = "(a,b,(c,d),(e,(f),h)) ";
	GeneralList s1(str);
	GeneralList s2(s1);
	GeneralList s3;
	s3 = s2;
	s1.Size();
	s1.Depth();
	s1.PrintGeneralList();
}
int main()
{
	Test1();
	return 0;
}