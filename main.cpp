#include <iostream>
#include <math.h>
#include "Calc/lib/rkf45.cpp"
#include "Calc/lib/quanc8.cpp"
#include "Calc/lib/fmin.cpp"
#include "MATRIX.CPP"
#include "regex.h"

#define matrixSize 4

using namespace ::std;

//Исходные параметры
const int K_FROM = 36, K_TO = 46;
double x[] = {0.0, 0.303, -0.465, 0.592, -0.409, 0.164, 0.180};
double t[] = {0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
const int nodeDigit = 7;
const double M = 1;//Масса маятника
const double g = 9.81;
double L;//Начальная длина пружины
double K;//Жесткость пружины
double y[4];// y[0] = y, y[1] = y', y[2] = z, y[3] = z'
double dy[4];//Дифференциалы
double cond;
VECTOR(sourceAnswers, matrixSize);

//Параметры RKF45
double h = 0.4, rBottom = 0, rUp = 2.4, tOut = 0, re = 1e-8, ae = 1e-8;
int iflag = 1, n = 4;
double work[27];
int iwork[30];

//Параметры FMIN
double ERROR_FMIN = 0.0001;
int flag_fmin = 1;
double K1;


char line[] = "--------------------------------------------------\n";

//Подынтегральная функция L
void setupL() {
    L = 0.6836896 * (exp(1.0) - exp(0.0));
}


//Приведенная система ДУ
void DE(double t, double *y, double *dy) {
    dy[0] = y[1];
    dy[1] = -K / M * y[0] - g * (1 - cos(y[2])) + (L + y[0]) * (y[3] * y[3]);
    dy[2] = y[3];
    dy[3] = -g / (L + y[0]) * sin(y[2]) - 2 / (L + y[0]) * y[1] * y[3];
}


//Установка параметров RKF45
void setUpRKF45param() {
    iflag = 1;
    rBottom = 0;
    y[0] = sourceAnswers[0];
    y[1] = sourceAnswers[1];
    y[2] = sourceAnswers[2];
    y[3] = sourceAnswers[3];
}


//Поиск K при помощи fmin, расчет и вывод погрешности
double calculateFun(double k) {
    K = k;
    double sum = 0;
    printf("K = %.6f\n", K);
    for (int i = 0; i < nodeDigit; ++i) {
        setUpRKF45param();
        tOut = t[i];
        RKF45(DE, n, y, &rBottom, &tOut, &re, &ae, &iflag, work, iwork);
        sum += pow(y[0] - x[i], 2);
        printf("tout = %.1f \t ", t[i]);
        printf("x*  = %.6f \t", x[i]);
        printf("x[] = %.6f\n", y[0]);
    }
    printf("errors = %.16f\n", sum);
    printf("%s", line);
    return sum;

}


int main() {

    MATRIX(sourceMatrix);

    sourceMatrix[0][0] = 5;
    sourceMatrix[0][1] = 7;
    sourceMatrix[0][2] = 6;
    sourceMatrix[0][3] = 5;
    sourceMatrix[1][0] = 7;
    sourceMatrix[1][1] = 10;
    sourceMatrix[1][2] = 8;
    sourceMatrix[1][3] = 7;
    sourceMatrix[2][0] = 6;
    sourceMatrix[2][1] = 8;
    sourceMatrix[2][2] = 10;
    sourceMatrix[2][3] = 9;
    sourceMatrix[3][0] = 5;
    sourceMatrix[3][1] = 7;
    sourceMatrix[3][2] = 9;
    sourceMatrix[3][3] = 10;

    sourceAnswers[0] = 24;
    sourceAnswers[1] = 32;
    sourceAnswers[2] = 40;
    sourceAnswers[3] = 36;

    MATRIX(work);

    int ipvt[4];

    decomp(matrixSize, sourceMatrix, &cond, ipvt, *work);
    solve(matrixSize, sourceMatrix, sourceAnswers, ipvt);

    setUpRKF45param();

    for (int i = 0; i < matrixSize; i++) {
        printf("%f \n", sourceAnswers[i]);
    }



//    double sourceMatrix[4][4] = {
//            {5, 7, 6, 5},
//            {7, 10, 8, 7},
//            {6, 8, 10, 9},
//            {5, 7, 9, 10}
//    };
//
//    //Расчитываем и выводим значение L
//    setupL();
//    printf("L = ");
//    printf("%.10f\n", L);
//    printf(line);
//
//    //Находим K при помощи fmin
//    K = fmin(K_FROM, K_TO, calculateFun, ERROR_FMIN, K1, flag_fmin);
//
//    printf("Answer:\nK = %.6f\n", K);
//
   return 0;

}
