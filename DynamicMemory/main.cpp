//DynamicMemory
#include <iostream>
using namespace std;

void FillRand(int arr[], const int n);
void Print(int arr[], const int n);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер массива: "; cin >> n;
	int* arr = new int[n]; //Объявление динамического массива
	FillRand(arr, n);
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
