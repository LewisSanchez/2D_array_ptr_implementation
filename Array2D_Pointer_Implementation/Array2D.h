#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "Row.h"
#include "Exception.h"

template <typename T>
class Array2D
{
	public:
		Array2D();
		Array2D(int row, int col = 0);
		Array2D(const Array2D & copy);
		~Array2D();
		Array2D & operator= (const Array2D & rhs);

		Row<T> operator[] (int index);
		Row<T> operator[] (int index) const;
		int getRow();
		void setRow(int row);
		int getColumn();
		void setColumn(int column);
		T & Select(int row, int column);

	private:
		T ** m_array;
		int m_row;
		int m_col;

		void AllocateArrayMemory(int row, int column);
		void CopyArrayValues(const Array2D & array2D);
		void DeallocateArrayMemory();
};

template <typename T>
Array2D<T>::Array2D()
	: m_array(nullptr), m_row(0), m_col(0)
{

}

template <typename T>
Array2D<T>::Array2D(int row, int col)
	: m_row(row), m_col(col)
{
	AllocateArrayMemory(row, col);
}

template <typename T>
Array2D<T>::Array2D(const Array2D & copy)
	: m_row(copy.m_row), m_col(copy.m_col)
{
	AllocateArrayMemory(copy.m_row, copy.m_col);
	CopyArrayValues(copy);
}

template <typename T>
Array2D<T>::~Array2D()
{
	if (m_array != nullptr)
		DeallocateArrayMemory();

	m_row = 0;
	m_col = 0;
}

template <typename T>
Array2D<T> & Array2D<T>::operator= (const Array2D<T> & rhs)
{
	if (this != &rhs)
	{
		if (m_array != nullptr)
			DeallocateArrayMemory();

		m_row = rhs.m_row;
		m_col = rhs.m_col;
		AllocateArrayMemory(rhs.m_row, rhs.m_col);
		CopyArrayValues(rhs);
	}

	return *this;
}

template <typename T>
Row<T> Array2D<T>::operator[] (int index)
{
	if (index < 0 || index >= m_row)
		throw Exception("Error: Array row index access violation");

	Row<T> row(*this, index);

	return row;
}

template <typename T>
Row<T> Array2D<T>::operator[] (int index) const
{
	if (index < 0 || index >= m_row)
		throw Exception("Error: Array row index access violation");

	Row<T> row(const_cast<Array2D<T> &>(*this), index);

	return row;
}

template <typename T>
int Array2D<T>::getRow()
{
	return m_row;
}

template <typename T>
void Array2D<T>::setRow(int row)
{
	Array2D<T> newArray(row, m_col);
	int rowsToCopy = (row <= m_row ? row : m_row);

	for (int row = 0; row < rowsToCopy; row++)
	{
		for (int col = 0; col < m_col; col++)
			newArray.m_array[row][col] = this->m_array[row][col];
	}

	*this = newArray;
	m_row = row;
}

template <typename T>
int Array2D<T>::getColumn()
{
	return m_col;
}

template <typename T>
void Array2D<T>::setColumn(int column)
{
	Array2D<T> newArray(m_row, column);
	int columnsToCopy = (column <= m_col ? column : m_col);

	for (int row = 0; row < m_row; row++)
	{
		for (int col = 0; col < columnsToCopy; col++)
			newArray.m_array[row][col] = this->m_array[row][col];
	}

	*this = newArray;
	m_col = column;
}

template <typename T>
void Array2D<T>::AllocateArrayMemory(int row, int column)
{
	m_array = new T *[row];

	for (int curRow = 0; curRow < m_row; curRow++)
		m_array[curRow] = new T[column];
}

template <typename T>
T & Array2D<T>::Select(int row, int column)
{
	return m_array[row][column];
}

template <typename T>
void Array2D<T>::CopyArrayValues(const Array2D<T> & array2D)
{
	for (int curRow = 0; curRow < array2D.m_row; curRow++)
	{
		for (int curCol = 0; curCol < array2D.m_col; curCol++)
			m_array[curRow][curCol] = array2D.m_array[curRow][curCol];
	}
}

template <typename T>
void Array2D<T>::DeallocateArrayMemory()
{
	for (int curRow = 0; curRow < m_row; curRow++)
		delete[] m_array[curRow];

	delete[] m_array;
	m_array = nullptr;
}

#endif