#include <iostream>
#include <memory>
#include <utility>

#include "./include/app.h"
// #include "./include/expdata.h"
// #include "./include/energies.h"
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
    // TestEnergyFormulas();
    expdata Lu163;
    std::cout << "Initializing rms class...";
    std::cout << "\n";
    auto startTime = std::chrono::system_clock::now();
    rms rms;
    std::cout << "Starting to search for the minimum RMS...";
    std::cout << "\n";
    rms.SearchMIN_RMS(Lu163);
    auto endTime = std::chrono::system_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Finished computations. Process took: " << duration_ms / 1000.0 << " s";
    std::cout << "\n";
}
