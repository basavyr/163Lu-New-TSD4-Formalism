#include <iostream>
#include <memory>
#include <utility>

// #include "./include/app.h"
// #include "./include/expdata.h"
// #include "./include/energies.h"
#include "./include/rms.h"

//Declaring the experimental data set for Lu163
expdata Lu163;

//Class with the analytic formulas used into RMS computations
Formulas energies(0);

void RunApp_OMP(double &exec_time, int Phonon_Selector, double gamma)
{
    // std::cout << "Initializing rms class...";
    // std::cout << "\n";
    std::cout << "Searching for the minimal RMS value using the fixed array procedure."
              << "\n";
    std::cout << "TSD4: (" << Phonon_Selector << ",0)\n";

    auto startTime = std::chrono::system_clock::now();
    rms rms;

    //look for 1-moi ordering only
    //change this value if the maximal moi should be along the other two axes
    int max_moi = 1;

    //Determine the best parameter set using TRANSVERSE wobbling regime. max_moi = Maximal MOI
    rms.SearchRMS_OMP(Phonon_Selector, max_moi);

    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count();
    std::cout << "Finished computations. Process took: " << duration_ms / 1000.0 << " s";
    std::cout << "\n";
    exec_time = static_cast<double>(duration_ms / 1000.0);
}

void RunApp_DirectComputation(double &exec_time)
{
    // std::cout << "Initializing rms class...";
    // std::cout << "\n";
    auto startTime = std::chrono::system_clock::now();
    rms rms;
    std::cout << "Starting to search for the minimum RMS...";
    std::cout << "\n";

    //Determine the best parameter set using TRANSVERSE wobbling regime. I2-Maximal MOI
    rms.SearchRMS_DirectComputation(Lu163, energies);

    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count();
    std::cout << "Finished computations. Process took: " << (duration_ms / 1000.0) << " s";
    std::cout << "\n";
    exec_time = static_cast<double>(duration_ms / 1000.0);
}

int main()
{

    double exec_proc1 = 0;
    std::vector<double> spins = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
    auto I1 = 73.0;
    auto I2 = 3.0;
    auto I3 = 67.0;
    auto V = 6.01;
    auto gm = 21.0;
    std::cout << energies.BTerm(8.5, 6.5, I1, I2, I3, V, gm) << "\n";
    std::cout << energies.CTerm(8.5, 6.5, I1, I2, I3, V, gm);
    // for (auto &&n : spins)
    // {
    //     auto e1 = energies.E_TSD1(n, I1, I2, I3, V, gm);
    //     auto e2 = energies.E_TSD2(n, I1, I2, I3, V, gm);
    //     auto e3 = energies.E_TSD3(n, I1, I2, I3, V, gm);
    //     std::cout << n << " " << e1 << " " << e2 << " " << e3 << "\n";
    // }
    // RunApp_OMP(exec_proc1, 0, 17);
    // RunApp_OMP(exec_proc1, 1, 17);

    // std::cout << "\n";
    // std::cout << "#############################"
    //           << "\n";
    // std::cout << "#############################"
    //           << "\n";
    // std::cout << "\n";

    // std::cout << "Searching for the minimal RMS value using the fixed array procedure.";
    // std::cout << "\n";
    // std::cout << "TSD4:  (1,0)";
    // std::cout << "\n";

    // RunApp_FixedArray(exec_proc1, 1);

    // std::cout << "Searching for the minimal RMS value using the direct computation method.";
    // std::cout << "\n";

    // double exec_proc2 = 0;
    // RunApp_DirectComputation(exec_proc2);

    // // auto improvement = (std::max(exec_proc1, exec_proc2) == exec_proc2) ? (static_cast<double>(exec_proc1 / exec_proc2)) : (static_cast<double>(exec_proc2 / exec_proc1));
    // auto improvement = (static_cast<double>(exec_proc2 / exec_proc1));
    // std::cout << "Time improvement: " << improvement;
    // std::cout << "\n";
}
