#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

#include "expdata.h"
class Formulas
{
private:
    std::string debug_ON = "Debugger is ON...";
    std::string debug_OFF = "Debugger is OFF...";
    bool debug;

public:
    static constexpr double error_number = 6969.0;
    static constexpr double PI = 3.141592654;
    double Omega1(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double Omega2(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double BTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double CTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double Hmin(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    static int ValidNumbers(double);
    //The general formula for the excitation energy of a triaxial band defined by the two wobbling phonon numbers n1 and n2, respectively
    double E_Wobbling(int n1, int n2, double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double E_TSD1(double spin, double i1, double i2, double i3, double V, double gamma);
    double E_TSD2(double spin, double i1, double i2, double i3, double V, double gamma);
    double E_TSD3(double spin, double i1, double i2, double i3, double V, double gamma);

    // Calculation of the fourth wobbling band using the new formalism, where the TSD4 band is considered as the g.s.b. for a different sequence of spins
    double E_TSD4_00(double spin, double i1, double i2, double i3, double V, double gamma);

    // Calculation of the fourth wobbling band using the standard and well-known formalism, where TSD4 is considered the third excited wobbling-phonon band
    double E_TSD4_30(double spin, double i1, double i2, double i3, double V, double gamma);

    // template <typename T>
    // static std::vector<double> GenerateTheoreticalData(T &obj, double oddSpin, double I1, double I2, double I3, double V, double gamma)
    // {
    //     std::vector<double> th_data;
    //     double size;
    //     th_data.emplace_back(1.0);
    //     //generating the first band
    //     //?TSD1
    //     return th_data;
    // }
    static std::vector<double> GenerateTheoreticalData(expdata &data, Formulas &energies, double I1, double I2, double I3, double V, double gamma)
    {
        std::vector<double> th_data;
        double size = data.spin1.size();
        //generating the first band
        //?TSD1
        for (auto id = 0; id < size; ++id)
        {
            auto th = energies.E_TSD1(data.spin1.at(id), I1, I2, I3, V, gamma);
            if (ValidNumbers(th))
                th_data.emplace_back(th);
        }

        size = data.spin2.size();
        //?TSD2
        for (auto id = 0; id < size; ++id)
        {
            auto th = energies.E_TSD2(data.spin2.at(id), I1, I2, I3, V, gamma);
            if (ValidNumbers(th))
                th_data.emplace_back(th);
        }

        size = data.spin3.size();
        //?TSD3
        for (auto id = 0; id < size; ++id)
        {
            auto th = energies.E_TSD3(data.spin3.at(id), I1, I2, I3, V, gamma);
            if (ValidNumbers(th))
                th_data.emplace_back(th);
        }

        size = data.spin4.size();
        //?TSD4
        for (auto id = 0; id < size; ++id)
        {
            auto th = energies.E_TSD4_00(data.spin4.at(id), I1, I2, I3, V, gamma);
            if (ValidNumbers(th))
                th_data.emplace_back(th);
        }
        return th_data;
    }

public:
    Formulas(bool);
    ~Formulas();

    //helper functions
public:
    static double InertiaFactor(double I);
};
