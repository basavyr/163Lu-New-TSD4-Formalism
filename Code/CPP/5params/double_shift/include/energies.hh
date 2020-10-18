#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

//The analytical expressions for the wobbling energies of $^{163}$Lu - using B1 formalism and adopting a double-energy-shift in the bands TSD2 and TSD4
//Free-Parameter set: A1, A2, A3, V, Gamma
//Gamma *must* have units of radians
class Energies
{
public:
    const double PI = 3.141592654;
    const double YRAST_SPIN = 6.5;
    const double j = 6.5;
    const double ERROR = 6969;

    int valid(double number)
    {
        if (!isnan(number) && number != ERROR)
            return 1;
        return 0;
    }

    //Gamma in radians!
    double B_Term(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        auto t1 = ((2.0 * I - 1.0) * (A3 - A1) + 2.0 * j * A1) * ((2.0 * I - 1.0) * (A2 - A1) + 2.0 * j * A1) + 8.0 * A2 * A3 * I * j;
        if (!valid(t1))
            return ERROR;

        auto t2 = ((2.0 * j - 1.0) * (A3 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1) / (j * (j + 1.0)) * sqrt(3.0) * (sqrt(3.0) * cos(Gamma) + sin(Gamma)));
        if (!valid(t2))
            return ERROR;

        auto t3 = ((2.0 * j - 1.0) * (A2 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / (j * (j + 1.0)) * 2 * sqrt(3.0) * sin(Gamma));
        if (!valid(t3))
            return ERROR;

        return static_cast<double>((t1 + t2 * t3) * (-1.0));
    }

    //Gamma in radians!
    double C_Term(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        auto t1 = ((2.0 * I - 1.0) * (A3 - A1) + 2.0 * j * A1) * ((2.0 * j - 1.0) * (A3 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / ((j * (j + 1))) * sqrt(3.0) * (sqrt(3.0) * cos(Gamma) + sin(Gamma))) - 4.0 * I * j * A3 * A3;
        if (!valid(t1))
            return ERROR;

        auto t2 = ((2.0 * I - 1.0) * (A2 - A1) + 2.0 * j * A1) * ((2.0 * j - 1.0) * (A2 - A1) + 2.0 * I * A1 + V * (2.0 * j - 1.0) / ((j * (j + 1))) * 2.0 * sqrt(3.0) * sin(Gamma)) - 4.0 * I * j * A2 * A2;
        if (!valid(t2))
            return ERROR;

        return static_cast<double>(t1 * t2);
    }

    //Gamma in radians!
    double H_min(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        auto hmin = (A2 + A3) * (I + j) * 0.5 + A1 * pow(I - j, 2) - V * (2.0 * j - 1.0) / (j + 1) * sin(Gamma + (PI / 6));
        if (!valid(hmin))
            return ERROR;

        return static_cast<double>(hmin);
    }

    //Gamma in radians!
    double OmegA1(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        auto B = B_Term(I, A1, A2, A3, V, Gamma);
        if (!valid(B))
            return ERROR;

        auto C = C_Term(I, A1, A2, A3, V, Gamma);
        if (!valid(C))
            return ERROR;

        auto Om_1 = static_cast<double>(sqrt(0.5 * (-B - sqrt(B * B - 4.0 * C))));
        if (!valid(Om_1))
            return ERROR;

        return Om_1;
    }

    //Gamma in radians!
    double OmegA2(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        auto B = B_Term(I, A1, A2, A3, V, Gamma);
        if (!valid(B))
            return ERROR;

        auto C = C_Term(I, A1, A2, A3, V, Gamma);
        if (!valid(C))
            return ERROR;

        auto Om_2 = static_cast<double>(sqrt(0.5 * (-B + sqrt(B * B - 4.0 * C))));
        if (!valid(Om_2))
            return ERROR;

        return Om_2;
    }

    //The general formula of the Wobbling Energy for a triaxial band in $^{163}$Lu
    //Phonon excitation numbers nw_1 and nw_2 represent the core and particle effects, respectively
    //gamma in radians!
    double Wobbling_Energy(int nw_1, int nw_2, double I, double A1, double A2, double A3, double V, double Gamma)
    {
        //Check if both frequencies are real-physical numbers
        //First Wobbling Phonon Energy OmegA1
        auto Om_1 = OmegA1(I, A1, A2, A3, V, Gamma);
        if (!valid(Om_1))
            return ERROR;

        //Second Wobbling Phonon Energy OmegA2
        auto Om_2 = OmegA2(I, A1, A2, A3, V, Gamma);
        if (!valid(Om_2))
            return ERROR;

        double E = H_min(I, A1, A2, A3, V, Gamma) + Om_1 * (nw_1 + 0.5) + Om_2 * (nw_2 + 0.5);
        if (!valid(E))
            return ERROR;

        return E;
    }

    double TSD1(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        double E_0 = Wobbling_Energy(0, 0, YRAST_SPIN, A1, A2, A3, V, Gamma);
        if (!valid(E_0))
            return ERROR;

        double E = Wobbling_Energy(0, 0, I, A1, A2, A3, V, Gamma);
        if (!valid(E))
            return ERROR;

        //Return the excitation energy
        return E - E_0;
    }

    //approach B1 (from the UNIFIED MODEL)
    //TSD2 is a 0-phonon excitation built on top of TSD1, being the signature-partner of TSD1
    //TSD2 is a ground-state band
    //TSD2 Contains an upward shift in energy due to the signature nature
    double TSD2(double I, double A1, double A2, double A3, double V, double Gamma, double TSD2_SHIFT)
    {
        double E_0 = Wobbling_Energy(0, 0, YRAST_SPIN, A1, A2, A3, V, Gamma);
        if (!valid(E_0))
            return ERROR;

        double E_Shifted = Wobbling_Energy(0, 0, I, A1, A2, A3, V, Gamma) + TSD2_SHIFT;
        if (!valid(E_Shifted))
            return ERROR;

        //Return the excitation energy
        return E_Shifted - E_0;
    }

    //TSD3 is the 1-phonon excited band of the nucleus
    double TSD3(double I, double A1, double A2, double A3, double V, double Gamma)
    {
        double E_0 = Wobbling_Energy(0, 0, YRAST_SPIN, A1, A2, A3, V, Gamma);
        if (!valid(E_0))
            return ERROR;

        double E = Wobbling_Energy(1, 0, I - 1.0, A1, A2, A3, V, Gamma);
        if (!valid(E))
            return ERROR;

        //Return the excitation energy
        return E - E_0;
    }

    //approach B1 (from the UNIFIED MODEL)
    //TSD4 is a 0-phonon excitation built on top of TSD1, being the chiral partner of TSD1
    //TSD4 is in fact a ground-state band
    //TSD4 Contains an upward shift in energy due to the chiral nature
    double TSD4(double I, double A1, double A2, double A3, double V, double Gamma, double TSD4_SHIFT)
    {
        double E_0 = Wobbling_Energy(0, 0, YRAST_SPIN, A1, A2, A3, V, Gamma);
        if (!valid(E_0))
            return ERROR;

        //adds the shift to the overall Absolute Wobbling Energy  (before normallizing it to the excitation value)
        double E_Shifted = Wobbling_Energy(0, 0, I, A1, A2, A3, V, Gamma) + TSD4_SHIFT;

        if (!valid(E_Shifted))
            return ERROR;

        //Return the excitation energy
        return E_Shifted - E_0;
    }

    //The energy function H(theta,varphi) associated to the nucleus $^{163}$Lu.
    //The spherical coordinates theta and fi are given in RADIANS
    //The triaxial parameter \gamma must be in RADIANS
    double H_En(double theta, double fi, double I, double A1, double A2, double A3, double V, double gamma)
    {
        auto free_term = (I * 0.5 * (A1 + A2)) + A3 * pow(I, 2) + (j * 0.5 * (A2 + A3)) + A1 * pow(j, 2) - (V * (2.0 * j - 1.0) / (j + 1.0) * sin(gamma + PI / 6.0));
        if (!valid(free_term))
            return ERROR;

        auto theta_term = -(2.0 * A1 * I * j * sin(theta));
        if (!valid(theta_term))
            return ERROR;

        auto mixed_term = I * (I - 0.5) * pow(sin(theta), 2.0) * (A1 * pow(cos(fi), 2) + A2 * pow(sin(fi), 2) - A3);
        if (!valid(mixed_term))
            return ERROR;

        return free_term + mixed_term + theta_term;
    }
};