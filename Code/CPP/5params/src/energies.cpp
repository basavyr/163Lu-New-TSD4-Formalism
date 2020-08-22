// #include "../include/energies.h"
// #include "../include/expdata.h"
#include "../include/rms.h"

Formulas::Formulas(bool ok)
{
    debug = ok;
}

Formulas::~Formulas()
{
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

double Formulas::Omega1(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto B = BTerm(spin, oddSpin, i1, i2, i3, V, gamma);
    auto C = CTerm(spin, oddSpin, i1, i2, i3, V, gamma);
    if (!ValidNumbers(B) || !ValidNumbers(B))
        return error_number;
    auto Delta = sqrt(pow(B, 2) - 4.0 * C);
    if (!ValidNumbers(Delta))
        return error_number;
    //The first wobbling frequency has a MINUS sign
    auto Omega = sqrt(0.5 * (-B - Delta));
    if (!ValidNumbers(Omega))
        return error_number;
    return Omega;
}

double Formulas::Omega2(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto B = BTerm(spin, oddSpin, i1, i2, i3, V, gamma);
    auto C = CTerm(spin, oddSpin, i1, i2, i3, V, gamma);
    if (!ValidNumbers(B) || !ValidNumbers(B))
        return error_number;
    auto Delta = sqrt(pow(B, 2) - 4.0 * C);
    if (!ValidNumbers(Delta))
        return error_number;
    //The second wobbling frequency has a PLUS sign
    auto Omega = sqrt(0.5 * (-B + Delta));
    if (!ValidNumbers(Omega))
        return error_number;
    return Omega;
}

double Formulas::E_Wobbling(int n1, int n2, double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma)
{
    auto om1 = Omega1(spin, oddSpin, i1, i2, i3, V, gamma);
    auto om2 = Omega2(spin, oddSpin, i1, i2, i3, V, gamma);
    auto H = Hmin(spin, oddSpin, i1, i2, i3, V, gamma);
    if (!ValidNumbers(om1) || !ValidNumbers(om2) || !ValidNumbers(H))
        return error_number;
    //the formula for the excitation energy, in terms of Omega1,Omega2 and the minimum energy H_min
    auto E = om1 * (n1 + 0.5) + om2 * (n2 + 0.5) + H;
    if (!ValidNumbers(E))
        return error_number;
    return E;
}

double Formulas::E_TSD1(double spin, double i1, double i2, double i3, double V, double gamma)
{
    auto E0 = E_Wobbling(0, 0, expdata::yrastSpin, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    auto E1 = E_Wobbling(0, 0, spin, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    if (!ValidNumbers(E0) || !ValidNumbers(E1))
        return error_number;
    return static_cast<double>(E1 - E0);
}

double Formulas::E_TSD2(double spin, double i1, double i2, double i3, double V, double gamma)
{
    auto E0 = E_Wobbling(0, 0, expdata::yrastSpin, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    auto E1 = E_Wobbling(1, 0, spin - 1.0, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    if (!ValidNumbers(E0) || !ValidNumbers(E1))
        return error_number;
    return static_cast<double>(E1 - E0);
}

double Formulas::E_TSD3(double spin, double i1, double i2, double i3, double V, double gamma)
{
    auto E0 = E_Wobbling(0, 0, expdata::yrastSpin, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    auto E1 = E_Wobbling(2, 0, spin - 2.0, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    if (!ValidNumbers(E0) || !ValidNumbers(E1))
        return error_number;
    return static_cast<double>(E1 - E0);
}

double Formulas::E_TSD4_00(double spin, double i1, double i2, double i3, double V, double gamma)
{
    auto E0 = E_Wobbling(0, 0, expdata::yrastSpin, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    //use the same intruder in the I=R+j coupling scheme
    auto j = expdata::oddSpin_1;

    auto E1 = E_Wobbling(0, 0, spin, j, i1, i2, i3, V, gamma);

    if (!ValidNumbers(E1))
        return error_number;
    return static_cast<double>(E1 - E0);
}

double Formulas::E_TSD4_30(double spin, double i1, double i2, double i3, double V, double gamma)
{
    auto E0 = E_Wobbling(0, 0, expdata::yrastSpin, expdata::oddSpin_1, i1, i2, i3, V, gamma);
    //use the same intruder in the I=R+j coupling scheme
    auto j = expdata::oddSpin_1;

    auto E1 = E_Wobbling(3, 0, spin, j, i1, i2, i3, V, gamma);

    if (!ValidNumbers(E1))
        return error_number;
    return static_cast<double>(E1 - E0);
}
