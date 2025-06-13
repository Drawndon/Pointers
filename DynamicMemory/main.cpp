//DynamicMemory
#include <iostream>
using namespace std;
using std::cin;
using std::cout;

int** Allocate(int rows, int cols);
void Clear(int**& arr, int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);

void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* PushBack(int arr[], int& n, int value);
int* PushFront(int arr[], int& n, int value);

int* Insert(int arr[], int& n, int value, int index);
int** InsertRow(int** arr, int& rows, const int cols, int index);
void InsertCol(int** arr, int rows, int& cols, int index);

int* Erase(int arr[], int& n, int index);
int** EraseRow(int** arr, int& rows, const int index);
void EraseCol(int** arr, int rows, int& cols, int index);

int* PopBack(int arr[], int& n);
int* PopFront(int arr[], int& n);

int** PopRowFront(int** arr, int& rows);
int** PopRowBack(int** arr, int& rows);
void PopColBack(int** arr, const int rows, int& cols);
void PopColFront(int** arr, const int rows, int& cols);

int** PushRowBack(int** arr, int& rows, const int cols);
int** PushRowFront(int** arr, int& rows, const int cols);
void PushColBack(int** arr, const int rows, int& cols);
void PushColFront(int** arr, const int rows, int& cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1

	int n;
	cout << "Введите размер массива: "; cin >> n;
	int* arr = new int[n]; //Объявление динамического массива
	FillRand(arr, n);
	Print(arr, n);
	int value, index = -1;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс не больше " << n << " и не меньше " << 0 << endl; while (index > n || index < 0) cin >> index;
	arr = Insert(arr, n, value, index);
	cout << endl << "Добавили по индексу " << index << " значение " << value << endl;
	Print(arr, n);

	arr = PushBack(arr, n, value);
	cout << endl << "Добавили в конец " << value << endl;
	Print(arr, n);

	arr = PushFront(arr, n, value);
	cout << endl << "Добавили в начало " << value << endl;
	Print(arr, n);

	arr = PopBack(arr, n);
	cout << endl << "Удалили с конца " << value << endl;
	Print(arr, n);

	arr = PopFront(arr, n);
	cout << endl << "Удалили сначала " << value << endl;
	Print(arr, n);

	arr = Erase(arr, n, index);
	cout << endl << "Удалили элемент по индексу " << index << endl;
	Print(arr, n);

	delete[] arr;
	//Memory leak - утечка памяти
#endif // DYNAMIC_MEMORY_1


#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	int** arr = Allocate(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = PushRowBack(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);

	cout << endl << "Добавили строку в конец" << endl;
	Print(arr, rows, cols);

	arr = PushRowFront(arr, rows, cols);
	FillRand(arr[0], cols, 100, 1000);

	cout << endl << "Добавили строку в начало" << endl;
	Print(arr, rows, cols);

	PushColBack(arr, rows, cols);
	//Заполняем последний добавленный столбец случайными числами
	for (int i = 0; i < rows; i++)
		arr[i][cols - 1] = rand() % 100;

	cout << endl << "Добавили столбик в конец" << endl;
	Print(arr, rows, cols);

	PushColFront(arr, rows, cols);
	for (int i = 0; i < rows; i++)
		arr[i][0] = rand() % 100;

	cout << endl << "Добавили столбик в начало" << endl;
	Print(arr, rows, cols);

	arr = PopRowFront(arr, rows);

	cout << endl << "Удалили строку в начале" << endl;
	Print(arr, rows, cols);

	arr = PopRowBack(arr, rows);

	cout << endl << "Удалили строку в конце" << endl;
	Print(arr, rows, cols);

	PopColBack(arr, rows, cols);

	cout << endl << "Удалили столбец в конце" << endl;
	Print(arr, rows, cols);


	PopColFront(arr, rows, cols);

	cout << endl << "Удалили столбец в начале" << endl;
	Print(arr, rows, cols);

	int index;
	cout << "Введите индекс добавляемой строки: "; cin >> index;

	arr = InsertRow(arr, rows, cols, index);
	FillRand(arr[index], cols, 100, 1000);

	cout << endl << "Вставили строку" << endl;
	Print(arr, rows, cols);

	cout << "Введите индекс добавляемого столбца: "; cin >> index;
	InsertCol(arr, rows, cols, index);
	for (int i = 0; i < rows; i++) arr[i][0] = rand() % 100;
	cout << endl << "Вставили стоблец" << endl;
	Print(arr, rows, cols);

	cout << "Введите индекс удаляемой строки: "; cin >> index;
	arr = EraseRow(arr, rows, index);
	cout << "Удалили строку" << endl;
	Print(arr, rows, cols);

	cout << "Введите индекс удаляемого столбца: "; cin >> index;
	EraseCol(arr, rows, cols, index);
	cout << "Удалили столбец" << endl;
	Print(arr, rows, cols);


	Clear(arr, rows);

#endif // DYNAMIC_MEMORY_2

}

int** Allocate(int rows, int cols)
{
	//1) Создаем массив указателей
	int** buffer = new int* [rows];


	//2) Выделяем память под строки
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = new int[cols];
	}
	return buffer;
}

void Clear(int**& arr, int rows)
{
	//1) Удаляются строки
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) Теперь можно удалить массив указателей
	delete[] arr;

	//3) Зануляем указатель на массив
	arr = nullptr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand; //Через арифметику указателей и оператор разыменования
	}

}
void FillRand(int** arr, const int rows, const int cols, int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % (maxRand - minRand) + minRand;
		}
	}
}

void Print(int arr[], const int n)
{
	//cout << arr << endl;
	//cout << *arr << endl;

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t"; //Через оператор индексирования (subscript operator)
	}
	cout << endl;
}

void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int* PushBack(int arr[], int& n, int value)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	delete[] arr;
	buffer[n] = value;
	n++;
	return buffer;
}

int* PushFront(int arr[], int& n, int value)
{
	int* buffer = new int[n + 1];

	for (int i = 1; i < n + 1; i++)
	{
		buffer[i] = arr[i - 1];
	}
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}

int* Insert(int arr[], int& n, int value, int index)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < n; i++)
		buffer[i < index ? i : i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

int** InsertRow(int** arr, int& rows, const int cols, int index)
{
	if (index < 0 || index > rows)
	{
		cout << "Error out of range exception" << endl;
		return arr;
	}
	int** buffer = new int* [rows + 1];

	for (int i = 0; i < rows; i++) buffer[i < index ? i : i + 1] = arr[i];
	
	delete[] arr;

	buffer[index] = new int[cols] {};
	
	rows++;

	return buffer;
}

void InsertCol(int** arr, int rows, int& cols, int index)
{
	if (index == 0) PushColFront(arr, rows, cols);
	else if (index == cols) PushColBack(arr, rows, cols);
	else
	{
		for (int i = 0; i < rows; i++)
		{
			int* buffer = new int[cols + 1]{};
			for (int j = 0; j < cols; j++)
			{
				//if (j < index) buffer[j] = arr[i][j];
				//else buffer[j + 1] = arr[i][j];
				buffer[j < index ? j : j + 1] = arr[i][j];
			}
			delete[] arr[i];
			arr[i] = buffer;
		}
		cols++;
	}

}

int* Erase(int arr[], int& n, int index)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)
		buffer[i] = arr[i < index ? i : i + 1];
	delete[] arr;
	return buffer;
}

int** EraseRow(int** arr, int& rows, const int index)
{
	if (index == 0) return PopRowFront(arr, rows);
	else if (index == rows - 1) return PopRowBack(arr, rows);
	else
	{
		int** buffer = new int* [--rows];

		for (int i = 0; i < rows; ++i)
		{
			if (i < index) buffer[i] = arr[i];
			else buffer[i] = arr[i + 1];
		}
		delete[] arr[index];
		delete[] arr;
		return buffer;
	}
}

void EraseCol(int** arr, int rows, int& cols, int index)
{
	if (index == 0) PopColFront(arr, rows, cols);
	else if (index == cols - 1) PopColBack(arr, rows, cols);
	else
	{
		for (int i = 0; i < rows; ++i)
		{
			int* buffer = new int[cols - 1]{};
			for (int j = 0; j < cols - 1; ++j)
			{
				if (j < index) buffer[j] = arr[i][j];
				else buffer[j] = arr[i][j + 1];
			}
			delete[] arr[i];
			arr[i] = buffer;
		}
		cols--;
	}
}

int* PopBack(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)
		buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

int* PopFront(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++) buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int** PopRowFront(int** arr, int& rows)
{
	int** buffer = new int* [--rows];
	for (int i = 0; i < rows; i++) buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int** PopRowBack(int** arr, int& rows)
{
	int** buffer = new int* [--rows];
	for (int i = 0; i < rows; i++) buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

void PopColBack(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1]{};
		for (int j = 0; j < cols - 1; j++) buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	--cols;

}

void PopColFront(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1]{};
		for (int j = 0; j < cols - 1; j++) buffer[j] = arr[i][j + 1];
		delete[] arr[i];
		arr[i] = buffer;
	}

	--cols;

}

int** PushRowBack(int** arr, int& rows, const int cols)
{
	//1) Создаем буферный массив указателей нужного размера
	int** buffer = new int* [rows + 1];
	//2) Копируем адреса строк в новый массив
	for (int i = 0; i < rows; i++) buffer[i] = arr[i];
	//3) Удаляем исходный массив указателей
	delete[] arr;
	//4) Добавляем добавляемую строку
	buffer[rows] = new int[cols] {};
	//5)После добавления строки, количество строк увеличиваеся на 1
	rows++;
	//6) Возвращаем новый массив
	return buffer;
}

int** PushRowFront(int** arr, int& rows, const int cols)
{
	int** buffer = new int* [rows + 1];
	for (int i = 0; i < rows; i++) buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[0] = new int[cols] {};
	rows++;
	return buffer;

}

void PushColBack(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		//1) Создаем буферную строку нужного размера
		int* buffer = new int[cols + 1]{};
		//2) Копируем элементы из исходной строки в буферрую
		for (int j = 0; j < cols; j++) buffer[j] = arr[i][j];
		//3) Удаляем исходную строку
		delete[] arr[i];
		//4) Подменяем адрес исходной строки адресом новой строки
		arr[i] = buffer;
	}
	cols++;
}

void PushColFront(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1]{};
		for (int j = 0; j < cols; j++) buffer[j + 1] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}