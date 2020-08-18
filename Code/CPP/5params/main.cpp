#include <iostream>
#include <memory>
#include <utility>

#include "./include/app.h"
#include "./include/expdata.h"
#include "./include/energies.h"

int main()
{
    auto x = new app;
    x->~app();
    Formulas energies(0);
    // std::cout << energies.BTerm(2, 3, 3, 4, 5, 6, 7);
    std::cout << energies.Hmin(2, 3, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.Omega1(2, 3, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.Omega2(2, 3, 3, 4, 5, 6, 7);
    std::cout << "\n";
}