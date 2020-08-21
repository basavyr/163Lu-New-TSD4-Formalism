#include <vector>
#include <cmath>
#include <fstream>

// #include "expdata.h"
#include "app.h"
#include "energies.h"
class rms
{
    // private:
    //     static constexpr double error_number = 6969.0;
public:
    struct ParamSet
    {
        const double I_min = 1.0;
        const double I_max = 120;
        const double I_step = 10.0;
        const double gamma_min = 0.0;
        const double gamma_max = 60.0;
        const double gamma_step = 1.0;
        double I1, I2, I3, gamma, V;
        const double V_min = 0.01;
        const double V_max = 10.0;
        const double V_step = 1.0;
    };

public:
    static double RMS(std::vector<double> &exp_data, std::vector<double> &th_data);
    void SearchMIN_RMS(expdata &data, Formulas &energies)
    {
        ParamSet params;
        std::ofstream gout("params.dat");
        double best_RMS = 987654321.0;
        for (auto I1 = params.I_min; I1 < params.I_max; I1 += params.I_step)
        {
            for (auto I2 = params.I_min; I2 < params.I_max; I2 += params.I_step)
            {
                for (auto I3 = params.I_min; I3 < params.I_max; I3 += params.I_step)
                {
                    for (auto V = params.V_min; V < params.V_max; V += params.V_step)
                    {
                        for (auto gamma = params.gamma_min; gamma < params.gamma_max; gamma += params.gamma_step)
                        {
                            // std::cout << I1 << " " << I2 << " " << I3 << " " << V << " " << gamma << "\n";
                            auto th_Data = Formulas::GenerateTheoreticalData(data, energies, I1, I2, I3, V, gamma);
                            auto rms = RMS(data.exp_Data, th_Data);
                            if (rms <= best_RMS)
                            {
                                best_RMS = rms;
                                params.I1 = I1;
                                params.I2 = I2;
                                params.I3 = I3;
                                params.V = V;
                                params.gamma = gamma;
                                // gout<< I1 << " " << I2 << " " << I3 << " " << V << " " << gamma << " " << rms << "\n";
                            }
                        }
                    }
                }
            }
        }
        std::cout << "I1= " << params.I1;
        std::cout << "\n";
        std::cout << "I2= " << params.I2;
        std::cout << "\n";
        std::cout << "I3= " << params.I3;
        std::cout << "\n";
        std::cout << "V= " << params.V;
        std::cout << "\n";
        std::cout << "gm= " << params.gamma;
        std::cout << "\n";
        std::cout << "E_RMS= " << best_RMS;
        std::cout << "\n";
    }
};
