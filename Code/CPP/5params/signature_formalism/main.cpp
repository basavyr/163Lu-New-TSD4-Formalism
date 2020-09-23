#include "energies_0010.hh"
#include "energies_1230.hh"

int main()
{

    std::cout << "test the energies";
    std::cout << "\n";
    auto a1 = 1.0 / (2.0 * 73);
    auto a2 = 1.0 / (2.0 * 3);
    auto a3 = 1.0 / (2.0 * 67);
    auto v = 6.01;

    Bands_0010 bands_0010;
    Bands_1230 bands_1230;

    auto gm = 21 * bands_0010.PI / 180.0;
    std::vector<double> spins = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
    for (auto &&n : spins)
    {
        std::cout << n << " " << bands_0010.TSD1(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD2(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD3(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD4(n, a1, a2, a3, v, gm) << "\n";
    }
    for (auto &&n : spins)
    {
        std::cout << n << " " << bands_1230.TSD1(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD2(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD3(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD4(n, a1, a2, a3, v, gm) << "\n";
    }
    std::cout << "\n";
}