#pragma once
#include <vector>
template <class T>
struct Triple
{
	Triple()
	{}
	Triple(int row, int col, T value)
		:_rowsize(row)
		, _colsize(col)
		, _value(value)
	{}
	int _rowsize;
	int _colsize;
	T _value;
};
template <class T>
class SparseMatrix
{
public:
	SparseMatrix(T* array,int row,int col,T invalid)
		:_row(row)
		,_col(col)
		,_invalid(invalid)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (array[i*col + j] != invalid)
				{
					T temp = array[i*col + j];
					Triple<T> n(i,j,temp);
					_array.push_back(n);
				}
			}
		}
	}
	T& Display(int x, int y)
	{
		for (int i = 0; i < _array.size(); i++)
		{
			if (_array[i]._rowsize == x&&_array[i]._colsize == y)
			{
				return _array[i]._value;
			}
		}
		return _invalid;
	}
	void PrintMatrix()
	{
		int index = 0;
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				if (index<_array.size()&&_array[index]._colsize == j&&_array[index]._rowsize == i)
				{
					cout << _array[index]._value << " ";
					index++;
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
	}
	void TurnMatrix()
	{
		vector<Triple<T>> array;
		int index = 0;
		for (int i = 0; i < _col; i++)
		{
			for (int j = 0; j < _row; j++)
			{
				for (int k = 0; k < _array.size(); k++)
				{
					if (_array[k]._colsize == i&&_array[k]._rowsize == j)
					{
						Triple<T> n(_array[k]._colsize, _array[k]._rowsize, _array[k]._value);
						array.push_back(n);
						break;
					}
				}
			}
		}
		_array = array;
		swap(_row,_col);
	}
	void FastTurnMatrix()
	{
		vector<Triple<T>> array;
		array.resize(_array.size());
		int* RowCounts =new int[_col];
		memset(RowCounts,0,_col * sizeof(int));
		int* RowStart = new int[_col];
		memset(RowCounts, 0, _col * sizeof(int));
		for (int i = 0; i < _array.size(); i++)
		{
			RowCounts[_array[i]._colsize]++;
		}
		RowStart[0] = 0;
		for (int i = 1; i < _col; i++)
		{
			RowStart[i] = RowCounts[i - 1] + RowStart[i - 1];
		}
		for (int i = 0; i < _array.size(); i++)
		{
			array[RowStart[_array[i]._colsize]] = _array[i];
			swap(array[RowStart[_array[i]._colsize]]._colsize, array[RowStart[_array[i]._colsize]]._rowsize);
			RowStart[_array[i]._colsize]++;
		}
		_array = array;
		delete[] RowCounts;
		delete[] RowStart;
		swap(_row,_col);
	}
	~SparseMatrix()
	{}
private:
	vector< Triple<T>> _array;
	int _row;
	int _col;
	T _invalid;
};