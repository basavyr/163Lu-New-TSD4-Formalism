#include <iostream>

#include "./include/expdata.h"
#include "./include/rms.h"
#include "./include/energies.h"

bool ok = 0;

inline void newline()
{
    std::cout<<"\n";
}

int main()
{
    ok = 1;
    if (ok)
    {
        std::cout << "App runs OK";
        newline();
    }

    expdata Lu163;
    Lu163.ShowVector<double>(Lu163.spin1);
    newline();
}