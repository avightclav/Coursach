#include <iostream>
#include <math.h>
#include "Calc/lib/rkf45.cpp"
#include "Calc/lib/quanc8.cpp"
#include "Calc/lib/fmin.cpp"
#include "Calc/lib/spline.cpp"

using namespace ::std;

//Исходная таблица
int start = 36, xout = 46;
double x[] = {0.0, 0.303, -0.465, 0.592, -0.409, 0.164, 0.180};
double t[] = {0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
const int nodeDigit = 7;


//Параметры курсача
const double M = 1;//Масса маятника
const double g = 9.81;
double L;//Начальная длина пружины
const double divisorOfL = 0.90452424;
double K;//Жесткость пружины
double y[4];// y[0] = y, y[1] = y', y[2] = z, y[3] = z'
double dy[4];//Дифференциалы


//Параметры для QUANC8
const int down = 0, up = 1;
const double abserr = 1.0e-12, relerr = 0;
double errest, flag;
int nofun;

//Параметры RKF45
double h = 0.4, rBottom = 0, rUp = 2.4, tOut = 0, re = 1e-8, ae = 1e-8;
int iflag = 1, n = 4;
double work[27];
int iwork[30];

//FMIN
double ERROR_FMIN = 0.01;
int flag_fmin = 1;
double K1;


//Тупо лайн
char line[] = "--------------------------------------------------\n";


//Подынтегральная функция L
double funL(double x) {
    return cos(x * x);
}


//Приведенная система ДУ
void fun(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = -K / M * y[0] - g * (1 - cos(y[2])) + (L + y[0]) * (y[3] * y[3]);
    dy[2] = y[3];
    dy[3] = -g / (L + y[0]) * sin(y[2]) - 2 / (L + y[0]) * y[1] * y[3];
}


//Установка параметров RKF45
void setUpRKF45param() {
    iflag = 1;
    rBottom = 0;
    y[0] = 0;
    y[1] = 0;
    y[2] = 0;
    y[3] = 4;
}


//Перебор всех K на заданном промежутке
double calcFun(double k) {
    K = k;
    double sum = 0;
    for (int i = 0; i < nodeDigit; ++i) {
        setUpRKF45param();
        tOut = t[i];
        RKF45(fun, n, y, &rBottom, &tOut, &re, &ae, &iflag, work, iwork);
        sum += pow(y[0] - x[i], 2);
    }

    return sum;

}


int main() {
    quanc8(funL, down, up, abserr, relerr, &L, &errest, &nofun, &flag);
    L = L / divisorOfL;
    printf("L = ");
    printf("%.10f\n", L);

    K = fmin(start, xout, calcFun, ERROR_FMIN, K1, flag_fmin);
    printf("K = ");
    printf("%.2f\n", K);

    L = L / divisorOfL;

    return 0;

}
