#include <vector>
#include <cmath>
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
        const double gamma_max = 30.0;
        const double gamma_step = 5.0;
        double I1, I2, I3, theta, V;
        const double V_min = 0.01;
        const double V_max = 10.0;
        const double V_step = 1.0;
    };

public:
    static double RMS(std::vector<double> &exp_data, std::vector<double> &th_data);
    void SearchMIN_RMS();
};
