#include <chrono>
#include <iostream>
#include <cstring>
#include <ctime>

class app
{
private:
    std::chrono::system_clock::time_point now;
    std::string app_name;

public:
    app(/* args */);
    ~app();
};