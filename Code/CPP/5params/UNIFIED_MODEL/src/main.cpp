#include <iostream>
#include <fstream>
#include "../include/approachA.h"
#include "../include/approachB.h"

void App()
{
    std::cout << "UNIFIED MODEL..."
              << "\n";
}

void print(double var)
{
    std::cout << var << "\n";
}

void print_array(std::string arr_name, std::vector<double> &arr)
{
    std::cout << arr_name << " = {";
    for (auto id = 0; id < arr.size(); ++id)
    {
        if (id != arr.size() - 1)
            std::cout << arr.at(id) << " , ";
        else
        {
            std::cout << arr.at(id);
        }
    }
    std::cout << "}"
              << "\n";
}

int main()
{
    Approach_A A;
    Approach_B B;

    std::vector<double> a1 = {1, 2, 3, 4, 4};
    print_array("E_TSD1", a1);
    print_array("E_TSD2", a1);
    print_array("E_TSD3", a1);
    print_array("E_TSD4", a1);
}