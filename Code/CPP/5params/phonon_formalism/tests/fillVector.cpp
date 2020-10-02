//Testing the time performance of computing a sum by filling a vector or just by direct computations
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <array>

static constexpr int arr_size = 2000;

std::vector<double> static_filler(arr_size);

double fct(double a, double b, double c, double p, double q)
{
    auto retval = a + b + c * (p + q);
    return static_cast<double>(retval);
}

std::vector<double> FillDynamic(size_t size, double a, double b, double c, double p, double q)
{
    std::vector<double> v;
    for (auto id = 0; id < size; ++id)
    {
        auto v_elem = fct(a, b, c, p, q);
        if (!isnan(v_elem))
            v.emplace_back(v_elem);
    }
    return v;
}

std::vector<double> FillStatic(std::vector<double> &v, double a, double b, double c, double p, double q)
{
    for (auto id = 0; id < v.size(); ++id)
    {
        auto v_elem = fct(a, b, c, p, q);
        if (!isnan(v_elem))
            v[id] = v_elem;
    }
    return v;
}

void Filling(bool ok)
{
    auto minval = 0;
    auto maxval = 10;
    auto start = std::chrono::system_clock::now();
    for (auto I1 = minval; I1 < maxval; ++I1)
    {
        for (auto I2 = minval; I2 < maxval; ++I2)
        {
            for (auto I3 = minval; I3 < maxval; ++I3)
            {
                for (auto p = minval; p < maxval; ++p)
                {
                    for (auto q = minval; q < maxval; ++q)
                    {
                        if (ok)
                            auto x = FillDynamic(arr_size, I1, I2, I3, p, q);
                        else
                        {
                            /* code */
                            auto x = FillStatic(static_filler, I1, I2, I3, p, q);
                        }
                    }
                }
            }
        }
    }
    auto stop = std::chrono::system_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << "Process took: " << duration_ms / 1000.0;
    std::cout << "\n";
}

int main()
{
    std::cout << "Dynamic allocation..."
              << "\n";
    Filling(1);
    std::cout << "Static allocation..."
              << "\n";
    Filling(0);
}