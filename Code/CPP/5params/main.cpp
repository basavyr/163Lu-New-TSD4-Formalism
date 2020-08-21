#include <iostream>
#include <memory>
#include <utility>

// #include "./include/app.h"
// #include "./include/expdata.h"
// #include "./include/energies.h"
#include "./include/rms.h"

int main()
{
    expdata Lu163;
    Formulas energies(0);
    std::cout << "Initializing rms class...";
    std::cout << "\n";
    auto startTime = std::chrono::system_clock::now();
    rms rms;
    std::cout << "Starting to search for the minimum RMS...";
    std::cout << "\n";
    rms.SearchMIN_RMS(Lu163, energies);
    auto endTime = std::chrono::system_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Finished computations. Process took: " << duration_ms / 1000.0 << " s";
    std::cout << "\n";
}
