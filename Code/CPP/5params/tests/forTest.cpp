#include <iostream>
#include <chrono>
#include <vector>

struct ParamSet
{
    const double I_min = 1;
    const double I_max = 10;
    const double I_step = 2;
    const double gamma_min = 0.0;
    const double gamma_max = 60.0;
    const double gamma_step = 1;
    // double I1, I2, I3, gamma, V;
    const double V_min = 0.01;
    const double V_max = 10.0;
    const double V_step = 0.25;
};

int main()
{
    ParamSet params;
    int count = 0;
    std::vector<double> storage;

    auto start = std::chrono::system_clock::now();
    for (auto I1 = params.I_min; I1 < params.I_max; I1 += params.I_step)
    {
        for (auto I2 = params.I_min; I2 < params.I_max; I2 += params.I_step)
        {
            if (I2 > I1)
                for (auto I3 = params.I_min; I3 < params.I_max; I3 += params.I_step)
                    if (I2 > I3 && I1 != I3)
                    {
                        std::cout << I1 << " " << I2 << " " << I3;
                        std::cout << "\n";
                        count++;
                        storage.emplace_back(count);
                    }
        }
    }
    auto stop = std::chrono::system_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << "Process took: " << duration_ms / 1000.0 << " s";
    std::cout << "\n";
    std::cout << "Size of container: N=" << storage.size();
    std::cout << "\n";
}