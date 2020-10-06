#include "../include/approachA.h"
#include "../include/approachB.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

class RMS_IMPL
{
public:
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
    double IF(double x)
    {
        return (1.0) / (2.0 * x);
    }

public:
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

public:
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
        const double I_step = 1.0;
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
    void ShowResults_00(Formalism &F, Params_tuple &params, std::ofstream &gout)
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
    void ShowResults_10(Formalism &F, Params_tuple &params, std::ofstream &gout)
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
};