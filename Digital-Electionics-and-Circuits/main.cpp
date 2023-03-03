#include "circuits2.hpp"
#include "DigitalElec.hpp"
#include "conversion.hpp"
using namespace Hugh::Circuits2;
using namespace Hugh::DigitalElectronics;

int main()
{
    // Vs is ALWAYS the terminal at the lower voltage
    // Vt is threshold voltage
    // Vtp == Threshold voltage
    // Vsb = Vs - Vb
    // Vb not shown so it's tied to the lowest supply voltage for NMOS, and HIGHEST for PMOS
    // If lambdan is not given, take it as 0
    // Vb is 0 unless otherwise stated
    double Vg = 1;
    double Vs = 0;
    double Vb = 0;
    double Vd = .24806;
    double gamma = .3;
    double Phi = (.4);
    double Vt = .3;
    double Vsb = Vs - Vb;
    double Vgs = Vg - Vs;
    double Vtn = Vt + (Vsb == 0 ? 0 : gamma * (sqrt(fabs(2 * Phi) + Vsb) - sqrt(fabs(2 * Phi))));
    double Vds = Vd - Vs;
    DigETuple<TransistorPhase> Thing = currentSCMNMOSNOVANNOCOX(Vgs, Vtn, Vds, 200, 0, 3, .6);
    Vg = 1;
    Vs = .24806;
    Vb = .24806;
    Vd = 1;
    gamma = .3;
    Phi = (.4);
    Vt = .3;
    Vsb = Vs - Vb;
    Vgs = Vg - Vs;
    Vtn = Vt + (Vsb == 0 ? 0 : gamma * (sqrt(fabs(2 * Phi) + Vsb) - sqrt(fabs(2 * Phi))));
    Vds = Vd - Vs;
    DigETuple<TransistorPhase> oThing = currentSCMNMOSNOVANNOCOX(Vgs, Vtn, Vds, 200, 0, 6, .6);
    std::cout
        << Thing << std::endl;
    std::cout << oThing << std::endl;
}
