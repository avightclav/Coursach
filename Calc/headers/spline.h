#ifndef _SPLINES
#define _SPLINES

/**
 *
 * @param n - число заданных точек (n>2)
 * @param x - массив узлов
 * @param y - массив значений в узлах
 * @param b, c, d - массивы коэффициенто
 */

void spline(int n, double *x, double *y, double *b, double *c, double *d);

/**
 *
 * @param n - число заданных точек (n>2)
 * @param u - точка, в которой ищем значение
 * @param x - массив узлов
 * @param y - массив значений в узлах
 * @param b, c, d - массивы коэффициенто
 * @return
 */
double seval(int n, double *u,
             double *x, double *y, double *b, double *c,
             double *d);

#endif