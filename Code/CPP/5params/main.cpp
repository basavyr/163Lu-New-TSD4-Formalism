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
    // std::cout << energies.E_Wobbling(1, 1, 2, 3, 3, 4, 5, 6, 7);
    // std::cout << "\n";
    // std::cout << energies.E_TSD1(2, 3, 4, 5, 6, 7);
    // std::cout << "\n";
    // std::cout << energies.E_TSD2(2, 3, 4, 5, 6, 7);
    // std::cout << "\n";
    // std::cout << energies.E_TSD3(2, 3, 4, 5, 6, 7);
    // std::cout << "\n";
    std::cout << energies.E_TSD4_00(2, 3, 4, 5, 6, 7);
    std::cout << "\n";
    std::cout << energies.E_TSD4_30(2, 3, 4, 5, 6, 7);
    std::cout << "\n";
}

int main()
{
    TestEnergyFormulas();
    rms rms;
    rms.SearchMIN_RMS();
}
