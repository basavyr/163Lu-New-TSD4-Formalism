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
    // std::cout << energies.BTerm(1, 2, 0, 0, 0, 1, 1);
    std::cout << Formulas::ValidNumbers(6969);
}