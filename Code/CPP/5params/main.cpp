#include <iostream>
#include <memory>
#include <utility>

#include "./include/app.h"
#include "./include/expdata.h"
#include "./include/energies.h"

int main()
{
    auto x = new app;
    x->~app();
    Formulas energies(0);
    std::cout << energies.E_Wobbling(1, 1, 2, 3, 3, 4, 5, 6, 7);
    std::cout << "\n";
}
