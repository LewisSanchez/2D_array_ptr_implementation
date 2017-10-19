#include <crtdbg.h>
#include <Windows.h>
#include <cassert>
#include <iostream>
using std::cout;

#include "Array2D.h"
#include "Row.h"

#define _CRTDBG_MAP_ALLOC

const size_t GREEN = 10;
const size_t RED = 12;
const size_t WHITE = 23;
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void RunTests();
void PrintTestHeader(const char * testName);
void PrintTestPass(const char * test);
void PrintTestFail(const char * test, const char * message);
void TestingConstructor();
void TestingTwoArgConstructor();
void TestingCopyConstructor();
void TestingAssignmentOperator();
void TestingIndexer();
void TestingSelect();
void TestingConst();

int main()
{
	RunTests();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}

void RunTests()
{
	TestingConstructor();
	TestingTwoArgConstructor();
	TestingCopyConstructor();
	TestingAssignmentOperator();
	TestingIndexer();
	TestingSelect();
	TestingConst();
}

void PrintTestHeader(const char * testName)
{
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << "\n********** " << testName << " **********" << std::endl;
}

void PrintTestPass(const char * test)
{
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << '\t' << test << ": TEST PASS" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void PrintTestFail(const char * test, const char * message)
{
	SetConsoleTextAttribute(hConsole, RED);
	std::cerr << message << std::endl;
	std::cerr << '\t' << test << ": TEST FAIL" << std::endl;
	SetConsoleTextAttribute(hConsole, WHITE);
}

void TestingConstructor()
{
	const char * test = "Constructor";
	PrintTestHeader(test);

	Array2D<int> array1;

	assert(array1.getRow() == 0);
	assert(array1.getColumn() == 0);

	PrintTestPass(test);
}

void TestingTwoArgConstructor()
{
	const char * test = "Two-arg constructor";
	PrintTestHeader(test);

	try
	{
		// Creating instance of 2x2 array
		Array2D<int> array1(2, 2);

		int values[2][2] = { { 1, 2 },{ 3, 4 } };
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				array1[row][col] = values[row][col];
		}

		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				assert(array1[row][col] == values[row][col]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingCopyConstructor()
{
	const char * test = "Copy constructor";
	PrintTestHeader(test);

	try
	{
		// Creating instance of an array
		Array2D<int> array1;
		array1.setRow(2);
		array1.setColumn(2);

		int values[2][2] = { { 1, 2 },{ 3, 4 } };
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				array1[row][col] = values[row][col];
		}

		Array2D<int> array2(array1);
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				assert(array2[row][col] == values[row][col]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingAssignmentOperator()
{
	const char * test = "Assignment operator";
	PrintTestHeader(test);

	try
	{
		// Creating instance of an array
		Array2D<int> array1(2, 2);
		Array2D<int> array2;

		int values[2][2] = { { 1, 2 },{ 3, 4 } };
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				array1[row][col] = values[row][col];
		}

		array2 = array1;
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				assert(array2[row][col] == values[row][col]);
		}

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingIndexer()
{
	const char * test = "Indexer";
	PrintTestHeader(test);

	try
	{
		// Creating instance of an array
		Array2D<int> array1(2, 2);

		int values[2][2] = { { 1, 2 },{ 3, 4 } };
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				array1[row][col] = values[row][col];
		}

		array1[0][1] = 5;
		assert(array1[0][1] == 5);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingSelect()
{
	const char * test = "Select";
	PrintTestHeader(test);

	try
	{
		// Creating instance of an array
		Array2D<int> array1(2, 2);

		int values[2][2] = { { 1, 2 },{ 3, 4 } };
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				array1.Select(row, col) = values[row][col];
		}

		array1.Select(0, 1) = 5;
		assert(array1[0][1] == 5);

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}

void TestingConst()
{
	const char * test = "Testing const";
	PrintTestHeader(test);

	try
	{
		Array2D<int> array1(2, 2);

		int values[2][2] = { { 1, 2 },{ 3, 4 } };
		for (size_t row = 0; row < 2; ++row)
		{
			for (size_t col = 0; col < 2; ++col)
				array1[row][col] = values[row][col];
		}

		const Array2D<int> array2(array1);
		const int value = array2[1][1];

		PrintTestPass(test);
	}
	catch (Exception exception)
	{
		PrintTestFail(test, exception.getMessage());
	}
}