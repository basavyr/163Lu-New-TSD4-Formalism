#include <iostream>
#include <fstream>
#include "../include/approachA.h"
#include "../include/approachB.h"

//compute all four values of the rms (A1,A2,B1 and B2) in a single function and store the results
struct RMS_tuple
{
    double A1, A2;
    double B1, B2;
};

//The containers for storing the experimental data for spins
const std::vector<double>
    spin1 = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
const std::vector<double> spin2 = {13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};
const std::vector<double> spin3 = {16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5};
const std::vector<double> spin4 = {23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5};

//The containers for storing the experimental data for excitation energies
const std::vector<double> tsd1 = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
const std::vector<double> tsd2 = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
const std::vector<double> tsd3 = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
const std::vector<double> tsd4 = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};

//store the values of the triaxial parameter which will be used within the `min_rms` searching function
const std::vector<int> gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

void print(double var)
{
    std::cout << var << "\n";
}

void print_array(std::string arr_name, const std::vector<double> &arr)
{
    std::cout << arr_name << " = {";
    for (auto id = 0; id < arr.size(); ++id)
    {
        if (id != arr.size() - 1)
            std::cout << arr.at(id) << " , ";
        else
        {
            std::cout << arr.at(id);
        }
    }
    std::cout << "}"
              << "\n";
}

RMS_tuple RMS(double i1, double i2, double i3, double v, double gm)
{
    RMS_tuple rms_results;
    rms_results.A1 = 1;
    rms_results.A2 = 2;
    rms_results.B1 = 3;
    rms_results.B2 = 4;
    return rms_results;
}

void show_rms_values(RMS_tuple &rms)
{
    std::cout << "A1: " << rms.A1 << "\n";
    std::cout << "A2: " << rms.A2 << "\n";
    std::cout << "B1: " << rms.B1 << "\n";
    std::cout << "B2: " << rms.B2 << "\n";
}

int main()
{
    Approach_A A;
    Approach_B B;
    auto best_rms = RMS(1, 1, 1, 1, 1);
    show_rms_values(best_rms);
}