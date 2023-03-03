#include <complex>
#include <ostream>
namespace Hugh
{
    namespace Circuits2
    {
        double bandwith_series(double R, double L, double C)
        {
            return R / L;
        }
        double bandwith_parallel(double R, double L, double C)
        {
            return 1 / (R * C);
        }
        double bandwidthfromHalf_parallel(double w1, double w2)
        {
            return w2 - w1;
        }
        double bandwidthfromQuality(double Q, double resonance)
        {
            return resonance / Q;
        }
        double capacitancefromQuality(double Q, double R, double resonance)
        {
            return Q / (resonance * R);
        }
        double inductancefromQuality(double Q, double R, double resonance)
        {
            return R / (Q * resonance);
        }
        double resonance_parallel(double R, double L, double C)
        {
            return 1 / sqrt(L * C);
        }
        double resonance_series(double R, double L, double C)
        {
            return 1 / sqrt(L * C);
        }
        double qualityfromBandwidth(double B, double resonance)
        {
            return resonance / B;
        }
        double qualityfromcapacitance(double R, double C, double resonance)
        {
            return R * C * resonance;
        }
        double qualityfromInductance(double R, double L, double resonance)
        {
            return R / (resonance * L);
        }
        double capacitancefromBandwidth_parallel(double B, double R)
        {
            return 1 / (B * R);
        }
        double inductancefromw2_parallel(double w2, double R, double C)
        {
            return R / (w2 * w2 * R * C - w2);
        }
        double resonance(double w1, double w2)
        {
            return sqrt(w1 * w2);
        }
        double scale_resistance_mag_freq(double resistance, double mag, double freq)
        {
            return mag * resistance;
        }
        double scale_inductance_mag_freq(double inductance, double mag, double freq)
        {
            return (mag / freq) * inductance;
        }
        double scale_capacitance_mag_freq(double capacitance, double mag, double freq)
        {
            return (1 / (mag * freq)) * capacitance;
        }
        double inductance_from_bandwidth_and_resistance_series(double bandwidth, double resistance)
        {
            return resistance / bandwidth;
        }
        double capacitance_from_resonance_and_inductance_series(double resonance, double inductance)
        {
            return 1 / (resonance * resonance * inductance);
        }
        double half_power_starter_parallel(double resistance, double inductance, double capacitence)
        {
            return (1 / (2 * resistance * capacitence));
        }
        double half_power_starter_series(double resistance, double inductance, double capacitence)
        {
            return resistance / (2 * inductance);
        }
        double half_power_consistent(double resistance, double inductance, double capacitence)
        {
            return sqrt(pow(half_power_starter_series(resistance, inductance, capacitence), 2) +
                        (1 / (inductance * capacitence)));
        }
        double half_power_1_series(double resistance, double inductance, double capacitence)
        {
            return -half_power_starter_series(resistance, inductance, capacitence) +
                   half_power_consistent(resistance, inductance, capacitence);
        }
        double half_power_2_series(double resistance, double inductance, double capacitence)
        {
            return half_power_starter_series(resistance, inductance, capacitence) +
                   half_power_consistent(resistance, inductance, capacitence);
        }
        double half_power_1_parallel(double resistance, double inductance, double capacitence)
        {
            return -half_power_starter_parallel(resistance, inductance, capacitence) +
                   half_power_consistent(resistance, inductance, capacitence);
        }
        double half_power_2_parallel(double resistance, double inductance, double capacitence)
        {
            return half_power_starter_parallel(resistance, inductance, capacitence) +
                   half_power_consistent(resistance, inductance, capacitence);
        }
        // This is the polar form from an std::complex, stored in polar for easy conversion
        struct polar_form
        {
            double r;
            double theta;
            polar_form(std::complex<double> from)
            {
                r = std::sqrt(from.imag() * from.imag() + from.real() * from.real());
                theta = std::atan(from.imag() / from.real());
            }
            polar_form(double r, double theta)
            {
                this->r = r;
                this->theta = theta;
            }
            std::complex<double> to_rect()
            {
                return std::polar(r, theta);
            }
            friend std::ostream &operator<<(std::ostream &os, const polar_form &polar)
            {
                os << "R: " << polar.r << " Theta: " << polar.theta * 57.2957795 << " Degrees";
                return os;
            }
        };

        std::complex<double> transfer(double frequency, double R, double L, double C)
        {
            std::complex<double> Numerator = R * L * C * (std::pow(std::complex<double>(0, frequency), 2) + (1 / (L * C)));
            std::complex<double> Denominator = R * L * C *
                                               (std::pow(std::complex<double>(0, frequency), 2) +
                                                (std::complex<double>(0, frequency) / (R * C)) + (1 / (L * C)));
            return Numerator / Denominator;
        }
        std::complex<double> impedence(double w, double R1, double R2, double L1, double L2, double k, std::complex<double> ZL);
        enum class Value
        {
            lower,
            higher
        };
        // This is for when I'm tired of dealing with Ideal Transformers
        // Get turns ratio, that's simple, then determine to negate or not
        // Chainable too
        std::complex<double> impedence(Value FirstInductor, Value SecondInductor, double firstNum, double secondNum,
                                       std::complex<double> firstImpedence, std::complex<double> secondImpedence)
        {
            double N = secondNum / firstNum;
            if (FirstInductor != SecondInductor)
            {
                N = -N;
            }
            std::complex<double> reflectedImpedence = firstImpedence + (secondImpedence / std::pow(N, 2));
            return reflectedImpedence;
        }

        std::complex<double> primaryImpedence(std::complex<double> R1, double L1)
        {
            return R1 + std::complex<double>(0, L1);
        }
        std::complex<double> primaryImpedence(double w, double R1, double L1)
        {
            return std::complex<double>(R1, L1 * w);
        }
        std::complex<double> reflectedImpedence(double w, std::complex<double> M, double R2, double L2, std::complex<double> ZL)
        {
            std::complex<double> top = w * w * std::pow(M, 2);
            std::complex<double> bottom = std::complex<double>(R2, w * L2) + ZL;
            return top / bottom;
        }
        std::complex<double> reflectedImpedence(std::complex<double> M, std::complex<double> R2, double L2,
                                                std::complex<double> ZL)
        {
            std::complex<double> top = std::pow(M, 2);
            std::complex<double> bottom = R2 + std::complex<double>(0, L2) + ZL;
            return top / bottom;
        }
        std::complex<double> impedence(std::complex<double> R1, std::complex<double> R2, double L1, double L2, double M,
                                       std::complex<double> ZL)
        {
            return primaryImpedence(R1, L1) + reflectedImpedence(M, R2, L2, ZL);
        }
        std::complex<double> impedence(double w, double R1, double R2, double L1, double L2, double k, std::complex<double> ZL)
        {
            return primaryImpedence(w, R1, L1) + reflectedImpedence(w, k * std::sqrt(L1 * L2), R2, L2, ZL);
        }
    }
}