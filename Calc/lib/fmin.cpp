// fmin.cpp
/*
			
		���� �������� ������� fmin, ������� ������� �������� ����� ����� ��������
		������� ����� ����������.�����: ������� ����. ������ 2081/2
*/

#include<math.h>

double fmin(double beg,                        // ������ ��������� ������
            double end,                            // ����� ��������� ������
            double (*f)(double x),                // �������� �������
            double Tol,                            // �����������
            double &Count,                        // �������� ������� � ����� ��������
            int &flag)                            // ����
{
    double BegBuf = f(beg),                        // �������� ������� � ������ ���������
            EndBuf = f(end),                        // �������� ������� � ������ ���������
            Lcenter, Rcenter, Lfcenter, Rfcenter;    // ���������� �����
    int counter = 0;                                // �������
    int maxcounts = 500;                            // ������������ ����� ��������

    flag = 0;




    // ����� ������������ �������� �� �������
    do {
        // ������ �������� ���������
        Lcenter = (end + beg - Tol) / 2;
        Lfcenter = f(Lcenter);

        Rcenter = (end + beg + Tol) / 2;
        Rfcenter = f(Rcenter);
        if (Lfcenter < Rfcenter) {
            end = Rcenter;
            EndBuf = Rfcenter;
        }

            // ����� ������ ���������
        else if (Lfcenter > Rfcenter) {
            beg = Lcenter;
            BegBuf = Lfcenter;
        } else {
            return (Lcenter + Rcenter) / 2;
        }

        // ������ ������� ������
        if (fabs(end - beg) < 2 * Tol) {
            Lcenter = (end + beg) / 2;
            Count = f(Lcenter);
            return Lcenter;
        }

        counter++;
    } while (counter < maxcounts);

    flag = 1;
    return end;

}