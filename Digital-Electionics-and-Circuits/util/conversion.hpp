#include "constants.hpp"
namespace Hugh
{
    namespace Util
    {
#pragma region operators
        long double operator"" _km(long double d)
        {
            return d * 1000;
        }
        long double operator"" _m(long double d)
        {
            return d;
        }
        long double operator"" _mm(long double d)
        {
            return d * 0.001;
        }
        unsigned long long int operator"" _mm(unsigned long long int d)
        {
            return d / 1000;
        }
        long double operator"" _um(long double d)
        {
            return d * 0.000001;
        }
        unsigned long long int operator"" _um(unsigned long long int d)
        {
            return d / 1000000;
        }
        long double operator"" _nm(long double d)
        {
            return d * 1e-09;
        }
        long double operator"" _hz(long double d)
        {
            return d * (2 * M_PI);
        }
        long double operator"" _khz(long double d)
        {
            return d * 1000 * (2 * M_PI);
        }
        long double operator"" _deg(long double d)
        {
            return d / 57.2957795;
        }
        long double fromkilo(long double d)
        {
            return d * 1000;
        }
        constexpr double toMilli(double d)
        {
            return d * 1000;
        }
        constexpr double fromMilli(double d)
        {
            return d / 1000;
        }
        constexpr double toMicro(double d)
        {
            return d * 1e+6;
        }
        constexpr double fromMicro(double d)
        {
            return d * 1e-6;
        }
        constexpr double toNano(double d)
        {
            return d * 1e+9;
        }
        constexpr double fromNano(double d)
        {
            return d * 1e-9;
        }
        constexpr double toPico(double d)
        {
            return d * 1e+12;
        }
        constexpr double fromPico(double d)
        {
            return d * 1e-12;
        }
        constexpr double toFemto(double d)
        {
            return d * 1e+15;
        }
        constexpr double fromFemto(double d)
        {
            return d * 1e-15;
        }
#pragma endregion
    }
}