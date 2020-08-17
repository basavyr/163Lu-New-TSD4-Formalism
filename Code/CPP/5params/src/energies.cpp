#include "../include/energies.h"

Formulas::Formulas(bool ok)
{
    debug = ok;
}

Formulas::~Formulas()
{
    // if (debug)
    //     std::cout << debug_ON;
    // else
    // {
    //     std::cout << debug_OFF;
    // }
}

int Formulas::ValidNumbers(double number)
{
    if (isnan(number) || number == error_number)
        return 0;
    return 1;
}

double Formulas::InertiaFactor(double I)
{
    if (I == 0)
        return error_number;
    return 1.0 / (2.0 * I);
}

double Formulas::Omega1(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    return 0;
}

double Formulas::Omega2(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    return 0;
}

double Formulas::BTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto A1 = InertiaFactor(i1);
    auto A2 = InertiaFactor(i2);
    auto A3 = InertiaFactor(i3);
    if (!ValidNumbers(A1) || !ValidNumbers(A2) || !ValidNumbers(A3))
        return error_number;
    auto j = oddSpin;
    auto I = spin;
    //Transform gamma into radians (from degrees)
    auto gm = gamma * PI / 180.0;
    auto T1 = ((2.0 * I - 1.0) * (A3 - A1) + 2.0 * j * A1);
    auto T2 = ((2.0 * I - 1.0) * (A2 - A1) + 2.0 * j * A1);
    if (!ValidNumbers(T1) || !ValidNumbers(T2))
        return error_number;
    auto T3 = T1 * T2 + 8.0 * A2 * A3 * I * j;
    auto T4 = ((2.0 * j - 1.0) * (A3 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / (j * (j + 1.0)) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm)));
    auto T5 = ((2.0 * j - 1.0) * (A2 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / (j * (j + 1.0)) * 2.0 * sqrt(3.0) * sin(gm));
    if (!ValidNumbers(T3) || !ValidNumbers(T4) || !ValidNumbers(T5))
        return error_number;
    auto B = static_cast<double>(T3 + T4 * T5);
    if (!ValidNumbers(B))
        return error_number;
    if (debug)
    {
        std::cout << A1 << " " << A2 << " " << A3;
        std::cout << "\n";
        std::cout << gm;
        std::cout << "\n";
        std::cout << "T1= " << T1 << "\n";
        std::cout << "T2= " << T2 << "\n";
        std::cout << "T3= " << T3 << "\n";
        std::cout << "T4= " << T4 << "\n";
        std::cout << "T5= " << T5 << "\n";
    }
    return -B;
}

double Formulas::CTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto A1 = InertiaFactor(i1);
    auto A2 = InertiaFactor(i2);
    auto A3 = InertiaFactor(i3);
    if (!ValidNumbers(A1) || !ValidNumbers(A2) || !ValidNumbers(A3))
        return error_number;
    auto j = oddSpin;
    auto I = spin;
    //Transform gamma into radians (from degrees)
    auto gm = gamma * PI / 180.0;
    auto T1 = ((2.0 * I - 1.0) * (A3 - A1) + 2.0 * j * A1) * ((2.0 * j - 1.0) * (A3 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / (j * (j + 1.0)) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm))) - 4.0 * I * j * pow(A3, 2);
    auto T2 = ((2.0 * I - 1.0) * (A2 - A1) + 2.0 * j * A1) * ((2.0 * j - 1.0) * (A2 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / (j * (j + 1.0)) * 2.0 * sqrt(3.0) * sin(gm)) - 4.0 * I * j * pow(A2, 2);
    if (!ValidNumbers(T1) || !ValidNumbers(T2))
        return error_number;
    auto C = T1 * T2;
    if (debug)
    {
        std::cout << A1 << " " << A2 << " " << A3;
        std::cout << "\n";
        std::cout << gm;
        std::cout << "\n";
        std::cout << "T1= " << T1 << "\n";
        std::cout << "T2= " << T2 << "\n";
    }
    return C;
}

double Formulas::Hmin(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto A1 = InertiaFactor(i1);
    auto A2 = InertiaFactor(i2);
    auto A3 = InertiaFactor(i3);
    if (!ValidNumbers(A1) || !ValidNumbers(A2) || !ValidNumbers(A3))
        return error_number;
    auto j = oddSpin;
    auto I = spin;
    //Transform gamma into radians (from degrees)
    auto gm = gamma * PI / 180.0;
    auto H = (A2 + A3) * 0.5 * (I + j) + A1 * pow(I - j, 2) - V * (2.0 * j - 1.0) / (j + 1.0) * sin(gm + PI / 6.0);
    if (!ValidNumbers(H))
        return error_number;
    return H;
}