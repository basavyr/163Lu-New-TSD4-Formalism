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
    std::cout << Formulas::Omega1(1, 1, 1, 1, 1, 1, 1);
    std::cout << "\n";
}