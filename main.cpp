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
//double rightX[] = {0, 0.303, -0.465, 0.592, -0.409, 0.164, 0.180};

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

//Тупо лайн
char line[] = "--------------------------------------------------";

//Параметры узла
double awaitedX;
double rightX;
double rightK;
double errors;
double current_tOut = 0;


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
void setUp() {
    iflag = 1;
    rBottom = 0;
    tOut = current_tOut;
    y[0] = 0;
    y[1] = 0;
    y[2] = 0;
    y[3] = 4;
}


//Установка текущего узла таблцы
void setUpNode(double sAwaitedX, double sRightX, double sRightK) {
    awaitedX = sAwaitedX;
    rightX = sRightX;
    rightK = sRightK;


}


//Перебор всех K на заданном промежутке
void callRKF45() {
    for (K = 36; K < 46; K += 0.01) {
        setUp();
        tOut = current_tOut;
        RKF45(fun, n, y, &rBottom, &tOut, &re, &ae, &iflag, work, iwork);
        if (abs(y[0] - awaitedX) < abs(rightX - awaitedX)) {
            rightX = y[0];
            rightK = K;
        }
        errors = abs(y[0] - awaitedX);

        //printf("%.10f    %f\n", y[0], K);

    }
    printf(line);
    printf("\n");
    printf("%.10f\n", rightK);
    printf("%.10f\n", rightX);

}


int main() {
    quanc8(funL, down, up, abserr, relerr, &L, &errest, &nofun, &flag);
    L = L / divisorOfL;
    printf("L = ");
    printf("%.10f\n", L);


    current_tOut = 0.0;
    setUpNode(0.0, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);


    current_tOut = 0.4;
    setUpNode(0.303, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);


    current_tOut = 0.8;
    setUpNode(-0.465, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);

    current_tOut = 1.2;
    setUpNode(0.592, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);


    current_tOut = 1.6;
    setUpNode(-0.409, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);


    current_tOut = 2.0;
    setUpNode(0.164, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);


    current_tOut = 2.4;
    setUpNode(0.180, 10, 0);
    callRKF45();
    printf("errors = \n");
    printf("%.10f\n", errors);


    return 0;

}
