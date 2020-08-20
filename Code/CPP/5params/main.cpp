#include <iostream>
#include <memory>
#include <utility>

#include "./include/app.h"
#include "./include/expdata.h"
#include "./include/energies.h"
#include "./include/rms.h"

void TestEnergyFormulas()
{
    auto x = new app;
    x->~app();
    Formulas energies(0);
    std::cout << energies.E_Wobbling(1, 1, 2, 3, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.E_TSD1(2, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.E_TSD2(2, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.E_TSD3(2, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.E_TSD4(2, 3, 4, 5, 6, 7);
    std::cout << "\n";
}

int main()
{
    std::vector<double> v1 = {2, 2, 3};
    std::vector<double> v2 = v1;
    v2.emplace_back(5);
    v1.emplace_back(4);
    std::cout << rms::RMS(v1, v2) << "\n";
}
