#include "../include/app.h"

app::app()
{
    now = std::chrono::system_clock::now();
    app_name = "Lu163 - 5 Parameters Implementation.";
}

app::~app()
{
    auto time = std::chrono::system_clock::to_time_t(now);
    std::cout << app_name;
    std::cout << "\n";
    std::cout << ctime(&time);
}