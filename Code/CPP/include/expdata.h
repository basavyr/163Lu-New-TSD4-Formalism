#ifndef EXPDATA_HH
#define EXPDATA_HH

#include <vector>
#include <iostream>

class expdata
{
public:
    const double j1 = 13.0 / 2.0;
    const double j2 = 11.0 / 2.0;
    const double spinZero = 6.5;
    //SPINS
    const std::vector<double> spin1 = {1, 2, 3, 4};
    const std::vector<double> spin2 = {1, 2, 3, 4};
    const std::vector<double> spin3 = {1, 2, 3, 4};
    const std::vector<double> spin4 = {1, 2, 3, 4};
    //ENERGIES
    const std::vector<double> tsd1 = {1, 2, 3, 4};
    const std::vector<double> tsd2 = {1, 2, 3, 4};
    const std::vector<double> tsd3 = {1, 2, 3, 4};
    const std::vector<double> tsd4 = {1, 2, 3, 4};
    template <typename T>
    void ShowVector(const std::vector<T> &v)
    {
        for (auto &&n : v)
        {
            std::cout << n << " ";
        }
        std::cout << "\n";
    }
};

// void expdata::ShowVector(std::vector<double> &v)
// {
// }

#endif // EXPDATA_HH