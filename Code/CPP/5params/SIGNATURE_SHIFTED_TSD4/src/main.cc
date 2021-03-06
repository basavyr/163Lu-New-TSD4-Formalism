#include "../include/energies.hh"

#include <iostream>
#include <fstream>
#include <chrono>

#include <iomanip>

//the size of the step for the spherical coordinates (theta, varphi)
const double SPH_STEP = 50000.0;

//N+1 data points (subtract the band head level of TSD1)
const double DATA_SIZE = 62 + 1;

//The containers for storing the experimental data for spins
const std::vector<double>
    spin1 = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
const std::vector<double> spin2 = {13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};
const std::vector<double> spin3 = {16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5};
const std::vector<double> spin4 = {23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5};

const std::vector<double> ALLSPINS = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};

//The containers for storing the experimental data for excitation energies
const std::vector<double> tsd1 = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
const std::vector<double> tsd2 = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
const std::vector<double> tsd3 = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
const std::vector<double> tsd4 = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};

//store the values of the triaxial parameter which will be used within the `min_rms` searching function
const std::vector<int>
    gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

//store the values of the tsd4 energy shift
std::vector<double> tsd4_shift = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6};

struct FitParameters
{
    double I1, I2, I3, V, GAMMA;
    double TSD4_SHIFT;
    double RMS;
    FitParameters(double i1, double i2, double i3, double v, double gamma, double shift)
    {
        I1 = i1;
        I2 = i2;
        I3 = i3;
        V = v;
        GAMMA = gamma;
        TSD4_SHIFT = shift;
    }
};

double IF(double I)
{
    return 1.0 / (2.0 * I);
}

Bands Lu163;

double RMS(double i1, double i2, double i3, double v, double gm, double SHIFT)
{
    auto a1 = IF(i1);
    auto a2 = IF(i2);
    auto a3 = IF(i3);

    //variables that check validity of the rms computation
    bool ok = true;
    int count = 0;

    //store the RMS VALUE
    double sum = 0.0;
    double term;

    // Computing the squared sum of all the analytical energies (EXP-TH)^2 with respect to the parameter set
    {
        //TSD1
        for (auto id = 0; id < spin1.size() && ok; ++id)
        {
            term = pow(tsd1.at(id) - Lu163.TSD1(spin1.at(id), a1, a2, a3, v, gm), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }

        //TSD2
        for (auto id = 0; id < spin2.size() && ok; ++id)
        {
            term = pow(tsd2.at(id) - Lu163.TSD2(spin2.at(id), a1, a2, a3, v, gm), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }

        //TSD3
        for (auto id = 0; id < spin3.size() && ok; ++id)
        {
            term = pow(tsd3.at(id) - Lu163.TSD3(spin3.at(id), a1, a2, a3, v, gm), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }

        //TSD4
        for (auto id = 0; id < spin4.size() && ok; ++id)
        {
            term = pow(tsd4.at(id) - Lu163.TSD4(spin4.at(id), a1, a2, a3, v, gm, SHIFT), 2);
            if (!Lu163.valid(term))
            {
                ok = false;
                count = 6969;
                break;
            }
            else
            {
                /* code */
                sum += term;
                count++;
            }
        }
    }
    if (count + 1 == DATA_SIZE)
        return static_cast<double>(sqrt(sum / DATA_SIZE));
    return Lu163.error_checker;
}

void Search_MIN_RMS(FitParameters &params)
{
    double MIN_RMS = 987654321.0;

    //! **************
    //! Change the parameters for precision improvement (Quality-of-fit)
    //! **************
    double I_step = 30.0;
    double V_step = 0.1;
    //! **************

    double current_rms;

    for (auto i1 = 1.0; i1 <= 100.0; i1 += I_step)
    {
        for (auto i2 = 1.0; i2 <= 100.0 && i2 < i1; i2 += I_step)
        {
            for (auto i3 = 1.0; i3 <= 100.0 && i3 != i2; i3 += I_step)
            {
                for (auto V = 0.1; V <= 10.0; V += V_step)
                {
                    for (auto gm = 15.0; gm <= 25.0; gm += 1.0)
                    {
                        for (auto &&shift : tsd4_shift)
                        {
                            current_rms = RMS(i1, i2, i3, V, gm * Lu163.PI / 180.0, shift);
                            if (Lu163.valid(current_rms) && current_rms <= MIN_RMS)
                            {
                                MIN_RMS = current_rms;
                                params.I1 = i1;
                                params.I2 = i2;
                                params.I3 = i3;
                                params.V = V;
                                params.GAMMA = gm;
                                params.TSD4_SHIFT = shift;
                                params.RMS = MIN_RMS;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Show_Params(FitParameters &fit_params)
{
    std::ofstream gout("shifted_tsd4.dat");
    std::cout << "ℐ₁ : ℐ₂ : ℐ₃ | " << fit_params.I1 << ":" << fit_params.I2 << ":" << fit_params.I3 << "\n";
    std::cout << "V=" << fit_params.V << "\n";
    std::cout << "𝛾=" << fit_params.GAMMA << "\n";
    std::cout << "### RMS=" << fit_params.RMS << " [keV] ###\n";
    std::cout << "SHIFT -> E_TSD4 = " << fit_params.TSD4_SHIFT << "\n";

    gout << "ℐ₁ : ℐ₂ : ℐ₃ | " << fit_params.I1 << ":" << fit_params.I2 << ":" << fit_params.I3 << "\n";
    gout << "V=" << fit_params.V << "\n";
    gout << "𝛾=" << fit_params.GAMMA << "\n";
    gout << "### RMS=" << fit_params.RMS << " [keV] ###\n";
    gout << "SHIFT -> E_TSD4 = " << fit_params.TSD4_SHIFT << "\n";
}

void Search_RMS(FitParameters &fit_params)
{

    auto start = std::chrono::system_clock::now();
    Search_MIN_RMS(fit_params);
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0;

    std::cout << "Process took: " << execution_time << "s\n";

    Show_Params(fit_params);
}

struct PartialD
{
    double dH_dTheta;
    double dH_dFi;
    double mixed;
};

//Computes the partial derivative of H to both variables
PartialD DH(double theta, double fi, double I, FitParameters &params)
{
    PartialD dh;

    //the step h (from the 5-point-stencil-method)
    double theta_step = (180.0 / SPH_STEP);

    //the step h (from the 5-point-stencil-method)
    double fi_step = (360.0 / SPH_STEP);

    //the partial derivative w.r.t. theta
    auto fx_2h = Lu163.H_En(theta + 2.0 * theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_h = Lu163.H_En(theta + theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_mh = Lu163.H_En(theta - theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_m2h = Lu163.H_En(theta - 2.0 * theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    dh.dH_dTheta = static_cast<double>((-fx_2h + 8.0 * fx_h - 8.0 * fx_mh + fx_m2h) / (12.0 * theta_step));

    //computing the partial derivative w.r.t. fi
    auto fy_2h = Lu163.H_En(theta, fi + 2.0 * fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_h = Lu163.H_En(theta, fi + fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_mh = Lu163.H_En(theta, fi - fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_m2h = Lu163.H_En(theta, fi - 2.0 * fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    dh.dH_dFi = static_cast<double>((-fy_2h + 8.0 * fy_h - 8.0 * fy_mh + fy_m2h) / (12.0 * fi_step));

    //computing the mixed derivative
    auto f_11 = Lu163.H_En(theta + theta_step, fi + fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto f_m1m1 = Lu163.H_En(theta - theta_step, fi - fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto f_m11 = Lu163.H_En(theta - theta_step, fi + fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto f_1m1 = Lu163.H_En(theta + theta_step, fi - fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    dh.mixed = static_cast<double>((f_11 - f_1m1 - f_m11 + f_m1m1) / (4.0 * fi_step * theta_step));

    return dh;
}

PartialD D2H(double theta, double fi, double I, FitParameters &params)
{
    PartialD d2h;

    //the step h (from the 5-point-stencil-method)
    double theta_step = (180.0 / SPH_STEP);

    //the step h (from the 5-point-stencil-method)
    double fi_step = (360.0 / SPH_STEP);

    auto fx = Lu163.H_En(theta, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_2h = Lu163.H_En(theta + 2.0 * theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_h = Lu163.H_En(theta + theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_mh = Lu163.H_En(theta - theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fx_m2h = Lu163.H_En(theta - 2.0 * theta_step, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);

    auto fy = Lu163.H_En(theta, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_2h = Lu163.H_En(theta, fi + 2.0 * fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_h = Lu163.H_En(theta, fi + fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_mh = Lu163.H_En(theta, fi - fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto fy_m2h = Lu163.H_En(theta, fi - 2.0 * fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);

    d2h.dH_dTheta = static_cast<double>((-fx_2h + 16.0 * fx_h - 30.0 * fx + 16.0 * fx_mh - fx_m2h) / (12.0 * pow(theta_step, 2)));
    d2h.dH_dFi = static_cast<double>((-fy_2h + 16.0 * fy_h - 30.0 * fy + 16.0 * fy_mh - fy_m2h) / (12.0 * pow(fi_step, 2)));

    //computing the mixed derivative
    auto f_11 = Lu163.H_En(theta + theta_step, fi + fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto f_m1m1 = Lu163.H_En(theta - theta_step, fi - fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto f_m11 = Lu163.H_En(theta - theta_step, fi + fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    auto f_1m1 = Lu163.H_En(theta + theta_step, fi - fi_step, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
    d2h.mixed = static_cast<double>((f_11 - f_1m1 - f_m11 + f_m1m1) / (4.0 * fi_step * theta_step));

    return d2h;
}

//The second derivative test for a function of one variable provides a method for determining whether an extremum occurs at a critical point of a function.
//When extending this result to a function of two variables, an issue arises related to the fact thatthere are, in fact, four different second-order partial derivatives, although equality of mixed partials reduces this to three.
//The second derivative test for a function of two variables, stated in the following theorem, uses a discriminant D, that replaces f′′(x0) in the second derivative test for a function of one variable.
double D_Operator(FitParameters &params, double theta, double fi, double I)
{
    auto f_xx = D2H(theta, fi, I, params).dH_dTheta;
    auto f_yy = D2H(theta, fi, I, params).dH_dFi;
    auto f_xy = D2H(theta, fi, I, params).mixed;

    auto Discriminant = (f_xx * f_yy) - pow(f_xy, 2);
    return Discriminant;
}

bool Local_Minimum(FitParameters &params, double theta, double fi, double I)
{
    auto D = D_Operator(params, theta, fi, I);
    auto D2_x = D2H(theta, fi, I, params).dH_dTheta;

    if (D > 0.0 && D2_x > 0.0)
        return true;
    return false;
}

void Diff_H(FitParameters &fit_params, double theta, double fi, double I)
{
    std::cout << "I= " << I << "\n";
    Show_Params(fit_params);

    std::cout << "\n";

    std::cout << "First derivative of H(𝜃,𝜑) ⇒ (" << theta << " , " << fi << ")\n";
    std::cout << "dH/d𝜃= " << DH(theta, fi, I, fit_params).dH_dTheta << "\n";
    std::cout << "dH/d𝜑= " << DH(theta, fi, I, fit_params).dH_dFi << "\n";

    std::cout << "Second derivative of H(𝜃,𝜑) ⇒ (" << theta << ", " << fi << ")\n ";
    std::cout << "d²H/d𝜃²= " << D2H(theta, fi, I, fit_params).dH_dTheta << "\n";
    std::cout << "d²H/d𝜑²= " << D2H(theta, fi, I, fit_params).dH_dFi << "\n";
}

void Find_CriticalPoints_H(FitParameters &params, double I)
{
    std::ofstream gout("local_minimas.dat");
    double H_En_min = 987654321.987654321;
    double current_H_En;

    double ZERO = 1.0e-10;

    double angle_step = 1.0;

    for (auto theta = 0.0; theta <= 180.0; theta += angle_step)
    {
        for (auto fi = 0.0; fi <= 360.0; fi += angle_step)
        {
            auto f = DH(theta, fi, I, params);
            auto fx = abs(f.dH_dTheta);
            auto fy = abs(f.dH_dFi);
            if (fx < ZERO && fy < ZERO)
            {
                if (Local_Minimum(params, theta, fi, I))
                {
                    gout << theta << " " << fi << "\n";
                    // current_H_En = Lu163.H_En(theta, fi, I, IF(params.I1), IF(params.I2), IF(params.I3), params.V, params.GAMMA * Lu163.PI / 180.0);
                    // if (current_H_En <= H_En_min)
                    // {
                    //     gout << theta << " " << fi << " " << current_H_En << " " << D_Operator(params, theta, fi, I) << " " << fx << " " << fy << "\n";
                    //     H_En_min = current_H_En;
                    // }
                }
            }
        }
    }
}

double ThetaCritical(double i1, double i3, double I)
{
    auto j = Lu163.j;
    auto a1 = IF(i1);
    auto a3 = IF(i3);
    auto sin_theta = static_cast<double>((2.0 * j * a1) / ((2.0 * I - 1.0) * (a1 - a3)));
    if (sin_theta <= 1.0 && sin_theta >= -1.0)
        return asin(sin_theta);
    return Lu163.error_checker;
}

//Moments of inertia which produce valid theta angle for computing the arcsin function
struct valid_mois
{
    /* data */
    double i1, i2, i3;
    double asin;
    valid_mois(double x, double y, double z, double spin)
    {
        i1 = x;
        i2 = y;
        i3 = z;
        asin = ThetaCritical(x, z, spin);
    }
};

std::vector<valid_mois> Search_Valid_CriticalTheta(double spin, double V, double gamma, double shift)
{
    std::ofstream gout("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Energy_Function/local_minimas.dat");
    std::ofstream gout_mois("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Energy_Function/valid_mois.dat");
    auto j = Lu163.j;
    std::vector<valid_mois> ok_mois;
    int count = 0;

    const double ZERO = 1.0e-8;
    // for (auto id = 0; id < ALLSPINS.size(); ++id)
    // {
    // auto I = ALLSPINS.at(id);
    auto I = spin;
    for (auto i1 = 1.0; i1 <= 100.0; ++i1)
    {
        for (auto i2 = 1.0; i2 <= 100.0 && i2 < i1; ++i2)
        {
            for (auto i3 = 1.0; i3 <= 100.0 && i3 != i2 && i3 < i1; ++i3)
            {
                if (ThetaCritical(i1, i2, spin) != Lu163.error_checker)
                {
                    valid_mois current_mois(i1, i2, i3, I);
                    ok_mois.emplace_back(current_mois);
                    gout << i1 << " " << i2 << " " << i3 << " " << ok_mois.at(count).asin << "\n";
                    count++;
                }
            }
        }
    }

    for (auto id = 0; id < ok_mois.size(); ++id)
    {
        for (auto theta = 0.0; theta <= 180.0; theta += 10.0)
        {
            for (auto fi = 0.0; fi <= 360.0; fi += 10.0)
            {
                auto theta_rad = theta * Lu163.PI / 180.0;
                auto fi_rad = fi * Lu163.PI / 180.0;
                FitParameters current_params(ok_mois.at(id).i1, ok_mois.at(id).i2, ok_mois.at(id).i3, V, gamma, shift);
                auto x = DH(theta_rad, fi_rad, I, current_params);
                if (abs(x.dH_dFi) <= ZERO && abs(x.dH_dTheta) <= ZERO)
                {
                    auto xx = D2H(theta_rad, fi_rad, I, current_params);
                    auto discr = D_Operator(current_params, theta_rad, fi_rad, I);
                    if (discr > 0.0 && xx.dH_dTheta > 0)
                    {
                        gout_mois << ok_mois.at(id).i1 << " " << ok_mois.at(id).i2 << " " << ok_mois.at(id).i3 << " " << theta << " " << fi << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                    }
                }
            }
        }
    }

    // std::cout << ok_mois.at(10).i1 << " " << ok_mois.at(10).i2 << " " << ok_mois.at(10).i3 << " " << ok_mois.at(10).asin << "\n";
    // std::cout << Lu163.H_En(ok_mois.at(10).asin, 0, spin, ok_mois.at(10).i1, ok_mois.at(10).i2, ok_mois.at(10).i3)
    //                  std::cout
    //           << Lu163.H_En(ok_mois.at(10).asin, 180)
    // }
    return ok_mois;
}

//writing the analytical form of the first-order derivatives of H(theta,fi) (first partial deriv)
double dH_dTheta(double I, double theta, double fi, FitParameters &params)
{
    // theta = theta * Lu163.PI / 180.0;
    // fi = fi * Lu163.PI / 180.0;
    auto a1 = IF(params.I1);
    auto a2 = IF(params.I2);
    auto a3 = IF(params.I3);
    return static_cast<double>(I * (I - 0.5) * sin(2.0 * theta) * (a1 * pow(cos(fi), 2) + a2 * pow(sin(fi), 2) - a3) - 2.0 * I * a1 * Lu163.j * cos(theta));
}

//writing the analytical form of the first-order derivatives of H(theta,fi) (second partial deriv)
double dH_dFi(double I, double theta, double fi, FitParameters &params)
{
    // theta = theta * Lu163.PI / 180.0;
    // fi = fi * Lu163.PI / 180.0;
    auto a1 = IF(params.I1);
    auto a2 = IF(params.I2);
    return static_cast<double>(I * (I - 0.5) * (a2 - a1) * pow(sin(theta), 2) * sin(2.0 * fi));
}

//Testing the computation of the partial derivatives and other relevant quantities with Mathematica
void TestPartials(double I, FitParameters &params)
{
    std::ofstream gout("/Users/basavyr/Library/Mobile Documents/com~apple~CloudDocs/Work/Pipeline/DFT/163Lu-New-TSD4-Formalism/Resources/Output_Data/Energy_Function/H_Partials.dat");
    for (auto theta = 0; theta <= 180; theta += 10)
    {
        for (auto fi = 0; fi <= 360; fi += 10)
        {
            auto theta_rad = theta * Lu163.PI / 180.0;
            auto fi_rad = fi * Lu163.PI / 180.0;
            gout << theta << " " << fi << " " << DH(theta_rad, fi_rad, I, params).dH_dTheta << " " << DH(theta_rad, fi_rad, I, params).dH_dFi << "\n";
        }
    }
}

//Testing the computation of the partial discriminant and second-order partial derivatives
void TestValues(double I, FitParameters &params)
{
    for (auto theta = 0; theta <= 40; theta += 10)
    {
        for (auto fi = 0; fi <= 40; fi += 10)
        {
            auto theta_rad = theta * Lu163.PI / 180.0;
            auto fi_rad = fi * Lu163.PI / 180.0;
            std::cout << theta << " " << fi << " " << D_Operator(params, theta_rad, fi_rad, I) << " " << D2H(theta_rad, fi_rad, I, params).dH_dTheta << "\n";
        }
    }
}

struct coordinates
{
    double theta;
    double fi;
};

//checking if all the points are in fact minimum or not
void Check_MinimalPoints(FitParameters &params, double I, std::vector<coordinates> &contains_minimum_points)
{
    //checking if all the points are in fact minimum or not
    double theta, fi;

    const double ZERO = 1.0e-8;

    coordinates coords;
    //the first point
    {
        fi = 0;
        theta = ThetaCritical(params.I1, params.I3, I);
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }

    //the second point
    {
        fi = 0;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }

    //the third point
    {
        fi = Lu163.PI / 2.0;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }

    //the fourth point
    {
        fi = Lu163.PI;
        theta = ThetaCritical(params.I1, params.I3, I);
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }

    //the fifth point
    {
        fi = Lu163.PI;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }

    //extra points from mathematica
    //the sixth point
    {
        fi = 2.0 * Lu163.PI;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }

    //extra points from mathematica
    //the seventh point
    {
        fi = 3.0 * Lu163.PI / 2.0;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            if (xx.dH_dTheta > 0.0 && discr > 0.0)
            {
                std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
                coords.theta = theta;
                coords.fi = fi;
                contains_minimum_points.emplace_back(coords);
            }
        }
    }
}

//checking if all the points are critical (null first order partial derivative)
void Check_CriticalPoints(FitParameters &params, double I)
{
    double theta, fi;

    const double ZERO = 1.0e-8;

    //the first point
    {
        fi = 0;
        theta = ThetaCritical(params.I1, params.I3, I);
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }

    //the second point
    {
        fi = 0;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }

    //the third point
    {
        fi = Lu163.PI / 2.0;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }

    //the fourth point
    {
        fi = Lu163.PI;
        theta = ThetaCritical(params.I1, params.I3, I);
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }

    //the fifth point
    {
        fi = Lu163.PI;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }

    //extra points from mathematica
    //the sixth point
    {
        fi = 2.0 * Lu163.PI;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }

    //extra points from mathematica
    //the seventh point
    {
        fi = 3.0 * Lu163.PI / 2.0;
        theta = Lu163.PI / 2.0;
        auto x = DH(theta, fi, I, params);
        auto xx = D2H(theta, fi, I, params);
        auto discr = D_Operator(params, theta, fi, I);
        // if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO && x.dH_dFi >= 0.0 && x.dH_dTheta >= 0.0)
        if (x.dH_dFi <= ZERO && x.dH_dTheta <= ZERO)
        {
            std::cout << theta * 180.0 / Lu163.PI << " " << fi * 180 / Lu163.PI << " " << x.dH_dTheta << " " << x.dH_dFi << " " << discr << " " << xx.dH_dTheta << "\n";
        }
    }
}

int main()
{
    //testing values
    double i1 = 20.0, i2 = 70.0, i3 = 53.0;
    double v = 9.1, gm_deg = 19.0;
    double gamma = gm_deg * Lu163.PI / 180.0;
    double SHIFT = 0.0;

    FitParameters fit_params(i1, i2, i3, v, gm_deg, SHIFT);

    double theta = 90;
    double fi = 180;
    double spin = 25.0 / 2.0;

    // Search_Valid_CriticalTheta(spin, v, gamma, SHIFT);
    std::cout << "Critical Points"
              << "\n";
    Check_CriticalPoints(fit_params, spin);
    std::cout << "Minimal Points"
              << "\n";

    std::vector<coordinates> has_minimum;
    Check_MinimalPoints(fit_params, spin, has_minimum);
    std::cout << has_minimum.size() << "\n";

    return 0;
}