#include <iostream>
#include <memory>
#include <utility>

#include "./include/app.h"
#include "./include/expdata.h"

int main()
{
    auto x = new app;
    x->~app();
    expdata Lu163;
    for (auto &&n : Lu163.tsd1)
    {
        std::cout << n << " ";
    }
    std::cout << "\n";
}