#include "../include/rms.h"

// #include "../include/energies.h"

double rms::RMS(const std::vector<double> &exp_data, const std::array<double, expdata::STATES> &th_data)
{
    size_t s1 = exp_data.size();
    size_t s2 = th_data.size();

    //Stop of the arrays are not equal in length
    if (s1 != s2)
        return Formulas::error_number;

    int count = 0;
    int ok = 1;
    double sum = 0.0;

    for (auto id = 0; id < s1 && ok; ++id)
    {
        auto exp = exp_data.at(id);
        auto th = th_data.at(id);

        //Stop if ANY of the data sets contain non-physical values
        if (!Formulas::ValidNumbers(exp) || !Formulas::ValidNumbers(th))
        {
            ok = 0;
            return Formulas::error_number;
        }
        auto Delta = exp - th;
        auto T = pow(Delta, 2);

        //Stop if the term is non-physical
        if (!Formulas::ValidNumbers(T))
        {
            ok = 0;
            return Formulas::error_number;
        }

        sum += T;
        count += 1;
    }
    auto RMS = static_cast<double>(sqrt(sum / (s1 + 1)));
    if (count - s1 == 0 && Formulas::ValidNumbers(RMS))
        return RMS;
    return Formulas::error_number;
}

//search the minimum rms value while keeping the Lund convention (where the maximal moi is along the 1-axis)
//The Phonon selector allows for both formalisms to the applied in the analytic computations
//The triaxiality parameter $gamma$ is fixed while the iterative process searches for results
void rms::SearchRMS_FixedGamma(expdata &data, Formulas &energies, int Phonon_Selector, int Max_MOI_Axis, double gamma)
{
    ParamSet params;
    std::ofstream gout("./out/1AxisParams.dat");

    int state_counter = 0;
    auto best_rms = 987654321.0;
    std::array<double, expdata::STATES> best_th_data;

    for (auto I1 = params.I_min; I1 < params.I_max; I1 += params.I_step)
    {
        for (auto I2 = params.I_min; I2 < params.I_max; I2 += params.I_step)
        {
            for (auto I3 = params.I_min; I3 < params.I_max; I3 += params.I_step)
            {
                if (Formulas::LundConvention(I1, I2, I3, Max_MOI_Axis))
                {
                    for (auto V = params.V_min; V < params.V_max; V += params.V_step)
                    {
                        state_counter++;
                        auto th_Data = energies.GenerateData_Static(energies.TH_DATA, data, energies, I1, I2, I3, V, gamma, Phonon_Selector);
                        auto rms = rms::RMS(data.exp_Data, th_Data);
                        if (rms <= best_rms)
                        {
                            best_rms = rms;
                            params.I1 = I1;
                            params.I2 = I2;
                            params.I3 = I3;
                            params.V = V;
                            best_th_data = th_Data;
                            // gout << I1 << " " << I2 << " " << I3 << " " << V << " " << rms << "\n";
                        }
                    }
                }
            }
        }
    }
    gout << "I1= " << params.I1 << "\n";
    gout << "I2= " << params.I2 << "\n";
    gout << "I3= " << params.I3 << "\n";
    gout << "V= " << params.V << "\n";
    gout << "gamma= " << gamma << "\n";
    gout << "E_RMS= " << best_rms << "\n";
    gout << "Theoretical dataset:"
         << "\n";
    for (auto &&n : best_th_data)
    {
        gout << n << ",";
    }
    gout << "\n";
    // gout << state_counter;
}