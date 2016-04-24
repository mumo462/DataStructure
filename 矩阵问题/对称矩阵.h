#pragma once
template <class T>
class SymmetryArray
{
public:
	SymmetryArray(T* array, size_t row, size_t col)
		:_array(new T[row*(row + 1) / 2])
		, _row(row)
		, _col(col)
	{
		int count = 0;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (i < j)
				{
					break;
				}
				_array[count++] = array[i*col + j];
			}
		}
	}
	T& Display(size_t x, size_t y)
	{
		if (x < y)
		{
			swap(x, y);
		}
		T temp = _array[x*(x + 1) / 2 + y];
		return temp;
	}
	void PrintArray()
	{
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				if (i >= j)
				{
					cout << _array[i*(i + 1) / 2 + j]<<" ";
				}
				else
				{
					cout << _array[j*(j + 1) / 2 + i] << " ";

				}
			}
			cout << endl;
		}
		cout << endl;

	}
	~SymmetryArray()
	{
		if (_array)
			delete[] _array;
	}
private:
	T* _array;
	size_t _row;
	size_t _col;
};