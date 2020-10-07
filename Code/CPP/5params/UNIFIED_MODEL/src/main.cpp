#include <iostream>
#include <fstream>
#include <chrono>

#include "../include/approachA.h"
#include "../include/approachB.h"

std::ofstream gout("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/CPP_FIT_RESULTS.dat");

double IF(double x)
{
    return (1.0) / (2.0 * x);
}

void print(double var)
{
    std::cout << var << "\n";
}

//compute all four values of the rms (A1,A2,B1 and B2) in a single function and store the results
struct RMS_tuple
{
    double A1, A2;
    double B1, B2;
    RMS_tuple()
    {
        A1 = 0.0;
        A2 = 0.0;
        B1 = 0.0;
        B2 = 0.0;
    }
    RMS_tuple(double init_val)
    {
        A1 = init_val;
        A2 = init_val;
        B1 = init_val;
        B2 = init_val;
    }
};

struct Params_tuple
{
    double I1;
    double I2;
    double I3;
    double V;
    double gm;
    double rms;
    Params_tuple()
    {
    }
    Params_tuple(double moi1, double moi2, double moi3, double V_init, double gm_init)
    {
        I1 = moi1;
        I2 = moi2;
        I3 = moi3;
        V = V_init;
        gm = gm_init;
        rms = 9876543210.1;
    }
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

//N+1 data points (subtract the band head level of TSD1)
const double DATA_SIZE = 62 + 1;

//store the values of the triaxial parameter which will be used within the `min_rms` searching function
const std::vector<int>
    gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

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

void show_energies(Approach_A &A, Approach_B &B, Params_tuple &params)
{
    //Formalism A
    std::cout << "############# FORMALISM A #############"
              << "\n";
    std::cout << "TSD1"
              << "\n";
    std::cout << "I   "
              << "E(EXP)  "
              << "E(TH)   "
              << "\n";
    for (auto id = 0; id < spin1.size(); ++id)
    {
        std::cout << spin1.at(id) << " " << tsd1.at(id) << " " << A.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "TSD2"
              << "\n";
    std::cout << "I   "
              << "E(EXP)  "
              << "E(TH)   "
              << "\n";
    for (auto id = 0; id < spin2.size(); ++id)
    {
        std::cout << spin2.at(id) << " " << tsd2.at(id) << " " << A.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "TSD3"
              << "\n";
    std::cout << "I   "
              << "E(EXP)  "
              << "E(TH)   "
              << "\n";
    for (auto id = 0; id < spin3.size(); ++id)
    {
        std::cout << spin3.at(id) << " " << tsd3.at(id) << " " << A.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "TSD4 A1 & A2"
              << "\n";
    std::cout << "I   "
              << "E(EXP) "
              << "TSD4_(0,0)  "
              << "TSD4_(1,0)  "
              << "\n";
    for (auto id = 0; id < spin4.size(); ++id)
    {
        std::cout << spin4.at(id) << " " << tsd4.at(id) << " " << A.TSD4_00(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << " " << A.TSD4_10(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "\n";
    //Formalism B
    std::cout << "############# FORMALISM B #############"
              << "\n";
    std::cout << "TSD1"
              << "\n";
    std::cout << "I   "
              << "E(EXP)  "
              << "E(TH)   "
              << "\n";
    for (auto id = 0; id < spin1.size(); ++id)
    {
        std::cout << spin1.at(id) << " " << tsd1.at(id) << " " << B.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "TSD2"
              << "\n";
    std::cout << "I   "
              << "E(EXP)  "
              << "E(TH)   "
              << "\n";
    for (auto id = 0; id < spin2.size(); ++id)
    {
        std::cout << spin2.at(id) << " " << tsd2.at(id) << " " << B.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "TSD3"
              << "\n";
    std::cout << "I   "
              << "E(EXP)  "
              << "E(TH)   "
              << "\n";
    for (auto id = 0; id < spin3.size(); ++id)
    {
        std::cout << spin3.at(id) << " " << tsd3.at(id) << " " << B.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
    std::cout << "TSD4 B1 & B2"
              << "\n";
    std::cout << "I   "
              << "E(EXP) "
              << "TSD4_(0,0)  "
              << "TSD4_(1,0)  "
              << "\n";
    for (auto id = 0; id < spin4.size(); ++id)
    {
        std::cout << spin4.at(id) << " " << tsd4.at(id) << " " << B.TSD4_00(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << " " << B.TSD4_10(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
}

RMS_tuple RMS(Approach_A &A, Approach_B &B, double i1, double i2, double i3, double v, double gm)
{
    //the variable to store the rms results
    RMS_tuple rms_results;

    //init the variables with 0.0 (since the squared differences will be summed up in the same variable)
    //this initializing process is now moved into the actual struct implementation(definition)
    // rms_results.A1 = 0.0;
    // rms_results.A2 = 0.0;
    // rms_results.B1 = 0.0;
    // rms_results.B2 = 0.0;

    auto a1 = IF(i1);
    auto a2 = IF(i2);
    auto a3 = IF(i3);

    bool ok = 1;
    int count = 0;
    {
        //TSD1
        for (auto id = 0; id < tsd1.size() && ok; ++id)
        {
            if (!A.valid(A.TSD1(spin1.at(id), a1, a2, a3, v, gm)) || !A.valid(B.TSD1(spin1.at(id), a1, a2, a3, v, gm)))
            {
                ok = 0;
                break;
            }
            else
            {
                /* code */
                rms_results.A1 += pow(tsd1.at(id) - A.TSD1(spin1.at(id), a1, a2, a3, v, gm), 2);
                rms_results.A2 += pow(tsd1.at(id) - A.TSD1(spin1.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B1 += pow(tsd1.at(id) - B.TSD1(spin1.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B2 += pow(tsd1.at(id) - B.TSD1(spin1.at(id), a1, a2, a3, v, gm), 2);
                count++;
            }
        }
        //TSD2
        for (auto id = 0; id < tsd2.size() && ok; ++id)
        {
            if (!A.valid(A.TSD2(spin2.at(id), a1, a2, a3, v, gm)) || !A.valid(B.TSD2(spin2.at(id), a1, a2, a3, v, gm)))
            {
                ok = 0;
                break;
            }
            else
            {
                /* code */
                rms_results.A1 += pow(tsd2.at(id) - A.TSD2(spin2.at(id), a1, a2, a3, v, gm), 2);
                rms_results.A2 += pow(tsd2.at(id) - A.TSD2(spin2.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B1 += pow(tsd2.at(id) - B.TSD2(spin2.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B2 += pow(tsd2.at(id) - B.TSD2(spin2.at(id), a1, a2, a3, v, gm), 2);
                count++;
            }
        }
        //TSD3
        for (auto id = 0; id < tsd3.size() && ok; ++id)
        {
            if (!A.valid(A.TSD3(spin3.at(id), a1, a2, a3, v, gm)) || !A.valid(B.TSD3(spin3.at(id), a1, a2, a3, v, gm)))
            {
                ok = 0;
                break;
            }
            else
            {
                /* code */
                rms_results.A1 += pow(tsd3.at(id) - A.TSD3(spin3.at(id), a1, a2, a3, v, gm), 2);
                rms_results.A2 += pow(tsd3.at(id) - A.TSD3(spin3.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B1 += pow(tsd3.at(id) - B.TSD3(spin3.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B2 += pow(tsd3.at(id) - B.TSD3(spin3.at(id), a1, a2, a3, v, gm), 2);
                count++;
            }
        }
        //TSD4
        for (auto id = 0; id < tsd4.size() && ok; ++id)
        {
            if (!A.valid(A.TSD4_00(spin4.at(id), a1, a2, a3, v, gm)) || !A.valid(B.TSD4_00(spin4.at(id), a1, a2, a3, v, gm)) || !A.valid(A.TSD4_10(spin4.at(id), a1, a2, a3, v, gm)) || !A.valid(B.TSD4_10(spin4.at(id), a1, a2, a3, v, gm)))
            {
                ok = 0;
                break;
            }
            else
            {
                /* code */
                rms_results.A1 += pow(tsd4.at(id) - A.TSD4_00(spin4.at(id), a1, a2, a3, v, gm), 2);
                rms_results.A2 += pow(tsd4.at(id) - A.TSD4_10(spin4.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B1 += pow(tsd4.at(id) - B.TSD4_00(spin4.at(id), a1, a2, a3, v, gm), 2);
                rms_results.B2 += pow(tsd4.at(id) - B.TSD4_10(spin4.at(id), a1, a2, a3, v, gm), 2);
                count++;
            }
        }
    }

    //final step in computing the root mean square values for the excitation energies
    //current computations consider N=n+1
    //only computes the actual rms values of all the iterations were valid
    if (count + 1 == 63)
    {
        rms_results.A1 = sqrt(rms_results.A1 / 63.0);
        rms_results.A2 = sqrt(rms_results.A2 / 63.0);
        rms_results.B1 = sqrt(rms_results.B1 / 63.0);
        rms_results.B2 = sqrt(rms_results.B2 / 63.0);
        return rms_results;
    }

    //if the program returns this, then the rms procedure for the current set of parameters is invalid
    return RMS_tuple(A.error_checker);
}

void show_rms_values(RMS_tuple &rms)
{
    std::cout << "A1: " << rms.A1 << "\n";
    std::cout << "A2: " << rms.A2 << "\n";
    std::cout << "B1: " << rms.B1 << "\n";
    std::cout << "B2: " << rms.B2 << "\n";
}

void show_params(Params_tuple &params)
{
    std::cout << params.I1 << " " << params.I2 << " " << params.I3 << " " << params.V << " " << params.gm << " " << params.rms;
    std::cout << "\n";
}

template <typename Formalism>
double Custom_RMS(Formalism &F, int Approach_Selector, double i1, double i2, double i3, double v, double gm)
{
    double rms_value = 0.0;
    int count = 0;
    gm = gm * F.PI / 180.0;
    bool ok = 1;
    if (Approach_Selector == 1)
    {
        //TSD1 - part
        for (auto id = 0; id < spin1.size() && ok; ++id)
        {
            auto E = F.TSD1(spin1.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd1.at(id) - E, 2);
                count++;
            }
        }
        //TSD2 - part
        for (auto id = 0; id < spin2.size() && ok; ++id)
        {
            auto E = F.TSD2(spin2.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd2.at(id) - E, 2);
                count++;
            }
        }
        //TSD3 - part
        for (auto id = 0; id < spin3.size() && ok; ++id)
        {
            auto E = F.TSD3(spin3.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd3.at(id) - E, 2);
                count++;
            }
        }
        //TSD4 - part
        for (auto id = 0; id < spin4.size() && ok; ++id)
        {
            auto E = F.TSD4_00(spin4.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd4.at(id) - E, 2);
                count++;
            }
        }
    }
    else
    {
        //TSD1 - part
        for (auto id = 0; id < spin1.size() && ok; ++id)
        {
            auto E = F.TSD1(spin1.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd1.at(id) - E, 2);
                count++;
            }
        }
        //TSD2 - part
        for (auto id = 0; id < spin2.size() && ok; ++id)
        {
            auto E = F.TSD2(spin2.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd2.at(id) - E, 2);
                count++;
            }
        }
        //TSD3 - part
        for (auto id = 0; id < spin3.size() && ok; ++id)
        {
            auto E = F.TSD3(spin3.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd3.at(id) - E, 2);
                count++;
            }
        }
        //TSD4 - part
        for (auto id = 0; id < spin4.size() && ok; ++id)
        {
            auto E = F.TSD4_10(spin4.at(id), IF(i1), IF(i2), IF(i3), v, gm);
            if (!F.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                rms_value += pow(tsd4.at(id) - E, 2);
                count++;
            }
        }
    }
    if (count + 1 == DATA_SIZE)
    {
        rms_value = sqrt(rms_value / DATA_SIZE);
    }
    else
    {
        /* code */
        rms_value = F.error_checker;
    }

    return rms_value;
}

template <typename Formalism>
void Search_Minimum_RMS(Formalism &F, int Approach_Selector, Params_tuple &results)
{

    //! change the steps for improving the accuracy of the results

    //! #######################
    const double I_step = 5;
    //! #######################

    //! #######################
    const double V_step = 0.1;
    //! #######################

    double min_rms = 987654321.0;
    double current_rms;

    for (auto I1 = 1; I1 <= 100; I1 += I_step)
    {
        for (auto I2 = 1; I2 <= 100; I2 += I_step)
        {
            if (I1 > I2)
                for (auto I3 = 1; I3 <= 100; I3 += I_step)
                {
                    for (auto V = 0.1; V <= 10.1; V += V_step)
                    {
                        for (auto gamma = 15.0; gamma <= 25.0; gamma++)
                        {
                            current_rms = Custom_RMS(F, Approach_Selector, I1, I2, I3, V, gamma);
                            if (current_rms <= min_rms)
                            {
                                min_rms = current_rms;
                                results.rms = min_rms;
                                results.I1 = I1;
                                results.I2 = I2;
                                results.I3 = I3;
                                results.V = V;
                                results.gm = gamma;
                            }
                        }
                    }
                }
        }
    }
}

template <typename Formalism>
void ShowResults_00(Formalism &F, Params_tuple &params)
{
    params.gm = params.gm * F.PI / 180.0;

    // std::cout << "_________________________________"
    //           << "\n";
    // std::cout << "ℐ₁ : ℐ₂ : ℐ₃ | " << params.I1 << ":" << params.I2 << ":" << params.I3 << "\n";
    // std::cout
    //     << "V=" << params.V << "\n";
    // std::cout << "𝛾=" << params.gm * 180.0 / F.PI << "\n";
    // std::cout << "_________________________________"
    //           << "\n";
    // std::cout << "### RMS=" << params.rms << " [keV] ###\n";
    // std::cout << "_________________________________"
    //           << "\n";
    // std::cout << "TSD1"
    //           << "\n";
    // std::cout << "I   "
    //           << "E(EXP)  "
    //           << "E(TH)   "
    //           << "\n";

    gout << "_________________________________"
         << "\n";
    gout << "ℐ₁ : ℐ₂ : ℐ₃ | " << params.I1 << ":" << params.I2 << ":" << params.I3 << "\n";
    gout
        << "V=" << params.V << "\n";
    gout << "𝛾=" << params.gm * 180.0 / F.PI << "\n";
    gout << "_________________________________"
         << "\n";
    gout << "### RMS=" << params.rms << " [keV] ###\n";
    gout << "_________________________________"
         << "\n";
    gout << "TSD1"
         << "\n";
    gout << "I   "
         << "E(EXP)  "
         << "E(TH)   "
         << "\n";

    for (auto id = 0; id < spin1.size(); ++id)
    {
        // std::cout << spin1.at(id) << " " << tsd1.at(id) << " " << F.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin1.at(id) << " " << tsd1.at(id) << " " << F.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }

    // std::cout << "TSD2"
    //           << "\n";
    // std::cout << "I   "
    //           << "E(EXP)  "
    //           << "E(TH)   "
    //           << "\n";

    gout << "TSD2"
         << "\n";
    gout << "I   "
         << "E(EXP)  "
         << "E(TH)   "
         << "\n";

    for (auto id = 0; id < spin2.size(); ++id)
    {
        // std::cout << spin2.at(id) << " " << tsd2.at(id) << " " << F.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin2.at(id) << " " << tsd2.at(id) << " " << F.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }

    // std::cout << "TSD3"
    //           << "\n";
    // std::cout << "I   "
    //           << "E(EXP)  "
    //           << "E(TH)   "
    //           << "\n";

    gout << "TSD3"
         << "\n";
    gout << "I   "
         << "E(EXP)  "
         << "E(TH)   "
         << "\n";

    for (auto id = 0; id < spin3.size(); ++id)
    {
        // std::cout << spin3.at(id) << " " << tsd3.at(id) << " " << F.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin3.at(id) << " " << tsd3.at(id) << " " << F.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }

    // std::cout << "TSD4"
    //           << "\n";
    // std::cout << "I  "
    //           << "E(EXP) |"
    //           << " E(TH) [0,0] "
    //           << "\n";

    gout << "TSD4"
         << "\n";
    gout << "I  "
         << "E(EXP) |"
         << " E(TH) [0,0] "
         << "\n";

    for (auto id = 0; id < spin4.size(); ++id)
    {
        // std::cout << spin4.at(id) << " " << tsd4.at(id) << " " << F.TSD4_00(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin4.at(id) << " " << tsd4.at(id) << " " << F.TSD4_00(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
}

template <typename Formalism>
void ShowResults_10(Formalism &F, Params_tuple &params)
{
    params.gm = params.gm * F.PI / 180.0;

    // std::cout << "_________________________________\n";
    // std::cout << "ℐ₁ : ℐ₂ : ℐ₃ | " << params.I1 << ":" << params.I2 << ":" << params.I3 << "\n";
    // std::cout
    //     << "V=" << params.V << "\n";
    // std::cout << "𝛾=" << params.gm * 180.0 / F.PI << "\n";
    // std::cout << "_________________________________\n";
    // std::cout << "### RMS=" << params.rms << " [keV] ###\n";
    // std::cout << "_________________________________\n";
    // std::cout << "TSD1\n";
    // std::cout << "I   "
    //           << "E(EXP)  "
    //           << "E(TH)\n";

    gout << "_________________________________\n";
    gout << "ℐ₁ : ℐ₂ : ℐ₃ | " << params.I1 << ":" << params.I2 << ":" << params.I3 << "\n";
    gout
        << "V=" << params.V << "\n";
    gout << "𝛾=" << params.gm * 180.0 / F.PI << "\n";
    gout << "_________________________________\n";
    gout << "### RMS=" << params.rms << " [keV] ###\n";
    gout << "_________________________________\n";
    gout << "TSD1\n";
    gout << "I   "
         << "E(EXP)  "
         << "E(TH)\n";

    for (auto id = 0; id < spin1.size(); ++id)
    {
        // std::cout << spin1.at(id) << " " << tsd1.at(id) << " " << F.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin1.at(id) << " " << tsd1.at(id) << " " << F.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }

    // std::cout << "TSD2\n";
    // std::cout << "I   "
    //           << "E(EXP)  "
    //           << "E(TH)\n";

    gout << "TSD2\n";
    gout << "I   "
         << "E(EXP)  "
         << "E(TH)\n";

    for (auto id = 0; id < spin2.size(); ++id)
    {
        // std::cout << spin2.at(id) << " " << tsd2.at(id) << " " << F.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin2.at(id) << " " << tsd2.at(id) << " " << F.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }

    // std::cout << "TSD3\n";
    // std::cout << "I   "
    //           << "E(EXP)  "
    //           << "E(TH)\n";

    gout << "TSD3\n";
    gout << "I   "
         << "E(EXP)  "
         << "E(TH)\n";

    for (auto id = 0; id < spin3.size(); ++id)
    {
        // std::cout << spin3.at(id) << " " << tsd3.at(id) << " " << F.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin3.at(id) << " " << tsd3.at(id) << " " << F.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }

    // std::cout << "TSD4\n";
    // std::cout << "I  "
    //           << "E(EXP) |"
    //           << " E(TH) [1,0]\n";

    gout << "TSD4\n";
    gout << "I  "
         << "E(EXP) |"
         << " E(TH) [1,0]\n";

    for (auto id = 0; id < spin4.size(); ++id)
    {
        // std::cout << spin4.at(id) << " " << tsd4.at(id) << " " << F.TSD4_10(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
        gout << spin4.at(id) << " " << tsd4.at(id) << " " << F.TSD4_10(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
    }
}

// Method which outputs the parameters and the corresponding excitation energies in a dedicated file, for later mathematica importing/plotting
template <typename Formalism>
void MathematicaOutput(Formalism F, Params_tuple &params, std::ofstream &gout, int Approach_Selector)
{
    // gout << params.rms << "\n";
    // gout << params.I1 << " " << params.I2 << " " << params.I3 << " " << params.V << " " << params.gm * 180.0 / F.PI << "\n";
    gout << params.I1 << " " << params.I2 << " " << params.I3 << " " << params.V << " " << params.gm << "\n";

    //! transform in radians if gamma is taken in degree unit
    params.gm = params.gm * F.PI / 180.0;

    switch (Approach_Selector)
    {
    case 1:
        /* code */
        {
            for (auto id = 0; id < spin1.size(); ++id)
            {
                gout << spin1.at(id) << " " << tsd1.at(id) << " " << F.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
            for (auto id = 0; id < spin2.size(); ++id)
            {
                gout << spin2.at(id) << " " << tsd2.at(id) << " " << F.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
            for (auto id = 0; id < spin3.size(); ++id)
            {
                gout << spin3.at(id) << " " << tsd3.at(id) << " " << F.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
            for (auto id = 0; id < spin4.size(); ++id)
            {
                gout << spin4.at(id) << " " << tsd4.at(id) << " " << F.TSD4_00(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
        }
        break;
    case 2:
        /* code */
        {
            for (auto id = 0; id < spin1.size(); ++id)
            {
                gout << spin1.at(id) << " " << tsd1.at(id) << " " << F.TSD1(spin1.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
            for (auto id = 0; id < spin2.size(); ++id)
            {
                gout << spin2.at(id) << " " << tsd2.at(id) << " " << F.TSD2(spin2.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
            for (auto id = 0; id < spin3.size(); ++id)
            {
                gout << spin3.at(id) << " " << tsd3.at(id) << " " << F.TSD3(spin3.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
            for (auto id = 0; id < spin4.size(); ++id)
            {
                gout << spin4.at(id) << " " << tsd4.at(id) << " " << F.TSD4_10(spin4.at(id), IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.gm) << "\n";
            }
        }
        break;
    }
}

// int main()
// {
//     Approach_A A;
//     Approach_B B;

//     //Store the values of the parameter set
//     Params_tuple params_A1, params_A2, params_B1, params_B2;
//     {
//         auto start = std::chrono::system_clock::now();
//         Search_Minimum_RMS<Approach_A>(A, 1, params_A1);
//         std::cout << "Finished searching for params of A1..."
//                   << "\nProcess took:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0 << " s\n";

//         start = std::chrono::system_clock::now();
//         Search_Minimum_RMS<Approach_A>(A, 2, params_A2);
//         std::cout << "Finished searching for params of A2..."
//                   << "\nProcess took:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0 << " s\n";

//         start = std::chrono::system_clock::now();
//         Search_Minimum_RMS<Approach_B>(B, 1, params_B1);
//         std::cout << "Finished searching for params of B1..."
//                   << "\nProcess took:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0 << " s\n";

//         start = std::chrono::system_clock::now();
//         Search_Minimum_RMS<Approach_B>(B, 2, params_B2);
//         std::cout << "Finished searching for params of B2..."
//                   << "\nProcess took:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0 << " s\n";
//     }

//     // std::cout << "FORMALISM A \n";
//     // std::cout << "_________________________________\n";
//     // std::cout << "APPROACH A1 \n";

//     gout << "FORMALISM A \n";
//     gout << "_________________________________\n";
//     gout << "APPROACH A1 \n";

//     ShowResults_00(A, params_A1);

//     // std::cout << "\n";
//     // std::cout << "_________________________________\n";
//     // std::cout << "APPROACH A2 \n";

//     gout << "\n";
//     gout << "_________________________________\n";
//     gout << "APPROACH A2 \n";

//     ShowResults_10(A, params_A2);

//     // std::cout << "\n";

//     gout << "\n";

//     // std::cout << "FORMALISM B \n";
//     // std::cout << "_________________________________\n";
//     // std::cout << "APPROACH B1 \n";

//     gout << "FORMALISM B \n";
//     gout << "_________________________________\n";
//     gout << "APPROACH B1 \n";

//     ShowResults_00(B, params_B1);

//     // std::cout << "\n";
//     // std::cout << "_________________________________\n";
//     // std::cout << "APPROACH B2 \n";

//     gout << "\n";
//     gout << "_________________________________\n";
//     gout << "APPROACH B2 \n";

//     ShowResults_10(B, params_B2);

//     //* TO-DO
//     //* Implement proper output for mathematica taking in consideration for format described below
//     //LINE0: I1,I2,I3,V,gamma -> the fit parameters
//     //LINE1+: I | E_exp | E_th

//     std::ofstream math_file_A1("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitA1_cxx.dat");
//     std::ofstream math_file_A2("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitA2_cxx.dat");
//     std::ofstream math_file_B1("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitB1_cxx.dat");
//     std::ofstream math_file_B2("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitB2_cxx.dat");

//     MathematicaOutput(A, params_A1, math_file_A1, 1);
//     MathematicaOutput(A, params_A2, math_file_A2, 2);
//     MathematicaOutput(B, params_B1, math_file_B1, 1);
//     MathematicaOutput(B, params_B2, math_file_B2, 2);
// }

//!Use this main function if only the mathematica output with pre-defined parameters is needed
//!This main skips the computational part of the RMS

int main()
{
    Approach_A A;
    Approach_B B;

    //Store the values of the parameter set
    Params_tuple params_A1, params_A2, params_B1, params_B2;

    //Storing constant parameters from the I=1 step size (for each approach)
    Params_tuple step100_a1(76, 52, 3, 1.8, 18);
    Params_tuple step100_a2(73, 3, 67, 5.3, 25);
    Params_tuple step100_b1(78, 5, 14, 1.3, 25);
    Params_tuple step100_b2(73, 68, 3, 8.5, 15);

    //Storing constant parameters from the I=2.5 step size (for each approach)
    Params_tuple step205_a1(76, 52, 3, 1.8, 18);
    Params_tuple step205_a2(73, 3, 67, 5.3, 25);
    Params_tuple step205_b1(78, 5, 14, 1.3, 25);
    Params_tuple step205_b2(73, 68, 3, 8.5, 15);

    //* initialize the parameters with fixed values

    //A1-Approach
    params_A1.I1 = 76;
    params_A1.I2 = 52;
    params_A1.I3 = 3;
    params_A1.V = 1.8;
    params_A1.gm = 18;

    //A2-Approach
    params_A2.I1 = 73;
    params_A2.I2 = 3;
    params_A2.I3 = 67;
    params_A2.V = 5.3;
    params_A2.gm = 25;

    //B1-Approach
    params_B1.I1 = 77;
    params_B1.I2 = 15;
    params_B1.I3 = 5;
    params_B1.V = 1.3;
    params_B1.gm = 22;

    //B2-Approach
    params_B2.I1 = 73;
    params_B2.I2 = 68;
    params_B2.I3 = 3;
    params_B2.V = 8.5;
    params_B2.gm = 15;

    std::ofstream math_file_A1("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitA1_cxx.dat");
    std::ofstream math_file_A2("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitA2_cxx.dat");
    std::ofstream math_file_B1("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitB1_cxx.dat");
    std::ofstream math_file_B2("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Unified_Model/fitB2_cxx.dat");

    //The procedure for outputing data with the correct format
    MathematicaOutput(A, step100_a1, math_file_A1, 1);
    MathematicaOutput(A, step100_a2, math_file_A2, 2);
    MathematicaOutput(B, step100_b1, math_file_B1, 1);
    MathematicaOutput(B, step100_b2, math_file_B2, 2);
}