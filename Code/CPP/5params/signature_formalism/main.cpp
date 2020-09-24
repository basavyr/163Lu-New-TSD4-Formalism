#include "energies_0010.hh"
#include "energies_1230.hh"

const std::vector<double> spin1 = {8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5, 44.5, 46.5, 48.5};
const std::vector<double> spin2 = {13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5, 43.5, 45.5};
const std::vector<double> spin3 = {16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 32.5, 34.5, 36.5, 38.5, 40.5, 42.5};
const std::vector<double> spin4 = {23.5, 25.5, 27.5, 29.5, 31.5, 33.5, 35.5, 37.5, 39.5, 41.5};
const std::vector<double> tsd1 = {0.1966, 0.4597, 0.7746, 1.1609, 1.6112, 2.1265, 2.7051, 3.3441, 4.0411, 4.7937, 5.5992, 6.457, 7.3667, 8.3293, 9.3458, 10.4169, 11.5431, 12.7224, 13.9491, 15.2181, 16.5221};
const std::vector<double> tsd2 = {1.3394, 1.7467, 2.2184, 2.7527, 3.3484, 4.003, 4.7143, 5.4805, 6.3004, 7.1733, 8.0998, 9.08, 10.1147, 11.2036, 12.3466, 13.5441, 14.7911};
const std::vector<double> tsd3 = {2.1237, 2.6293, 3.1973, 3.8243, 4.5094, 5.2506, 6.0465, 6.8963, 7.7988, 8.7546, 9.7638, 10.8268, 11.9392, 13.0861};
const std::vector<double> tsd4 = {4.58, 5.2251, 5.9273, 6.6819, 7.4919, 8.3573, 9.2778, 10.2535, 11.2851, 12.3701};
const std::vector<int> gm = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

double rms(Bands_0010 &nucleus, double a1, double a2, double a3, double v)
{

    double best_rms = 9876543210.0;
    double E;
    double sum = 0.0;
    double gamma = gm.at(6);
    bool ok = 1;
    int count = 0;
    {
        std::cout << "Started TSD1...";
        std::cout << "\n";
        for (auto id = 0; id < spin1.size() && ok; ++id)
        {
            E = nucleus.TSD1(spin1.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                ok = 0;
                std::cout << "Failed inside TSD1 at I=" << spin1.at(id);
                std::cout << "\n";
                break;
            }
            else
            {
                sum += pow(E - tsd1.at(id), 2);
                count++;
            }
        }
        std::cout << "Started TSD2...";
        std::cout << "\n";
        for (auto id = 0; id < spin2.size() && ok; ++id)
        {
            E = nucleus.TSD2(spin2.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd2.at(id), 2);
                count++;
            }
        }
        std::cout << "Started TSD3...";
        std::cout << "\n";
        for (auto id = 0; id < spin3.size() && ok; ++id)
        {
            E = nucleus.TSD3(spin3.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd3.at(id), 2);
                count++;
            }
        }
        std::cout << "Started TSD4...";
        std::cout << "\n";
        for (auto id = 0; id < spin4.size() && ok; ++id)
        {
            E = nucleus.TSD4(spin4.at(id), a1, a2, a3, v, gamma * nucleus.PI / 180.0);
            if (!nucleus.valid(E))
            {
                ok = 0;
                break;
            }
            else
            {
                sum += pow(E - tsd4.at(id), 2);
                count++;
            }
        }
    }
    if (count == 62)
        std::cout << sqrt(sum / 63.0) << "\n";
    return count;
}

int main()
{
    //The bands initialization procedure
    Bands_0010 bands_0010;

    //The constants used in computations (testing purposes only)
    auto a1 = 1.0 / (2.0 * 73.0);
    auto a2 = 1.0 / (2.0 * 3.0);
    auto a3 = 1.0 / (2.0 * 67.0);
    auto v = 6.01;
    // auto gm = 21.0 * bands_0010.PI / 180.0;

    std::cout << rms(bands_0010, a1, a2, a3, v);
    // for (auto &&n : spin1)
    // {
    //     std::cout << n << " " << bands_0010.TSD1(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD2(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD3(n, a1, a2, a3, v, gm) << " " << bands_0010.TSD4(n, a1, a2, a3, v, gm) << "\n";
    // }
    // for (auto &&n : spins)
    // {
    //     std::cout << n << " " << bands_1230.TSD1(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD2(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD3(n, a1, a2, a3, v, gm) << " " << bands_1230.TSD4(n, a1, a2, a3, v, gm) << "\n";
    // }
    std::cout << "\n";
}