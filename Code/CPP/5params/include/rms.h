#include <vector>
#include <cmath>
#include <fstream>

// #include "expdata.h"
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
        double I1, I2, I3, theta, V;
        const double V_min = 0.01;
        const double V_max = 10.0;
        const double V_step = 1.0;
    };

public:
    static double RMS(std::vector<double> &exp_data, std::vector<double> &th_data);
    void SearchMIN_RMS(expdata &obj)
    {
        {
            ParamSet params;
            std::ofstream gout("params.dat");
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
                                gout << I1 << " " << I2 << " " << I3 << " " << V << " " << gamma << "\n";
                                auto x = Formulas::GenerateTheoreticalData(obj, 1, 1, 1, 1, 1, 1);
                            }
                        }
                    }
                }
            }
        }
    }
};
