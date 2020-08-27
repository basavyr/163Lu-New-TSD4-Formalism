#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <vector>

const double i_min = 1;
const double i_max = 100;
const double i_step = 1;

double fct(double a, double b, double c)
{
    return a * b + log(c) * a * a + pow(b, sin(a));
}

int Delta_Check(double delta, double i1, double i2, double i3)
{
    auto d12 = abs(i1 - i2);
    auto d23 = abs(i2 - i3);
    auto d13 = abs(i1 - i3);
    if (d12 >= delta && d13 >= delta && d23 >= delta)
        return 1;
    return 0;
}

void TestDelta(double delta, double i_max)
{
    auto start = std::chrono::system_clock::now();
    std::vector<double> math;
    for (auto i = i_min; i < i_max; i += i_step)
    {
        for (auto j = i_min; j < i_max; j += i_step)
        {
            for (auto k = i_min; k < i_max; k += i_step)
            {
                if (Delta_Check(delta, i, j, k))
                {
                    auto element = fct(i, j, k);
                    if (!isnan(element))
                    {
                        math.emplace_back(element);
                        // std::cout << i << " " << j << " " << k << "\n";
                    }
                }
            }
        }
    }
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
    std::cout << static_cast<double>(duration_ms / 1000.0) << " " << math.size();
    std::cout << "\n";
    // std::cout << math.size();
}

int main()
{
    auto start = std::chrono::system_clock::now();
    int n_iter = 5;
    std::cout << "{";
    for (auto id = 1; id <= n_iter; ++id)
    {
        TestDelta(id*2, i_max);
    }
    std::cout << "}";
    std::cout << "\n";

    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
    std::cout << "\n";
    std::cout << "Total execution time for " << n_iter << ": " << static_cast<double>(duration_ms / 1000.0) << " ";
    std::cout << "\n";
}