#include <iostream>
using namespace std;
#pragma warning (disable: 4018)
#include "HuffManTree.h"
#include "FileCompress.h"
#include <time.h>
int main()
{
	clock_t start = clock();
	FileCompress file;
	file.Compress("Input.BIG");
	file.unCompress("Input.BIGHuffMan");
	clock_t finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << 'S' << endl;
	
	return 0;
}