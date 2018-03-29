// quanc8.h

#ifndef _QUANC8
#define _QUANC8

/**
 *
 * @param FUN - вычисляемая функция
 * @param A - нижний предел
 * @param B - верхний предел (мб меньше А)
 * @param ABSERR - граница абсолютной погрешности (не отрицательное число)
 * @param RELERR - граница относительной погрешности (не отрицательное число)
 * @param RESULT - результат
 * @param ERREST - оценка величины действительной ошибки
 * @param NOFUN - число значений функции, использованных при вычислении RESULT
 * @param FLAG - индикатор надежности. Если FLAG равен нулю, то RESULT, вероятно,
 * удовлетворяет заданной границе погрешности. Если FLAG=XXX.YYY, то XXX=число
 * интервалов, для, которых не было сходимости, a O.YYY часть основного интервала.
 * Оставшаяся для обработки в тот момент, когда программа приблизилась к предельному
 * значению для NOFUN.
 */
void quanc8(double (*FUN)(double), double A, double B, double ABSERR,
            double RELERR, double *RESULT, double *ERREST, int *NOFUN, double *FLAG);

#endif