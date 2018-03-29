#ifndef _MATRIX
#define _MATRIX
#define ndim 10
#define N_TYPE float
#define FORMAT_STR "%18.11e "
#define MATRIX(name) N_TYPE name[ndim][ndim]
#define VECTOR(name, size) N_TYPE name[size]

/**
 *
 * @param n -
 * @param a
 * @param b
 * @param ipvt
 */
void solve(int n, MATRIX(a), N_TYPE *b, int *ipvt);

/**
 *
 * @param n - строчная размерность массива
 * @param a - матрица, над которой будут измываться
 * @param cond - переменная для числа обуслевленности
 * @param ipvt - вектор индексов ведущих элементов
 * @param work - вектор - одномерный рабочий массив
 */
void decomp(int n, MATRIX(a), N_TYPE *cond, int *ipvt, N_TYPE *work);

#endif