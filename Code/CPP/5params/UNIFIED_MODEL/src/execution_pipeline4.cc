#include "rms_impl.hh"

int main()
{
    RMS_IMPL rms_impl;
    Approach_A A;
    Approach_B B;
    RMS_IMPL::Params_tuple params;
    std::ofstream file4("exe4.dat");
    rms_impl.Search_Minimum_RMS(B, 2, params);
    rms_impl.ShowResults_10(B, params, file4);
}