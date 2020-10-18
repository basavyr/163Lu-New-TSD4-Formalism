#include "../include/energies.hh"

#include <iostream>
#include <fstream>

#include <cmath>
#include <algorithm>
#include <vector>

//constants for easy-access
const double PI = 3.141592654;

//?Initializing the analytical formulas as a class object instance at the start of the main implementation
Energies Lu163;

double IF(double MOI)
{
    return static_cast<double>(1.0 / (2.0 * MOI));
}

int main()
{
    return 0;
}