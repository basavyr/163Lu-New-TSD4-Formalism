#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

class Bands
{
public:
    const double PI = 3.141592654;
    const double spin0 = 6.5;
    const double j = 6.5;
    const double error_checker = 6969;

    int valid(double number)
    {
        if (!isnan(number) && number != error_checker)
            return 1;
        return 0;
    }

    //Gamma in radians!
    double b_term(double I, double a1, double a2, double a3, double v, double gm)
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

    //Gamma in radians!
    double c_term(double I, double a1, double a2, double a3, double v, double gm)
    {
        auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm))) - 4.0 * I * j * a3 * a3;
        if (!valid(t1))
            return error_checker;
        auto t2 = ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * 2.0 * sqrt(3.0) * sin(gm)) - 4.0 * I * j * a2 * a2;
        if (!valid(t2))
            return error_checker;
        return static_cast<double>(t1 * t2);
    }

    //Gamma in radians!
    double h_min(double I, double a1, double a2, double a3, double v, double gm)
    {
        auto hmin = (a2 + a3) * (I + j) * 0.5 + a1 * pow(I - j, 2) - v * (2.0 * j - 1.0) / (j + 1) * sin(gm + (PI / 6));
        if (!valid(hmin))
            return error_checker;
        return static_cast<double>(hmin);
    }

    //Gamma in radians!
    double Omega1(double I, double a1, double a2, double a3, double v, double gm)
    {
        auto B = b_term(I, a1, a2, a3, v, gm);
        if (!valid(B))
            return error_checker;
        auto C = c_term(I, a1, a2, a3, v, gm);
        if (!valid(C))
            return error_checker;
        auto omega1 = static_cast<double>(sqrt(0.5 * (-B - sqrt(B * B - 4.0 * C))));
        return omega1;
    }

    //Gamma in radians!
    double Omega2(double I, double a1, double a2, double a3, double v, double gm)
    {
        auto B = b_term(I, a1, a2, a3, v, gm);
        if (!valid(B))
            return error_checker;
        auto C = c_term(I, a1, a2, a3, v, gm);
        if (!valid(C))
            return error_checker;
        auto omega2 = static_cast<double>(sqrt(0.5 * (-B + sqrt(B * B - 4.0 * C))));
        return omega2;
    }

    //The general formula of the Wobbling Energy for a triaxial band in $^{163}$Lu
    //Phonon excitation numbers n1 and n2 represent the core and particle effects, respectively
    //gamma in radians!
    double Energy(int n1, int n2, double I, double a1, double a2, double a3, double v, double gm)
    {
        //First Wobbling Phonon Energy Omega1
        auto omega1 = Omega1(I, a1, a2, a3, v, gm);

        //Second Wobbling Phonon Energy Omega2
        auto omega2 = Omega2(I, a1, a2, a3, v, gm);

        if (!valid(omega1) && !valid(omega2))
            return error_checker;
        double E = h_min(I, a1, a2, a3, v, gm) + omega1 * (n1 + 0.5) + omega2 * (n2 + 0.5);
        if (!valid(E))
            return error_checker;
        return E;
    }

    double TSD1(double I, double a1, double a2, double a3, double v, double gm)
    {
        double E_0 = Energy(0, 0, spin0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(0, 0, I, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }

    //TSD2 is the 0-phonon excited band of the nucleus: ground state band
    double TSD2(double I, double a1, double a2, double a3, double v, double gm)
    {
        double E_0 = Energy(0, 0, spin0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(0, 0, I, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }

    //TSD3 is the 1-phonon excited band of the nucleus
    double TSD3(double I, double a1, double a2, double a3, double v, double gm)
    {

        double E_0 = Energy(0, 0, spin0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;
        double E = Energy(1, 0, I - 1.0, a1, a2, a3, v, gm);
        if (!valid(E))
            return error_checker;
        return E - E_0;
    }

    //approach B1 (from the UNIFIED MODEL)
    //TSD4 is a 0-phonon excitation built on top of TSD1, being the chiral partner of TSD1
    //TSD4 is in fact a ground-state band
    double TSD4(double I, double a1, double a2, double a3, double v, double gm, double SHIFT)
    {
        double E_0 = Energy(0, 0, spin0, a1, a2, a3, v, gm);
        if (!valid(E_0))
            return error_checker;

        //adds the shift to the overall Absolute Energy Value (before normallizing it to the excitation value)
        double E = Energy(0, 0, I, a1, a2, a3, v, gm) + SHIFT;

        if (!valid(E))
            return error_checker;
        return E - E_0;
    }
};