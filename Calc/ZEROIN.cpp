#include <iostream>
#include <assert.h>
#include "SPLINES.H"
#include "lagrange.h"

using namespace std;

double ZEROIN(double (*FUN1)(double), double xL, double xR, double eps) {

    if (FUN1(xL) == 0)
        return xL;
    if (FUN1(xR) == 0)
        return xR;
    double xi;
    double dx = xR - xL;
    int iteration = 0;
    while (xR - xL > eps) {
        xi = (xL + xR) / 2;
        if (FUN1(xL) * FUN1(xi) < 0)
            xR = xi;
        else
            xL = xi;
        iteration = iteration + 1;
    }
    printf("EPS %.11f", eps);
    printf("\nNumber of iteration %d", iteration);
    return xi;


}

