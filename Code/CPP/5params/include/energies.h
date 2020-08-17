#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

class Formulas
{
private:
    static constexpr double error_number = 6969.0;
    std::string debug_ON = "Debugger is ON...";
    std::string debug_OFF = "Debugger is OFF...";
    bool debug;

public:
    static constexpr double PI = 3.141592654;
    double Omega1(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double Omega2(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double BTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double CTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    double Hmin(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    static int ValidNumbers(double);

public:
    Formulas(bool);
    ~Formulas();

    //helper functions
public:
    static double InertiaFactor(double I);
};
