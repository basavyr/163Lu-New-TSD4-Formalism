#include <iostream>
#include <fstream>
#include "../include/approachA.h"
#include "../include/approachB.h"

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
    double rms_A1;
    double rms_A2;
    double rms_B1;
    double rms_B2;
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

//store the values of the triaxial parameter which will be used within the `min_rms` searching function
const std::vector<int> gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

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

int main()
{
    Approach_A A;
    Approach_B B;
    auto best_rms = RMS(A, B, 73, 3, 67, 6.01, 21 * A.PI / 180.0);

    Params_tuple params(73, 3, 67, 6.01, 21 * A.PI / 180.0);
    // show_energies(A, B, params);
    show_rms_values(best_rms);
}