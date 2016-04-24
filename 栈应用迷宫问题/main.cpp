#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

void GetMaze(int* array,int row,int col)
{
	FILE* fout=fopen("maze.txt","r");
	assert(fout);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;)
		{
			char ch=getc(fout);
			if(ch=='0'||ch=='1')
			{
				array[i*col+j]=ch-'0';
				j++;
			}
		}
	}
	fclose(fout);
}


void PrintMaze(int* array,int row,int col)
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout<<array[i*col+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

struct paths
{
	paths(int row,int col)
		:_row(row)
		,_col(col)
	{}
	int _row;
	int _col;
};

//stack<paths> RunMaze(int *array,paths entry,int row,int col)
//{
//	assert(array);
//	stack<paths> s;
//	stack<paths> s1;
//	paths next=entry;
//	s.push(next);
//	array[col*next._row+next._col]=2;
//	while(!s.empty())
//	{
//		next=s.top();
//		paths cur=next;
//		if(next._row==row-1)
//		{
//			if(s1.empty())
//			{
//				s1=s;
//			}
//			else if(s1.size()>s.size())
//			{
//				s1=s;
//			}
//		}
//		up
//		next=cur;
//		next._row--;
//		if(array[col*next._row+next._col]==0)
//		{
//			array[col*next._row+next._col]=2;
//			s.push(next);
//			continue;
//		}
//		right
//		next=cur;
//		next._col++;
//		if(array[col*next._row+next._col]==0)
//		{
//			array[col*next._row+next._col]=2;
//			s.push(next);
//			continue;
//		}
//		down
//		next=cur;
//		next._row++;
//		if(array[col*next._row+next._col]==0)
//		{
//			array[col*next._row+next._col]=2;
//			s.push(next);
//			continue;
//		}
//		left
//		next=cur;
//		next._col--;
//		if(array[col*next._row+next._col]==0)
//		{
//			array[col*next._row+next._col]=2;
//			s.push(next);
//			continue;
//		}
//		next=s.top();
//		s.pop();
//		array[col*next._row+next._col]=3;
//	}
//	return s1;
//}

void Run(int *array,stack<paths> &s,stack<paths> &s1,int row,int col)
{
	if (s.empty())
	{
		return;
	}
	paths next=s.top();
	paths cur=next;
	if(next._row==row-1)
	{
		if(s1.empty())
		{
			s1=s;
		}
		else if(s1.size()>s.size())
		{
			s1=s;
		}
	}
	//up
	next = cur;
	next._row--;
	if (array[col*next._row + next._col] == 0)
	{
		array[col*next._row + next._col] = 2;
		s.push(next);
		Run(array, s, s1, row, col);
	}
	//right
	next = cur;
	next._col++;
	if (array[col*next._row + next._col] == 0)
	{
		array[col*next._row + next._col] = 2;
		s.push(next);
		Run(array, s, s1, row, col);
	}
	//down
	next = cur;
	next._row++;
	if (array[col*next._row + next._col] == 0)
	{
		array[col*next._row + next._col] = 2;
		s.push(next);
		Run(array, s, s1, row, col);
	}
	//left
	next = cur;
	next._col--;
	if (array[col*next._row + next._col] == 0)
	{
		array[col*next._row + next._col] = 2;
		s.push(next);
		Run(array, s, s1, row, col);
	}
	if (s.empty())
	{
		return;
	}
	next = s.top();
	s.pop();
	array[col*next._row + next._col] = 3;
	Run(array, s, s1, row, col);
}
stack<paths> RunMaze(int *array,paths entry,int row,int col)
{
	assert(array);
	stack<paths> s;
	stack<paths> s1;
	s.push(entry);
	Run(array,s,s1,row,col);
	return s1;
}

int main()
{
	int a[10][10]={};
	GetMaze((int*)a,10,10);
	PrintMaze((int*)a,10,10);
	paths entry(2,0);
	int i=RunMaze((int*)a,entry,10,10).size();
	PrintMaze((int*)a,10,10);
	return 0;
}