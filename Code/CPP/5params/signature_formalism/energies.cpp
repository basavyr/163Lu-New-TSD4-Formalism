#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const double PI = 3.141592654;
const double spin0 = 6.5;
const double j_0 = 6.5;

struct OmegaTuple
{
    double omega1, omega2;
};

double b_term(double I, double j, double a1, double a2, double a3, double v, double gm)
{
    auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) + 8.0 * a2 * a3 * I * j;
    auto t2 = ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1) / (j * (j + 1.0)) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm)));
    auto t3 = ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / (j * (j + 1.0)) * 2 * sqrt(3.0) * sin(gm));
    return static_cast<double>((t1 + t2 * t3) * (-1.0));
}

double c_term(double I, double j, double a1, double a2, double a3, double v, double gm)
{
    auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm))) - 4.0 * I * j * a3 * a3;
    auto t2 = ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * 2.0 * sqrt(3.0) * sin(gm)) - 4.0 * I * j * a2 * a2;
    return static_cast<double>(t1 * t2);
}

double h_min(double I, double j, double a1, double a2, double a3, double v, double gm)
{
    auto hmin = (a2 + a3) * (I + j) * 0.5 + a1 * pow(I - j, 2) - v * (2.0 * j - 1.0) / (j + 1) * sin(gm + (PI / 6));
    return static_cast<double>(hmin);
}

OmegaTuple Omega(double I, double j, double a1, double a2, double a3, double v, double gm)
{
    OmegaTuple result;
    auto B = b_term(I, j, a1, a2, a3, v, gm);
    auto C = c_term(I, j, a1, a2, a3, v, gm);
    result.omega1 = sqrt(0.5 * (-B - sqrt(B * B - 4.0 * C)));
    result.omega2 = sqrt(0.5 * (-B + sqrt(B * B - 4.0 * C)));
    return result;
}

double Energy(int n1, int n2, double I, double j, double a1, double a2, double a3, double v, double gm)
{
    auto omega = Omega(I, j, a1, a2, a3, v, gm);
    double E = h_min(I, j, a1, a2, a3, v, gm) + omega.omega1 * (n1 + 0.5) + omega.omega2 * (n2 + 0.5);
    return E;
}

double TSD1(double I, double j, double a1, double a2, double a3, double v, double gm)
{

    double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
    double E = Energy(0, 0, I, j, a1, a2, a3, v, gm);
    return E - E_0;
}

double TSD2(double I, double j, double a1, double a2, double a3, double v, double gm)
{

    double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
    double E = Energy(1, 0, I - 1.0, j, a1, a2, a3, v, gm);
    return E - E_0;
}

double TSD3(double I, double j, double a1, double a2, double a3, double v, double gm)
{

    double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
    double E = Energy(2, 0, I - 2.0, j, a1, a2, a3, v, gm);
    return E - E_0;
}

double TSD4_00(double I, double j, double a1, double a2, double a3, double v, double gm)
{

    double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
    double E = Energy(0, 0, I, j, a1, a2, a3, v, gm);
    return E - E_0;
}

double TSD4_10(double I, double j, double a1, double a2, double a3, double v, double gm)
{

    double E_0 = Energy(0, 0, spin0, j_0, a1, a2, a3, v, gm);
    double E = Energy(1, 0, I - 1.0, j, a1, a2, a3, v, gm);
    return E - E_0;
}

int main()
{

    std::cout << "test the energies";
    std::cout << "\n";
    auto a1 = 1.0 / (2.0 * 73);
    auto a2 = 1.0 / (2.0 * 3);
    auto a3 = 1.0 / (2.0 * 67);
    auto v = 6.01;
    auto gm = 21 * PI / 180.0;
    std::vector<double> spins = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
    for (auto &&n : spins)
    {
        std::cout << n << " " << TSD1(n, j_0, a1, a2, a3, v, gm) << " " << TSD2(n, j_0, a1, a2, a3, v, gm) << " " << TSD3(n, j_0, a1, a2, a3, v, gm) << " " << TSD4_00(n, j_0, a1, a2, a3, v, gm) << " " << TSD4_10(n, j_0, a1, a2, a3, v, gm) << "\n";
    }
    std::cout << "\n";
}