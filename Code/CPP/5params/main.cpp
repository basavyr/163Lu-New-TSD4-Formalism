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

    //Determine the best parameter set using NO prior conditions with regards to the MOI's ordering
    // rms.SearchMIN_RMS(Lu163, energies);

    //Determine the best parameter set using TRANSVERSE wobbling regime. I2-Maximal MOI
    rms.SearchRMS_Transverse(Lu163, energies);
    // for (auto &&n : energies.TH_DATA)
    // {
    //     std::cout << n << " ";
    // }
    std::cout << "\n";
    auto endTime = std::chrono::system_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Finished computations. Process took: " << duration_ms / 1000.0 << " s";
    std::cout << "\n";
}
