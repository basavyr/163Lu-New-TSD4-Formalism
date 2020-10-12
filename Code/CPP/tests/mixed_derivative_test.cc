#include <iostream>
#include <cmath>

const double PI = 3.141592654;

double f(double x, double y)
{
    return static_cast<double>(2.0 * sin(x) * pow(y, 2) + pow(x, 2) * y);
}

double df_dx(double x, double y)
{
    double h = 0.00001;

    auto fx_2h = f(x + 2.0 * h, y);
    auto fx_h = f(x + h, y);
    auto fx_mh = f(x - 1.0 * h, y);
    auto fx_m2h = f(x - 2.0 * h, y);

    return static_cast<double>((-fx_2h + 8.0 * fx_h - 8.0 * fx_mh + fx_m2h) / (12.0 * h));
}

double df_dy(double x, double y)
{
    double h = 0.00001;

    auto fy_2h = f(x, y + 2.0 * h);
    auto fy_h = f(x, y + h);
    auto fy_mh = f(x, y - 1.0 * h);
    auto fy_m2h = f(x, y - 2.0 * h);

    return static_cast<double>((-fy_2h + 8.0 * fy_h - 8.0 * fy_mh + fy_m2h) / (12.0 * h));
}

double df_dxdy(double x, double y)
{
    double h = 0.00001;

    auto f_11 = f(x + h, y + h);
    auto f_m1m1 = f(x - h, y - h);
    auto f_1m1 = f(x + h, y - h);
    auto f_m11 = f(x - h, y + h);
    return static_cast<double>((f_11 - f_1m1 - f_m11 + f_m1m1) / (4.0 * pow(h, 2)));
}

struct diff
{
    double dx;
    double dy;
};
//Computes the partial derivative of H to both variables
diff df(double x, double y)
{
    double h = 0.00001;

    auto fx_2h = f(x + 2.0 * h, y);
    auto fx_h = f(x + h, y);
    auto fx_mh = f(x - 1.0 * h, y);
    auto fx_m2h = f(x - 2.0 * h, y);

    auto fy_2h = f(x, y + 2.0 * h);
    auto fy_h = f(x, y + h);
    auto fy_mh = f(x, y - 1.0 * h);
    auto fy_m2h = f(x, y - 2.0 * h);

    auto dx = static_cast<double>((-fx_2h + 8.0 * fx_h - 8.0 * fx_mh + fx_m2h) / (12.0 * h));
    auto dy = static_cast<double>((-fy_2h + 8.0 * fy_h - 8.0 * fy_mh + fy_m2h) / (12.0 * h));

    diff Diff;
    Diff.dx = dx;
    Diff.dy = dy;
    return Diff;
}

int main()
{
    auto x_0 = 0.0;
    auto y_0 = 1.0;
    for (auto x = 1; x < 3; ++x)
    {
        for (auto y = 1; y < 3; ++y)
        {
            std::cout << x << " " << y << " " << df(x, y).dx << " " << df(x, y).dy << " " << df_dxdy(x, y) << "\n";
        }
    }
    return 0;
}