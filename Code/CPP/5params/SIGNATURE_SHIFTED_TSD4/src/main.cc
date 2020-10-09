#include "../include/energies.hh"

#include <iostream>
#include <fstream>
#include <chrono>

//N+1 data points (subtract the band head level of TSD1)
const double DATA_SIZE = 62 + 1;

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
const std::vector<int>
    gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

//store the values of the tsd4 energy shift
std::vector<double> tsd4_shift = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5};

struct FitParameters
{
    double I1, I2, I3, V, GAMMA;
    double TSD4_SHIFT;
    double RMS;
};

double IF(double I)
{
    return 1.0 / (2.0 * I);
}

Bands Lu163;

double RMS(double i1, double i2, double i3, double v, double gm, double SHIFT)
{
    auto a1 = IF(i1);
    auto a2 = IF(i2);
    auto a3 = IF(i3);

    //variables that check validity of the rms computation
    bool ok = true;
    int count = 0;

    //store the RMS VALUE
    double sum = 0.0;
    double term;

    // Computing the squared sum of all the analytical energies (EXP-TH)^2 with respect to the parameter set
    {
        //TSD1
        for (auto id = 0; id < spin1.size() && ok; ++id)
        {
            term = pow(tsd1.at(id) - Lu163.TSD1(spin1.at(id), a1, a2, a3, v, gm), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }

        //TSD2
        for (auto id = 0; id < spin2.size() && ok; ++id)
        {
            term = pow(tsd2.at(id) - Lu163.TSD2(spin2.at(id), a1, a2, a3, v, gm), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }

        //TSD3
        for (auto id = 0; id < spin3.size() && ok; ++id)
        {
            term = pow(tsd3.at(id) - Lu163.TSD3(spin3.at(id), a1, a2, a3, v, gm), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }

        //TSD4
        for (auto id = 0; id < spin4.size() && ok; ++id)
        {
            term = pow(tsd4.at(id) - Lu163.TSD4(spin4.at(id), a1, a2, a3, v, gm, SHIFT), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }
    }
    if (count + 1 == DATA_SIZE)
        return static_cast<double>(sqrt(sum / DATA_SIZE));
    return Lu163.error_checker;
}

void Search_MIN_RMS(FitParameters &params)
{
    double MIN_RMS = 987654321.0;
    double I_step = 5.0;
    double V_step = 1.0;

    double current_rms;

    for (auto i1 = 1.0; i1 <= 100.0; i1 += I_step)
    {
        for (auto i2 = 1.0; i2 <= 100.0; i2 += I_step)
        {
            if (i1 > i2)
                for (auto i3 = 1.0; i3 <= 100.0; i3 += I_step)
                {
                    for (auto V = 0.1; V <= 10.0; V += V_step)
                    {
                        for (auto gm = 15.0; gm <= 25.0; gm += 1.0)
                        {
                            current_rms = RMS(i1, i2, i3, V, gm * Lu163.PI / 180.0, 0);
                            if (Lu163.valid(current_rms) && current_rms <= MIN_RMS)
                            {
                                MIN_RMS = current_rms;
                                params.I1 = i1;
                                params.I2 = i2;
                                params.I3 = i3;
                                params.V = V;
                                params.GAMMA = gm;
                                params.TSD4_SHIFT = 0.0;
                                params.RMS = MIN_RMS;
                            }
                        }
                    }
                }
        }
    }
}

int main()
{
    double i1 = 73.0;
    double i2 = 68.0;
    double i3 = 3.0;
    double v = 8.1;
    double gm_deg = 18;
    double gamma = gm_deg * Lu163.PI / 180.0;
    double SHIFT = 0.0;

    FitParameters fit_params;

    auto start = std::chrono::system_clock::now();
    Search_MIN_RMS(fit_params);
    std::cout << "Process took: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0 << "s\n";

    std::cout << fit_params.I1 << " " << fit_params.I2 << " " << fit_params.I3 << "\n";
    std::cout << fit_params.V << " " << fit_params.GAMMA << "\n";
    std::cout << fit_params.RMS << " @shift= " << fit_params.TSD4_SHIFT << "\n";
    return 0;
}