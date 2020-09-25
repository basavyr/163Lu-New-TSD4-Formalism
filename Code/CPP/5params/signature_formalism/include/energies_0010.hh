#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Bands_0010
{
public:
    struct OmegaTuple
    {
        double omega1, omega2;
        OmegaTuple()
        {
        }
        OmegaTuple(double x)
        {
            omega1 = x;
            omega2 = x;
        }
    };

    const double PI = 3.141592654;
    const double spin0 = 6.5;
    const double j_0 = 6.5;
    const double error_checker = 6969;
    const OmegaTuple FAILED_OMEGAS = OmegaTuple(error_checker);

    int valid(double number)
    {
        if (!isnan(number) && number != error_checker)
            return 1;
        return 0;
    }

    double b_term(double I, double j, double a1, double a2, double a3, double v, double gm)
    {
        auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) + 8.0 * a2 * a3 * I * j;
        if (!valid(t1))
            return error_checker;
        auto t2 = ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1) / (j * (j + 1.0)) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm)));
        if (!valid(t2))
            return error_checker;
        auto t3 = ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / (j * (j + 1.0)) * 2 * sqrt(3.0) * sin(gm));
        if (!valid(t3))
            return error_checker;
        return static_cast<double>((t1 + t2 * t3) * (-1.0));
    }

    double c_term(double I, double j, double a1, double a2, double a3, double v, double gm)
    {
        auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm))) - 4.0 * I * j * a3 * a3;
        if (!valid(t1))
            return error_checker;
        auto t2 = ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * 2.0 * sqrt(3.0) * sin(gm)) - 4.0 * I * j * a2 * a2;
        if (!valid(t2))
            return error_checker;
        return static_cast<double>(t1 * t2);
    }

    double h_min(double I, double j, double a1, double a2, double a3, double v, double gm)
    {
        auto hmin = (a2 + a3) * (I + j) * 0.5 + a1 * pow(I - j, 2) - v * (2.0 * j - 1.0) / (j + 1) * sin(gm + (PI / 6));
        if (!valid(hmin))
            return error_checker;
        return static_cast<double>(hmin);
    }

    OmegaTuple Omega(double I, double j, double a1, double a2, double a3, double v, double gm)
    {
        OmegaTuple result;
        auto B = b_term(I, j, a1, a2, a3, v, gm);
        if (!valid(B))
            return FAILED_OMEGAS;
        auto C = c_term(I, j, a1, a2, a3, v, gm);
        if (!valid(C))
            return FAILED_OMEGAS;
        result.omega1 = sqrt(0.5 * (-B - sqrt(B * B - 4.0 * C)));
        result.omega2 = sqrt(0.5 * (-B + sqrt(B * B - 4.0 * C)));
        return result;
    }

    double Energy(int n1, int n2, double I, double j, double a1, double a2, double a3, double v, double gm)
    {
        auto omega = Omega(I, j, a1, a2, a3, v, gm);
        if (!valid(omega.omega1) && !valid(omega.omega2))
            return error_checker;
        double E = h_min(I, j, a1, a2, a3, v, gm) + omega.omega1 * (n1 + 0.5) + omega.omega2 * (n2 + 0.5);
        if (!valid(E))
            return error_checker;
        return E;
    }

    double TSD1(double I, double a1, double a2, double a3, double v, double gm)
    {
        double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(0, 0, I, j_0, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }

    double TSD2(double I, double a1, double a2, double a3, double v, double gm)
    {
        double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(0, 0, I, j_0, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }

    double TSD3(double I, double a1, double a2, double a3, double v, double gm)
    {

        double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(1, 0, I - 1.0, j_0, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }

    double TSD4(double I, double a1, double a2, double a3, double v, double gm)
    {
        const double j_2 = 6.5;
        double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(0, 0, I, j_2, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }
};
