#include "BitMap.h"
int main()
{
	BitMap b1(-1);
	b1.Set(1);
	b1.Set(3);
	b1.Set(4);
	b1.Test(18);
	return 0;
}