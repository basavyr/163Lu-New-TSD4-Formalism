#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

double b_term(double I, double j, double a1, double a2, double a3, double v, double gm)
{
    auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) + 8.0 * a2 * a3 * I * j;
    auto t2 = ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1) / (j * (j + 1.0)) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm)));
    auto t3 = ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / (j * (j + 1.0)) * 2 * sqrt(3.0) * sin(gm));
    return static_cast<double>(t1 + t2 * t3);
}

double c_term(double I, double j, double a1, double a2, double a3, double v, double gm)
{
    auto t1 = ((2.0 * I - 1.0) * (a3 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a3 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * sqrt(3.0) * (sqrt(3.0) * cos(gm) + sin(gm))) - 4.0 * I * j * a3 * a3;
    auto t2 = ((2.0 * I - 1.0) * (a2 - a1) + 2.0 * j * a1) * ((2.0 * j - 1.0) * (a2 - a1) + 2.0 * I * a1 + v * (2.0 * j - 1.0) / ((j * (j + 1))) * 2.0 * sqrt(3.0) * sin(gm)) - 4.0 * I * j * a2 * a2;
    return static_cast<double>(t1 * t2);
}

int main()
{
    const double PI = 3.141592654;
    std::cout << "test the energies";
    std::cout << "\n";
    auto a1 = 1.0 / (2.0 * 73);
    auto a2 = 1.0 / (2.0 * 3);
    auto a3 = 1.0 / (2.0 * 67);
    auto v = 6.01;
    auto gm = 21 * PI / 180.0;
    std::cout << b_term(8.5, 6.5, a1, a2, a3, v, gm);
    std::cout << "\n";
    std::cout << c_term(8.5, 6.5, a1, a2, a3, v, gm);
    std::cout << "\n";
}