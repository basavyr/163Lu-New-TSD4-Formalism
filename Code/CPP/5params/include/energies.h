#include <cmath>
#include <algorithm>
#include <vector>

class Formulas
{
private:
    static constexpr double error_number = 6969.0;

public:
    static double Omega1(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    static double Omega2(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    static double BTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    static double CTerm(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);
    static double Hmin(double spin, double oddSpin, double i1, double i2, double i3, double V, double gamma);

    //helper functions
public:
    static double InertiaFactor(double I);
};
