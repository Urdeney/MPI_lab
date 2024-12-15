// IDM-23-04
// Afanasyev Vadim
// LR¹1

#include <iostream>
#include <iomanip>
#include <chrono>
#include "mpi.h"

#include <thread>

using namespace std;
using namespace std::chrono;

#define TAG_SEND 0
#define TAG_RECEIVE 1

#define N 3

int Matrix1[N][N];



static void FillMatrices()
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			Matrix1[i][j] = rand() % 10;
		}
	}

}
template<typename Type>
static void PrintMatrix(Type matrix[N][N])
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout << "\t" << matrix[i][j] << "";
		}
		cout << endl;
	}
}

void SingleProcessMult()
{
	// TODO
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int Matr[N][N] ={
		{2,5,7},
		{6,3,4},
		{5,-2,-3} 
	};


	int Minors[N][N];

	//матрица миноров
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			// Инициализируем индексы для 2x2 матрицы
			int subMatrix[2][2];
			int row = 0, col = 0;

			for (int k = 0; k < N; ++k) {
				for (int v = 0; v < N; ++v) {
					if (k != i && v != j) { // Исключаем i-ю строку и j-й столбец
						subMatrix[row][col] = Matr[k][v];
						col++;
						if (col == 2) {
							col = 0;
							row++;
						}
					}
				}
			}
			// Вычисляем определитель
			Minors[i][j] = (subMatrix[0][0] * subMatrix[1][1]) - (subMatrix[1][0] * subMatrix[0][1]);
		}
	}

	//вычисление определителя
	float det = Matr[0][0] * Minors[0][0] - Matr[0][1] * Minors[0][1] + Matr[0][2] * Minors[0][2];
	cout << det << endl;



	//матрица алгебраических дополнений
	Minors[0][1] *= -1;
	Minors[1][0] *= -1;
	Minors[1][2] *= -1;
	Minors[2][1] *= -1;


	//транспонирование матрицы
	int Tranc[N][N];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			Tranc[j][i] = Minors[i][j];
		}
	}

	//получение обратной матрицы
	float Result[N][N];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			Result[i][j] = (1/det) * Tranc[i][j];
		}
	}

	PrintMatrix(Result);

	cout << "Checking..." << endl;
}