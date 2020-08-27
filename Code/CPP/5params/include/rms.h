#include <vector>
#include <cmath>
#include <array>
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
        const double I_max = 100;
        const double I_step = 1;
        const double gamma_min = 0.0;
        const double gamma_max = 60.0;
        const double gamma_step = 1;
        double I1, I2, I3, gamma, V;
        const double V_min = 0.01;
        const double V_max = 10.0;
        const double V_step = 0.25;
    };

public:
    static double RMS(const std::vector<double> &exp_data, const std::array<double, expdata::STATES> &th_data);

    //!No transverse regime considered into the search procedure
    void SearchMIN_RMS(expdata &data, Formulas &energies)
    {
        ParamSet params;
        std::ofstream gout("./out/params.dat");
        gout << "Starting to search for the minimum RMS...";
        gout << "\n";
        double best_RMS = 987654321.0;
        int OK_iterations = 0;
        const int n_total_evals = pow((params.I_max - params.I_min) / params.I_step, 3) * ((params.V_max - params.V_min) / params.V_step) * ((params.gamma_max - params.gamma_min) / params.gamma_step);
        std::vector<double> best_th_set;
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
                            if (Formulas::Triaxiality(I1, I2, I3))
                            {
                                auto th_Data = Formulas::GenerateTheoreticalData(data, energies, I1, I2, I3, V, gamma);

                                auto rms = 1;

                                if (rms <= best_RMS)
                                {
                                    best_RMS = rms;
                                    params.I1 = I1;
                                    params.I2 = I2;
                                    params.I3 = I3;
                                    params.V = V;
                                    params.gamma = gamma;
                                    best_th_set = th_Data;
                                    OK_iterations++;
                                }
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
        gout << "I1= " << params.I1;
        gout << "\n";
        gout << "I2= " << params.I2;
        gout << "\n";
        gout << "I3= " << params.I3;
        gout << "\n";
        gout << "V= " << params.V;
        gout << "\n";
        gout << "gm= " << params.gamma;
        gout << "\n";
        gout << "E_RMS= " << best_RMS;
        gout << "\n";
        for (auto &&n : best_th_set)
        {
            gout << n << ",";
        }
        gout << "\n";
        gout << "Finished computations after " << OK_iterations << " valid parameter evaluations...";
        gout << "\n";
        gout << "Total evaluations: " << n_total_evals;
        gout << "\n";
    }

    //?Transverse regime implemented by default
    void SearchRMS_DirectComputation(expdata &data, Formulas &energies)
    {
        ParamSet params;
        std::ofstream gout("./out/DirectComp.dat");
        gout << "The TRANSVERSE regime for $^{163}$Lu...";
        gout << "\n";
        gout << "I2-maximal MOI...";
        gout << "\n";
        gout << "Starting to search for the minimum RMS...";
        gout << "\n";

        double best_RMS = 987654321.0;

        int OK_iterations = 0;
        double sum;
        int ok;

        const int n_total_evals = pow((params.I_max - params.I_min) / params.I_step, 3) * ((params.V_max - params.V_min) / params.V_step) * ((params.gamma_max - params.gamma_min) / params.gamma_step);

        std::array<double, expdata::STATES> best_th_set;

        for (auto I1 = params.I_min; I1 < params.I_max; I1 += params.I_step)
        {
            for (auto I2 = params.I_min; I2 < params.I_max; I2 += params.I_step)
            {
                for (auto I3 = params.I_min; I3 < params.I_max && (I2 > I1); I3 += params.I_step)
                {
                    for (auto V = params.V_min; V < params.V_max && (I2 > I3) && (I1 != I3); V += params.V_step)
                    {
                        for (auto gamma = params.gamma_min; gamma < params.gamma_max; gamma += params.gamma_step)
                        {
                            ok = 1;
                            sum = 0.0;
                            for (auto id = 0; id < data.STATES && ok; ++id)
                            {
                                if (id < 21)
                                {
                                    auto d = pow((data.exp_Data[id] - energies.E_TSD1(data.spins[id], I1, I2, I3, V, gamma)), 2);
                                    if (!Formulas::ValidNumbers(d))
                                    {
                                        ok = 0;
                                        sum = Formulas::error_number;
                                        break;
                                    }
                                    else
                                    {
                                        sum += d;
                                    }
                                }
                                if (id >= 21 && id < 38)
                                {
                                    auto d = pow((data.exp_Data[id] - energies.E_TSD2(data.spins[id], I1, I2, I3, V, gamma)), 2);
                                    if (!Formulas::ValidNumbers(d))
                                    {
                                        ok = 0;
                                        sum = Formulas::error_number;
                                        break;
                                    }
                                    else
                                    {
                                        sum += d;
                                    }
                                }
                                if (id >= 38 && id < 52)
                                {
                                    auto d = pow((data.exp_Data[id] - energies.E_TSD3(data.spins[id], I1, I2, I3, V, gamma)), 2);
                                    if (!Formulas::ValidNumbers(d))
                                    {
                                        ok = 0;
                                        sum = Formulas::error_number;
                                        break;
                                    }
                                    else
                                    {
                                        sum += d;
                                    }
                                }
                                if (id >= 52 && id < 62)
                                {
                                    auto d = pow((data.exp_Data[id] - energies.E_TSD4_00(data.spins[id], I1, I2, I3, V, gamma)), 2);
                                    if (!Formulas::ValidNumbers(d))
                                    {
                                        ok = 0;
                                        sum = Formulas::error_number;
                                        break;
                                    }
                                    else
                                    {
                                        sum += d;
                                    }
                                }
                            }
                            if (sum == Formulas::error_number)
                                break;
                            else
                            {
                                sum = sqrt(sum / (expdata::STATES + 1));
                            }
                            if (sum <= best_RMS)
                            {
                                best_RMS = sum;
                                params.I1 = I1;
                                params.I2 = I2;
                                params.I3 = I3;
                                params.V = V;
                                params.gamma = gamma;
                                // best_th_set = th_Data;
                                OK_iterations++;
                            }
                        }
                    }
                }
            }
        }

        std::cout << "Parameter set determination using direct computation of the RMS values, inside the search function. No external methods are called for computing the RMS of the dataset...";
        std::cout << "\n";
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

        gout << "Parameter set determination using direct computation of the RMS values, inside the search function. No external methods are called for computing the RMS of the dataset...";
        gout << "\n";
        gout << "I1= " << params.I1;
        gout << "\n";
        gout << "I2= " << params.I2;
        gout << "\n";
        gout << "I3= " << params.I3;
        gout << "\n";
        gout << "V= " << params.V;
        gout << "\n";
        gout << "gm= " << params.gamma;
        gout << "\n";
        gout << "E_RMS= " << best_RMS;
        gout << "\n";
        for (auto &&n : best_th_set)
        {
            gout << n << ",";
        }
        gout << "\n";
        gout << "Finished computations after " << OK_iterations << " valid parameter evaluations...";
        gout << "\n";
        gout << "Total evaluations: " << n_total_evals;
        gout << "\n";
    }

    //?Transverse regime implemented by default
    void
    SearchRMS_FixedArray(expdata &data, Formulas &energies)
    {
        ParamSet params;
        std::ofstream gout("./out/FixedArray.dat");
        gout << "The TRANSVERSE regime for $^{163}$Lu...";
        gout << "\n";
        gout << "I2-maximal MOI...";
        gout << "\n";
        gout << "Starting to search for the minimum RMS...";
        gout << "\n";

        double best_RMS = 987654321.0;

        int OK_iterations = 0;

        const int n_total_evals = pow((params.I_max - params.I_min) / params.I_step, 3) * ((params.V_max - params.V_min) / params.V_step) * ((params.gamma_max - params.gamma_min) / params.gamma_step);

        std::array<double, expdata::STATES> best_th_set;

        for (auto I1 = params.I_min; I1 < params.I_max; I1 += params.I_step)
        {
            for (auto I2 = params.I_min; I2 < params.I_max; I2 += params.I_step)
            {
                for (auto I3 = params.I_min; I3 < params.I_max && (I2 > I1); I3 += params.I_step)
                {
                    for (auto V = params.V_min; V < params.V_max && (I2 > I3) && (I1 != I3); V += params.V_step)
                    {
                        for (auto gamma = params.gamma_min; gamma < params.gamma_max; gamma += params.gamma_step)
                        {

                            //!change the implementation to support a fixed size array instead of re-allocation with every loop iteration
                            auto thdata = energies.GenerateData_Static(energies.TH_DATA, data, energies, I1, I2, I3, V, gamma);
                            auto sum = RMS(data.exp_Data, thdata);

                            if (sum <= best_RMS)
                            {
                                best_RMS = sum;
                                params.I1 = I1;
                                params.I2 = I2;
                                params.I3 = I3;
                                params.V = V;
                                params.gamma = gamma;
                                //Store the array with the evaluated excitation energies, given by the current "best" parameter set
                                best_th_set = thdata;
                                //? might be more optimal to evaluate the energy set after the parameters are determined from the iteration procedure
                                OK_iterations++;
                            }
                        }
                    }
                }
            }
        }
        std::cout << "Parameter set determination using the fixed size arrays, with no memory re-allocation...";
        std::cout << "\n";
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

        gout << "Parameter set determination using the fixed size arrays, with no memory re-allocation...";
        gout << "\n";
        gout << "I1= " << params.I1;
        gout << "\n";
        gout << "I2= " << params.I2;
        gout << "\n";
        gout << "I3= " << params.I3;
        gout << "\n";
        gout << "V= " << params.V;
        gout << "\n";
        gout << "gm= " << params.gamma;
        gout << "\n";
        gout << "E_RMS= " << best_RMS;
        gout << "\n";
        for (auto &&n : best_th_set)
        {
            gout << n << ",";
        }
        gout << "\n";
        gout << "Finished computations after " << OK_iterations << " valid parameter evaluations...";
        gout << "\n";
        gout << "Total evaluations: " << n_total_evals;
        gout << "\n";
    }

    //Function for searching the minimum RMS using the fixed-array method (no re-allocation)
    //The moments of inertia are triaxial, within the transverse wobbling regime and they have a general difference of 10% in the absolute values with respect to each other.
    void SearchRMS_FA_Delta(expdata &data, Formulas &energies)
    {
        ParamSet params;
        std::ofstream gout("./out/DeltaParams.dat");
        std::ofstream paramFile("./out/ParamValues.dat");
        gout << "The TRANSVERSE regime for $^{163}$Lu...";
        gout << "\n";
        gout << "I2-maximal MOI...";
        gout << "\n";
        gout << "Starting to search for the minimum RMS...";
        gout << "\n";

        double best_RMS = 987654321.0;

        int OK_iterations = 0;

        //change this quantity for accepting a certain difference between the three moments of inertia in the min_rms search loop
        double MOI_AcceptedDifference = 10;

        const int n_total_evals = pow((params.I_max - params.I_min) / params.I_step, 3) * ((params.V_max - params.V_min) / params.V_step) * ((params.gamma_max - params.gamma_min) / params.gamma_step);

        std::array<double, expdata::STATES> best_th_set;
        auto gamma = 17;
        auto V = 9.1;
        for (auto I1 = params.I_min; I1 < params.I_max; I1 += params.I_step)
        {
            for (auto I2 = params.I_min; I2 < params.I_max; I2 += params.I_step)
            {
                for (auto I3 = params.I_min; I3 < params.I_max && (I2 > I1) && (I2 > I3); I3 += params.I_step)
                {
                    //Accept only MOIs which belong to the transverse wobbling regime
                    //Only the moments of inertia with more than 15% of their absolute difference between each other are accepted
                    if (Formulas::Triaxiality(I1, I2, I3) && Formulas::Delta_MOI(MOI_AcceptedDifference, I1, I2, I3))
                    {
                        // for (auto V = params.V_min; V < params.V_max; V += params.V_step)
                        // {
                        //     for (auto gamma = params.gamma_min; gamma < params.gamma_max; gamma += params.gamma_step)
                        //     {

                        //!change the implementation to support a fixed size array instead of re-allocation with every loop iteration
                        auto thdata = energies.GenerateData_Static(energies.TH_DATA, data, energies, I1, I2, I3, V, gamma);
                        auto sum = RMS(data.exp_Data, thdata);

                        if (sum <= best_RMS)
                        {
                            best_RMS = sum;
                            params.I1 = I1;
                            params.I2 = I2;
                            params.I3 = I3;
                            params.V = V;
                            params.gamma = gamma;
                            //Store the array with the evaluated excitation energies, given by the current "best" parameter set
                            best_th_set = thdata;
                            //? might be more optimal to evaluate the energy set after the parameters are determined from the iteration procedure
                            OK_iterations++;
                        }
                        paramFile << I1 << " " << I2 << " " << I3 << "\n";
                        //     }
                        // }
                    }
                }
            }
        }
        std::cout << "Parameter set determination using the fixed size arrays, with no memory re-allocation...";
        std::cout << "\n";
        std::cout << "Using a fixed Delta between the three MOIs: delta= " << MOI_AcceptedDifference;
        std::cout << "\n";
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

        gout << "Parameter set determination using the fixed size arrays, with no memory re-allocation...";
        gout << "\n";
        gout << "Using a fixed Delta between the three MOIs: delta= " << MOI_AcceptedDifference;
        gout << "\n";
        gout << "I1= " << params.I1;
        gout << "\n";
        gout << "I2= " << params.I2;
        gout << "\n";
        gout << "I3= " << params.I3;
        gout << "\n";
        gout << "V= " << params.V;
        gout << "\n";
        gout << "gm= " << params.gamma;
        gout << "\n";
        gout << "E_RMS= " << best_RMS;
        gout << "\n";
        for (auto &&n : best_th_set)
        {
            gout << n << ",";
        }
        gout << "\n";
        gout << "Finished computations after " << OK_iterations << " valid parameter evaluations...";
        gout << "\n";
        gout << "Total evaluations: " << n_total_evals;
        gout << "\n";
    }
};
