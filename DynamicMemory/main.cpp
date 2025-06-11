//DynamicMemory
#include <iostream>
using namespace std;
using std::cin;
using std::cout;

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* PushBack(int arr[], int &n, int value);
int* PushFront(int arr[], int &n, int value);

int* Insert(int arr[], int &n, int value, int index);
int* Erase(int arr[], int& n, int index);

int* PopBack(int arr[], int& n);
int* PopFront(int arr[], int& n);

int** PushRowBack(int** arr, int& rows, const int cols);

void PushColBack(int** arr, const int rows, int& cols);

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
	cout << endl << "Удалили с конца "<< value << endl;
	Print(arr, n);

	arr = PopFront(arr, n);
	cout << endl << "Удалили сначала "<< value << endl;
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



	//1) Создаем массив указателей
	int** arr = new int* [rows];
	
	
	//2) Выделяем память под строки
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = PushRowBack(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);
	PushColBack(arr, rows, cols);
	//Заполняем последний добавленный столбец случайными числами
	for (int i = 0; i < rows; i++)
		arr[i][cols - 1] = rand() % 100;
	Print(arr, rows, cols);

	//1) Удаляются строки
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) Теперь можно удалить массив указателей
	delete[] arr;

#endif // DYNAMIC_MEMORY_2

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
	int* arr1 = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		arr1[i] = arr[i];
	}
	delete[] arr;
	arr1[n] = value;
	n++;
	return arr1;
}

int* PushFront(int arr[], int& n, int value)
{
	int* arr1 = new int[n + 1];
	
	for (int i = 1; i < n + 1; i++)
	{
		arr1[i] = arr[i - 1];
	}
	delete[] arr;
	arr1[0] = value;
	n++;
	return arr1;
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

int* Erase(int arr[], int& n, int index)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)
		buffer[i] = arr[i < index ? i : i + 1];
	delete[] arr;
	return buffer;
}

int* PopBack(int arr[], int& n)
{
	int *buffer = new int[--n];
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

int** PushRowBack(int** arr, int& rows, const int cols)
{
	//1) Создаем буферный массив указателей нужного размера
	int** buffer = new int* [rows + 1];
	//2) Копируме адреса строк в новый массив
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