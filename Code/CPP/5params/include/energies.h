#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <array>

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
    static int Triaxiality(double, double, double);

    //Considering only I2-maximal moment of inertia
    static int TransverseWobbling(double I1, double I2, double I3);

    static int Delta_MOI(double delta, double I1, double I2, double I3);

    //The general formula for the excitation energy of a triaxial band defined by the two wobbling phonon numbers n1 and n2, respectively
    double E_Wobbling(int n1, int n2, double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double E_TSD1(double spin, double i1, double i2, double i3, double V, double gamma);
    double E_TSD2(double spin, double i1, double i2, double i3, double V, double gamma);
    double E_TSD3(double spin, double i1, double i2, double i3, double V, double gamma);

    // Calculation of the fourth wobbling band using the new formalism, where the TSD4 band is considered as the g.s.b. for a different sequence of spins
    double E_TSD4_00(double spin, double i1, double i2, double i3, double V, double gamma);

    // Calculation of the fourth wobbling band using the standard and well-known formalism, where TSD4 is considered the first excited wobbling-phonon band built on top of TSD1
    double E_TSD4_10(double spin, double i1, double i2, double i3, double V, double gamma);

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

    //declaring the fixed-size array in which the values for the theoretical energies are stored
    std::array<double, expdata::STATES> TH_DATA;

    static std::array<double, expdata::STATES> GenerateData_Static(std::array<double, expdata::STATES> &th_data, expdata &data, Formulas &energies, double I1, double I2, double I3, double V, double gamma)
    {
        for (auto id = 0; id < expdata::STATES; ++id)
        {
            if (id < 21)
                th_data[id] = energies.E_TSD1(data.spins[id], I1, I2, I3, V, gamma);
            if (id >= 21 && id < 38)
                th_data[id] = energies.E_TSD2(data.spins[id], I1, I2, I3, V, gamma);
            if (id >= 38 && id < 52)
                th_data[id] = energies.E_TSD3(data.spins[id], I1, I2, I3, V, gamma);
            if (id >= 52 && id < 62)
                th_data[id] = energies.E_TSD4_00(data.spins[id], I1, I2, I3, V, gamma);
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
