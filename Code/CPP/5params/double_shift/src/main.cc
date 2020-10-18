#include "../include/energies.hh"

#include <iostream>
#include <fstream>

#include <cmath>
#include <algorithm>
#include <vector>

//constants for easy-access
const double PI = 3.141592654;

//*Experimental data

//The containers for storing the experimental data for spins
const std::vector<double>
    SPIN1 = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
const std::vector<double> SPIN2 = {13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};
const std::vector<double> SPIN3 = {16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5};
const std::vector<double> SPIN4 = {23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5};
const std::vector<double> ALL_SPINS = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};

//Containers for storing the experimental excitation energies
const std::vector<double> TSD1_Exp = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
const std::vector<double> TSD2_Exp = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
const std::vector<double> TSD3_Exp = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
const std::vector<double> TSD4_Exp = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};

//Values for the energy-shift which has to be added in TSD2 & TSD4
std::vector<double> SHIFTS = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6};

//?Initializing the analytical formulas as a class object instance at the start of the main implementation
Energies Lu163;

double IF(double MOI)
{
    return static_cast<double>(1.0 / (2.0 * MOI));
}

double RMS(double A1, double A2, double A3, double V, double Gamma, double TSD2_SHIFT, double TSD4_SHIFT)
{
    //Store the sum of the squared differences between E_Exp and E_Th
    double rms = 0.0;

    //store the current squared difference for each state
    double d_squared;

    //current energy for the spin and set parameters
    double E_wob_id;

    //Variable used for stopping the execution of the for-loops in case of fails within the runtime
    bool ok = true;

    //Prevent obtaining partial-squared-sums, by checking if every energy was a real-physical value for the current parameter set
    int valid_states_counter = 0;

    //TSD1
    {
        for (auto id = 0; id < SPIN1.size() && ok; ++id)
        {
            E_wob_id = Lu163.TSD1(SPIN1.at(id), A1, A2, A3, V, Gamma);
            d_squared = pow(TSD1_Exp.at(id) - E_wob_id, 2);
            if (!Lu163.valid(d_squared))
            {
                ok = false;
                valid_states_counter = 100;
                break;
            }
            else
            {
                /* code */
                rms += d_squared;
                valid_states_counter++;
            }
        }
    }

    //TSD2 - Shifted
    {
        for (auto id = 0; id < SPIN2.size() && ok; ++id)
        {
            E_wob_id = Lu163.TSD2(SPIN2.at(id), A1, A2, A3, V, Gamma, TSD2_SHIFT);
            d_squared = pow(TSD2_Exp.at(id) - E_wob_id, 2);
            if (!Lu163.valid(d_squared))
            {
                ok = false;
                valid_states_counter = 100;
                break;
            }
            else
            {
                /* code */
                rms += d_squared;
                valid_states_counter++;
            }
        }
    }

    //TSD3
    {
        for (auto id = 0; id < SPIN3.size() && ok; ++id)
        {
            E_wob_id = Lu163.TSD3(SPIN3.at(id), A1, A2, A3, V, Gamma);
            d_squared = pow(TSD3_Exp.at(id) - E_wob_id, 2);
            if (!Lu163.valid(d_squared))
            {
                ok = false;
                valid_states_counter = 100;
                break;
            }
            else
            {
                /* code */
                rms += d_squared;
                valid_states_counter++;
            }
        }
    }

    //TSD4 - Shifted
    {
        for (auto id = 0; id < SPIN4.size() && ok; ++id)
        {
            E_wob_id = Lu163.TSD4(SPIN4.at(id), A1, A2, A3, V, Gamma, TSD4_SHIFT);
            d_squared = pow(TSD4_Exp.at(id) - E_wob_id, 2);
            if (!Lu163.valid(d_squared))
            {
                ok = false;
                valid_states_counter = 100;
                break;
            }
            else
            {
                /* code */
                rms += d_squared;
                valid_states_counter++;
            }
        }
    }

    if ((valid_states_counter + 1) != Lu163.DATA_SIZE)
        return Lu163.ERROR;

    if (!Lu163.valid(rms))
        return Lu163.ERROR;

    return static_cast<double>(sqrt(rms / Lu163.DATA_SIZE));
}

int main()
{
    return 0;
}