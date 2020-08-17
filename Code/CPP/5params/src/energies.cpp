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
    auto retval = 6968.0;
    if (retval + 1 == error_number)
        return 1;
    return 0;
}

double Formulas::Omega2(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto retval = 6968.0;
    if (retval + 1 == error_number)
        return 1;
    return 0;
}

double Formulas::BTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto A1 = InertiaFactor(i1);
    auto A2 = InertiaFactor(i2);
    auto A3 = InertiaFactor(i3);
    auto j = oddSpin;
    auto I = spin;
    //Transform gamma into radians (from degrees)
    auto gm = gamma * PI / 180.0;

    if (debug)
    {
        std::cout << I << " " << j;
        std::cout << "\n";
        std::cout << A1 << " " << A2 << " " << A3;
        std::cout << "\n";
        std::cout << gm;
        std::cout << "\n";
    }
    return 1;
}