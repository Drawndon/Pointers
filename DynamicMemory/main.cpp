//DynamicMemory
#include <iostream>
using namespace std;

void FillRand(int arr[], const int n);
void Print(int arr[], const int n);
int* PushBack(int arr[], int &n, int value);
int* PushFront(int arr[], int &n, int value);
int* Insert(int arr[], int &n, int value, int index);
int* PopBack(int arr[], int& n);
int* PopFront(int arr[], int& n);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер массива: "; cin >> n;
	int* arr = new int[n]; //Объявление динамического массива
	FillRand(arr, n);
	Print(arr, n);
	int value, index;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс: "; cin >> index;
	arr = Insert(arr, n, value, index);
	cout << "Добавили по индексу" << endl;
	Print(arr, n);
		
	arr = PushBack(arr, n, value);
	cout << "Добавили в конец" << endl;
	Print(arr, n);

	arr = PushFront(arr, n, value);
	cout << "Добавили в начало" << endl;
	Print(arr, n);

	arr = PopBack(arr, n);
	cout << "Удалили с конца" << endl;
	Print(arr, n);

	arr = PopFront(arr, n);
	cout << "Удалили сначала" << endl;
	Print(arr, n);

	delete[] arr;
	//Memory leak - утечка памяти
}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % 100; //Через арифметику указателей и оператор разыменования
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