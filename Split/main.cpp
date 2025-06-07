#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	const int n = 10;
	int arr[n];
	int count_even = 0;

	//Генерируем исходный массив из десяти случайных чисел
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
		if (arr[i] % 2 == 0) count_even++;
	}

	//Выводим сгенерированный массив
	cout << "Сгенерированный массив: ";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
		
	}
	cout << endl;

	//Выделяем память для двух массивов необходимого размера
	int* even_arr = new int[count_even];
	int* odd_arr = new int[n - count_even];
	
	//Заполняем динамические массивы соответствующими элементами
	for (int i = 0, j = 0, k = 0; i < n; i++)
	{
		if (arr[i] % 2 == 0) even_arr[j++] = arr[i];
		else odd_arr[k++] = arr[i];
	}
	
	//Выводим массив четных чисел
	cout << endl << "Массив четных чисел: ";
	for (int i = 0; i < count_even; i++) cout << even_arr[i] << "\t";
	cout << endl;
	
	//Выводим массив нечетных чисел
	cout << endl << "Массив нечетных чисел: ";
	for (int i = 0; i < n - count_even; i++) cout << odd_arr[i] << "\t";
	cout << endl;
	
	//Освобождаем память
	delete[] odd_arr;
	delete[] even_arr;
}