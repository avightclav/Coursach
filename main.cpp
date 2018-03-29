#include <iostream>
#include <math.h>
#include "Calc/lib/rkf45.cpp"
#include "Calc/lib/quanc8.cpp"

using namespace ::std;
//Параметры курсача
const double M = 1;//Масса маятника
const double g = 9.81;
double L;//Начальная длина пружины
const double divisorOfL = 0.90452424;
double K;//Жесткость пружины
double y[4];// y[0] = y, y[1] = y', y[2] = z, y[3] = z'
double dy[4];//Дифференциалы
double rightX[] = {0, 0.303, -0.465, 0.592, -0.409, 0.164, 0.180};


//Переменные для QUANC8
const int down = 0, up = 1;
const double abserr = 1.0e-12, relerr = 0;
double errest, flag;
int nofun;


//RKF45
double h = 0.4, rBottom = 0, rUp = 2.4, tOut = 0, re = 1e-8, ae = 1e-8;
int iflag = 1, n = 4;
double work[15];
int iwork[30];

//Тупо лайн
char line[] = "--------------------------------------------------";


double funL(double x) {
    return cos(x * x);
}


void setUp() {
    quanc8(funL, down, up, abserr, relerr, &L, &errest, &nofun, &flag);
    L = L / divisorOfL;
    y[0] = 0;
    y[1] = 0;
    y[2] = 0;
    y[3] = 4;
}


void fun(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = -K / M * y[0] - g * (1 - cos(y[2])) + (L + y[0]) * y[3] * y[3];
    dy[2] = y[3];
    dy[3] = -g / (L + y[0]) * sin(y[2]) - 2 / (L + y[0]) * y[1] * y[3];
}


int main() {
    setUp();
    printf("%.10f\n", L);


    for (K = 36; K < 46; K += 0.01) {
        tOut = 1.2;
        RKF45(fun, n, y, &rBottom, &tOut, &re, &ae, &iflag, work, iwork);
        printf("%.10f    %f\n", y[0], K);

    }


    return 0;

}
