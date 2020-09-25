#include "../include/energies_0010.hh"
#include "../include/energies_0011.hh"
#include "../include/energies_1230.hh"
#include <iomanip>
#include <chrono>
#include <ctime>
#include <fstream>

//uses the system path copied from machine tree
//better to use relative path (to the current directory)
std::ofstream gout("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Reports/SIGNATURE_FORMALISM/signature_params.dat");

double IF(double I)
{
    return 1.0 / (2.0 * I);
}

const std::vector<double> spin1 = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
const std::vector<double> spin2 = {13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};
const std::vector<double> spin3 = {16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5};
const std::vector<double> spin4 = {23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5};
const std::vector<double> tsd1 = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
const std::vector<double> tsd2 = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
const std::vector<double> tsd3 = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
const std::vector<double> tsd4 = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};
const std::vector<int> gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

template <typename T>
double rms(T &nucleus, double a1, double a2, double a3, double v, double gamma)
{
    double best_rms = 9876543210.0;
    double E;
    double sum = 0.0;
    int count = 0;
    bool ok = 1;

    {
        // std::cout << "Started TSD1...";
        // std::cout << "\n";
        for (auto id = 0; id < spin1.size() && ok; ++id)
        {
            E = nucleus.TSD1(spin1.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                // std::cout << "Failed inside TSD1 at I=" << spin1.at(id) << " | Params: " << IF(a1) << " " << IF(a2) << " " << IF(a3) << " " << v << " " << gamma;
                // std::cout << "\n";
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd1.at(id), 2);
                count++;
            }
        }

        // std::cout << "Started TSD2...";
        // std::cout << "\n";
        for (auto id = 0; id < spin2.size() && ok; ++id)
        {
            E = nucleus.TSD2(spin2.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                // std::cout << "Failed inside TSD2 at I=" << spin2.at(id) << "and params:" << IF(a1) << " " << IF(a2) << " " << IF(a3) << " " << v << " " << gamma;
                // std::cout << "\n";
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd2.at(id), 2);
                count++;
            }
        }

        // std::cout << "Started TSD3...";
        // std::cout << "\n";
        for (auto id = 0; id < spin3.size() && ok; ++id)
        {
            E = nucleus.TSD3(spin3.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                // std::cout << "Failed inside TSD3 at I=" << spin3.at(id) << "and params:" << IF(a1) << " " << IF(a2) << " " << IF(a3) << " " << v << " " << gamma;
                // std::cout << "\n";
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd3.at(id), 2);
                count++;
            }
        }

        // std::cout << "Started TSD4...";
        // std::cout << "\n";
        for (auto id = 0; id < spin4.size() && ok; ++id)
        {
            E = nucleus.TSD4(spin4.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                // std::cout << "Failed inside TSD4 at I=" << spin4.at(id) << "and params:" << IF(a1) << " " << IF(a2) << " " << IF(a3) << " " << v << " " << gamma;
                // std::cout << "\n";
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd4.at(id), 2);
                count++;
            }
        }
    }

    if (count == 62)
    {
        sum = sqrt(sum / 63.0);
        if (sum < best_rms)
            best_rms = sum;
    }

    return best_rms;
}

void ShowEnergies()
{
    // for (auto &&n : spin1)
    // {
    //     std::cout << n << " " << bands_0010.TSD1(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD2(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD3(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD4(n, a1, a2, a3, v, gm) << "\n";
    // }
    // for (auto &&n : spins)
    // {
    //     std::cout << n << " " << bands_1230.TSD1(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD2(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD3(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD4(n, a1, a2, a3, v, gm) << "\n";
    // }
}

void TestRMS()
{
    //The bands initialization procedure
    Bands_0010 bands_0010;
    Bands_0011 bands_0011;

    //The constants used in computations (testing purposes only)
    auto a1 = 1.0 / (2.0 * 73.0);
    auto a2 = 1.0 / (2.0 * 3);
    auto a3 = 1.0 / (2.0 * 67.0);
    auto v = 6.01;
    // auto gm = 21.0 * bands_0010.PI / 180.0;

    std::cout << "TSD4: (0,0)";
    std::cout << "\n";
    std::cout << rms<Bands_0010>(bands_0010, a1, a2, a3, v, 21);
    std::cout << "\n";
    std::cout << "TSD4: (1,0)";
    std::cout << "\n";
    std::cout << rms<Bands_0011>(bands_0011, a1, a2, a3, v, 21);
    std::cout << "\n";
}

struct Parameters
{
    double V;
    double gamma;
    double I1;
    double I2;
    double I3;
    double rms;
};

void ShowFitParameters(Parameters &params)
{
    std::cout << "RMS=" << params.rms << " keV\n";
    std::cout << "ℐ₁:ℐ₂:ℐ₃ -> " << std::setprecision(3) << params.I1 << ":" << std::setprecision(3) << params.I2 << ":" << std::setprecision(3) << params.I3 << "\n";
    std::cout << "V=" << params.V << "\n";
    std::cout << "𝛾=" << params.gamma << "\n";
    gout << "RMS=" << params.rms << " keV\n";
    gout << "ℐ₁:ℐ₂:ℐ₃ -> " << std::setprecision(3) << params.I1 << ":" << std::setprecision(3) << params.I2 << ":" << std::setprecision(3) << params.I3 << "\n";
    gout << "V=" << params.V << "\n";
    gout << "𝛾=" << params.gamma << "\n";
}

void FindMinimumRMS(int Formalism, Parameters &params)
{
    if (Formalism == 0)
    {

        std::cout << "TSD4: (0,0)"
                  << "\n";
        gout << "TSD4: (0,0)"
             << "\n";
    }
    else
    {
        std::cout << "TSD4: (1,0)"
                  << "\n";
        gout << "TSD4: (1,0)"
             << "\n";
    }

    double best_rms = 9876543210.0;

    //The bands initialization procedure
    Bands_0010 bands_0010;
    Bands_0011 bands_0011;

    double current_rms;

    double istep = 1;

    for (auto i1 = 1; i1 < 100; i1 += istep)
    {
        for (auto i2 = 1; i2 < 100; i2 += istep)
        // auto i2 = 32;
        {
            // if (i1 > i2)
            {
                for (auto i3 = 1; i3 < 100; i3 += istep)
                {
                    // if (i3 > i2 + 15)
                    {
                        for (auto v = 0.1; v <= 10.0; v += 1)
                        {
                            for (auto &&gamma : gm)
                            {
                                if (Formalism == 1)
                                    current_rms = rms<Bands_0011>(bands_0011, IF(i1), IF(i2), IF(i3), v, gamma);
                                else
                                {
                                    current_rms = rms<Bands_0010>(bands_0010, IF(i1), IF(i2), IF(i3), v, gamma);
                                }
                                if (current_rms < best_rms)
                                {
                                    best_rms = current_rms;
                                    params.I1 = i1;
                                    params.I2 = i2;
                                    params.I3 = i3;
                                    params.V = v;
                                    params.gamma = gamma;
                                    params.rms = best_rms;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    ShowFitParameters(params);
}

void TestConsistencyMath(Parameters &params)
{
    Bands_0010 band_0010;
    Bands_0011 band_0011;
    //TSD1
    for (auto &&I : spin1)
    {
        std::cout << std::setprecision(4) << I << " " << band_0010.TSD1(I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gamma * band_0011.PI / 180.0) << "\n";
    }
    //TSD2
    for (auto &&I : spin2)
    {
        std::cout << std::setprecision(4) << I << " " << band_0010.TSD2(I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gamma * band_0011.PI / 180.0) << "\n";
    }

    //TSD3
    for (auto &&I : spin3)
    {
        std::cout << std::setprecision(4) << I << " " << band_0010.TSD3(I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gamma * band_0011.PI / 180.0) << "\n";
    }

    //TSD4(0,0)
    for (auto &&I : spin4)
    {
        std::cout << std::setprecision(4) << I << " " << band_0010.TSD4(I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gamma * band_0011.PI / 180.0) << "\n";
    }

    //TSD4(1,0)
    // for (auto &&I : spin4)
    // {
    //     std::cout << std::setprecision(5) << I << " " << band_0011.TSD4(I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gamma * band_0011.PI / 180.0) << "\n";
    // }
}

int main()
{
    Parameters FIT_PARAMETERS;

    //actual implementation which finds the minimum rms
    auto start = std::chrono::system_clock::now();
    FindMinimumRMS(0, FIT_PARAMETERS);
    FindMinimumRMS(1, FIT_PARAMETERS);
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
    std::cout << "Fit procedure lasted: " << std::setprecision(7) << duration_ms / 1000.0 << " s"
              << "\n";
    // TestConsistencyMath(FIT_PARAMETERS);

    // start = std::chrono::system_clock::now();
    // FindMinimumRMS(1, FIT_PARAMETERS);
    // duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
    // std::cout << "Fit procedure lasted: " << duration_ms / 1000.0 << " s"
    //           << "\n";
}