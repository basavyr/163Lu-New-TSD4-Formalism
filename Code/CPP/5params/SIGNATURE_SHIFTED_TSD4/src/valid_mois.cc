//Implementation for finding valid sets of moments of inertia for the energy function H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

const double ODD_SPIN = 6.5;
const double PI = 3.141592654;
const double ZERO = 1.0e-8;
const double ERROR = 6969;

//gives the reduced set of parameters to be used in the procedures
struct Parameters
{
    // const double V = 9.1;
    // const double gamma = 19.0;
    double I1, I2, I3, I;
    double V, gamma;
    Parameters(double x, double y, double z, double t, double v, double gm)
    {
        I1 = x;
        I2 = y;
        I3 = z;
        I = t;
        V = v;
        gamma = gm;
    }
    Parameters(double spin, double x, double y)
    {
        I = spin;
        V = x;
        gamma = y;
    }
};

//coordinates to be saved for eventual use-case
struct coordinates
{
    double theta;
    double fi;
};

struct valid_mois
{
    double i1, i2, i3;
};

//gives the corresponding inertia factor A_k from for the moment of inertia I_k
double IF(double MOI)
{
    double A = 1.0 / (2.0 * MOI);
    return A;
}

//using the analytical formulas for the partial derivatives
double Theta_Critical(Parameters &params)
{
    //the single particle spin
    auto j = ODD_SPIN;

    //the inertia factors
    auto a1 = IF(params.I1);
    auto a3 = IF(params.I3);

    //the total spin
    auto I = params.I;

    auto sin_theta = static_cast<double>((2.0 * j * a1) / ((2.0 * I - 1.0) * (a1 - a3)));

    if (sin_theta <= 1.0 && sin_theta >= -1.0)
        return asin(sin_theta);

    return ERROR;
}

//writing the analytical form of the first-order derivatives of H(theta,fi) (first partial deriv)
double dH_dTheta(double theta, double fi, Parameters &params)
{
    //the single particle spin
    auto j = ODD_SPIN;

    //the inertia factors
    auto a1 = IF(params.I1);
    auto a2 = IF(params.I2);
    auto a3 = IF(params.I3);

    //the total spin
    auto I = params.I;

    return static_cast<double>(I * (I - 0.5) * sin(2.0 * theta) * (a1 * pow(cos(fi), 2) + a2 * pow(sin(fi), 2) - a3) - 2.0 * I * a1 * j * cos(theta));
}

//writing the analytical form of the first-order derivatives of H(theta,fi) (second partial deriv)
double dH_dFi(double theta, double fi, Parameters &params)
{
    //the inertia factors
    auto a1 = IF(params.I1);
    auto a2 = IF(params.I2);

    //the total spin
    auto I = params.I;

    return static_cast<double>(I * (I - 0.5) * (a2 - a1) * pow(sin(theta), 2) * sin(2.0 * fi));
}

void Search_Valid_MOIs(double I, double V, double gm)
{
    //total spin
    Parameters params(I, V, gm);

    //store the valid sets of moments of inertia
    std::vector<valid_mois> ok_mois;
    std::vector<coordinates> ok_coordinates;

    valid_mois current_mois;
    coordinates current_coords;

    int count = 0;

    double theta_rad;
    double fi_rad;

    for (auto i1 = 10.0; i1 < 90.0; i1 += 1.0)
    {
        for (auto i2 = 1.0; i2 < 90.0 && i2 < i1; i2 += 1.0)
        {
            for (auto i3 = 1.0; i3 < 90.0 && i3 != i2 && i3 < i1; i3 += 1.0)
            {
                params.I1 = i1;
                params.I2 = i2;
                params.I3 = i3;
                for (auto theta = 0.0; theta <= 180; theta += 10.0)
                {
                    for (auto fi = 0.0; fi <= 360.0; fi += 10.0)
                    {
                        fi_rad = fi * PI / 180.0;
                        theta_rad = theta * PI / 180.0;
                        if ((dH_dTheta(theta_rad, fi_rad, params) <= ZERO && dH_dTheta(theta_rad, fi_rad, params) >= -ZERO) && (dH_dFi(theta_rad, fi_rad, params) <= ZERO && dH_dFi(theta_rad, fi_rad, params) >= -ZERO))
                        {
                            // std::cout << dH_dTheta(theta_rad, fi_rad, params) << " " << dH_dFi(theta_rad, fi_rad, params) << "\n";
                            current_mois.i1 = i1;
                            current_mois.i2 = i2;
                            current_mois.i3 = i3;
                            current_coords.theta = theta;
                            current_coords.fi = fi;
                            ok_mois.emplace_back(current_mois);
                            ok_coordinates.emplace_back(current_coords);
                        }
                    }
                }
            }
        }
    }
    std::ofstream gout("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Energy_Function/valid_mois.dat");
    for (auto id = 0; id < ok_mois.size(); ++id)
    {
        gout << ok_mois.at(id).i1 << " " << ok_mois.at(id).i2 << " " << ok_mois.at(id).i3 << " " << ok_coordinates.at(id).theta << " " << ok_coordinates.at(id).fi << "\n";
    }
}

int main()
{
    auto start = std::chrono::system_clock::now();
    Search_Valid_MOIs(12.5, 9.1, 19);
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0;

    std::cout << "Process took: " << duration_ms << " s. \n";
}