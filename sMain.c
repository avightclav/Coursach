//
// Created by Danila Eremenko on 11.04.2018.
//

#include "Forsythe.h"
#include<iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const Float g = 9.81;
const Float M = 1.;
const Float EPS = 0.00001;
Float K;

Float myFunctIntegr1(Float x) //функция для вычисления интеграла для L
{
    return (cos(x*x))/0.90452424;
}
Float errest, flag;
int nofun;
float res = 0;
Float L = Quanc8(myFunctIntegr1, 0, 1, 1.0e-6, res, &errest, &nofun, &flag); //вычисление значения L

void MyFunc(Float t, Float *y, Float *dy) //система дифференциальных уравнений в нормированном виде
{

    dy[0] = y[1];
    dy[1] = -K*y[0]/M - g*(1 - cos(y[2])) + (L + y[0])*y[3]*y[3];
    dy[2] = y[3];
    dy[3] = -g*sin(y[2])/(L + y[0]) - 2*y[1]*y[3]/(L + y[0]);
}

Float averageQuadSumm(Float K) //функция вычисления среднеквадратичного критерия
{
    ::K = K;

    Float y0[] = {0, 0, 0, 4};//начальные значения
    Float t = 0;
    Float x[] = {0, 0.303, -0.465, 0.592, -0.409, 0.164, 0.180};//экспериментальные значения удлинения пружины

    unsigned char work[6*(4*sizeof(Float)) + sizeof(rkf_inside)];
    rkf_inside *p;

    rkf myRKF;
    myRKF.f = MyFunc;
    myRKF.Y = y0;
    myRKF.t = t;
    myRKF.tout = 0;
    myRKF.ae = EPS;
    myRKF.re = EPS;
    myRKF.neqn = 4;
    myRKF.flag = 1;
    myRKF.work = work;
    p = (rkf_inside *)myRKF.work;
    Float tout = 0;

    Float summ = 0; //среднеквадратичный критерий
    for (int i = 0; i < 7; i++)
    {
        rkf45(&myRKF);
        cout << "tout = " << setw(3) << myRKF.tout <<  " x* = " << setw(9) << myRKF.Y[0] << " x[] = " << setw(5) << x[i] << endl;
        summ += ( (myRKF.Y[0] - x[i]) * (myRKF.Y[0] - x[i]) );

        myRKF.tout += 0.4;
    }
    return summ;
}

int main()
{
    Float K = FMin(averageQuadSumm, 36, 46, 0.0001);//жесткость пружины
    std::cout << K << '\n';
    system("pause");


    return 0;
}

