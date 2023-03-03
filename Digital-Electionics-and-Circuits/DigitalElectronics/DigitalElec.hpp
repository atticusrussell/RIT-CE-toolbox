#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
namespace Hugh
{
    namespace DigitalElectronics
    {
        enum class TransistorPhase
        {
            SATURATED,
            TRIODE,
            OFF,
            DONTCARE
        };
        enum class ActivationMode
        {
            NMOS,
            PMOS,
            CMOS
        };
        enum class ElectricType
        {
            VOLTAGE,
            CURRENT,
            TIME
        };
        enum class TransistorCalcModel
        {
            LONGCHANNEL,
            SHORTCHANNEL,
            // THIS IS AN ALIAS FOR THE LONG CHANNEL MODEL
            LCM = LONGCHANNEL,
            // THIS IS AN ALIAS FOR THE SHORT CHANNEL MODEL
            SCM = SHORTCHANNEL
        };
        template <class T>
        struct DigETuple
        {
            T state;
            double value;
            ElectricType electricType = ElectricType::CURRENT;
            std::stringstream string_buffer; // Take a list of the equations we want
            // specialize this per enum for DigETuple, may want to use MagicEnum here
            friend std::ostream &operator<<(std::ostream &os, const DigETuple<T> &tuple);
            bool operator==(DigETuple<T> b)
            {
                if ((this->value + .001) > b.value && (this->value - .001) < b.value)
                {
                    return true;
                }
                return false;
            }
            DigETuple<T> &SetAppend(const DigETuple<T> &other)
            {
                if (this == &other)
                {
                    return *this;
                }
                this->state = other.state;
                this->value = other.value;
                this->electricType = other.electricType;
                this->string_buffer << other.string_buffer.str();
                return *this;
            }
        };
        std::ostream &operator<<(std::ostream &os, const DigETuple<TransistorPhase> &tuple)
        {
            os << tuple.string_buffer.str() << std::endl;
            switch (tuple.electricType)
            {
            case ElectricType::CURRENT:
            {
                os << "Phase of transistor: ";
                switch (tuple.state)
                {
                case TransistorPhase::SATURATED:
                    os << "SATURATED";
                    break;
                case TransistorPhase::TRIODE:
                    os << "TRIODE";
                    break;
                case TransistorPhase::OFF:
                    os << "OFF";
                    break;
                default:
                    assert(false);
                    break;
                }
            }
            break;
            case ElectricType::VOLTAGE:
            {
                os << "Phase of transistor: ";
                switch (tuple.state)
                {
                case TransistorPhase::SATURATED:
                    os << "SATURATED";
                    break;
                case TransistorPhase::TRIODE:
                    os << "TRIODE";
                    break;
                case TransistorPhase::OFF:
                    os << "OFF";
                    break;
                case TransistorPhase::DONTCARE:
                    os << "DONTCARE";
                    break;
                default:
                    assert(false);
                    break;
                }
            }
            break;
            case ElectricType::TIME:
            {
            }
            default:
                break;
            }

            os << " The value of the ";
            switch (tuple.electricType)
            {
            case ElectricType::TIME:
                os << "time";
                break;
            case ElectricType::VOLTAGE:
                os << "voltage";
                break;
            case ElectricType::CURRENT:
                os << "current";
                break;
            }
            os << " is: " << tuple.value << std::endl;
            return os;
        }

        DigETuple<TransistorPhase> currentSCMNMOSNOVANNOCOX(double Vgs, double Vtn, double Vds, double k, double lambdan, double ecnln)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            double Vgstn = Vgs - Vtn;
            returnval.string_buffer << "Vgstn = Vgs - Vtn: " << Vgstn << " = " << Vgs << " - " << Vtn << std::endl;
            double VDSsat = (Vgstn * ecnln) / (Vgstn + ecnln);
            returnval.string_buffer << "VDSsat = (Vgstn * ecnln) / (Vgstn + ecnln): " << VDSsat << " = (" << Vgstn << " * " << ecnln << ") / (" << Vgstn << " + " << ecnln << ")" << std::endl;
            if (VDSsat <= 0)
            {
                std::cerr << "VDSsat is below 0, erroring, VDSSat: " << VDSsat << std::endl;
            }
            if (Vds <= 0)
            {
                std::cerr << "VDs is below 0, erroring, Vds: " << Vds << std::endl;
            }
            if (lambdan < 0)
            {
                std::cerr << "lambdan is below 0, erroring, lambdan:" << lambdan << std::endl;
            }
            if (Vgs < Vtn)
            {
                returnval.string_buffer << "Vgs < Vtn: " << Vgs << " < " << Vtn << std::endl;
                return returnval;
            }
            if (Vgs > Vtn && Vds <= VDSsat)
            {
                returnval.state = TransistorPhase::TRIODE;
                returnval.value = (k / (1 + (Vds / ecnln))) * ((Vgstn * Vds) - ((Vds * Vds) / 2));
                returnval.string_buffer << "Vgs > Vtn: " << Vgs << " > " << Vtn << std::endl;
                returnval.string_buffer << "Vds <= VDSSat: " << Vds << " <= " << VDSsat << std::endl;
                returnval.string_buffer << "Id = (k / (1 + (Vds / ecnln) * ((Vgstn * Vds) - ((Vds * Vds) / 2)): " << std::endl;
                returnval.string_buffer << returnval.value << " = (" << k << " / (1 + (" << Vds << " / " << ecnln << ") * ((" << Vgstn << " * " << Vds << ") - ((" << Vds << " * " << Vds << " / 2))" << std::endl;
                return returnval;
            }
            if (Vgs > Vtn && Vds >= VDSsat)
            {
                returnval.state = TransistorPhase::SATURATED;
                returnval.value = ((k / 2) * ecnln) * ((Vgstn * Vgstn) / (Vgstn + ecnln)) * (1 + lambdan * (Vds - VDSsat));
                returnval.string_buffer << "Vgs > Vtn: " << Vgs << " > " << Vtn << std::endl;
                returnval.string_buffer << "Vds >= VDSSat: " << Vds << " >= " << VDSsat << std::endl;
                returnval.string_buffer << "Id = ((k / 2) * ecnln) * ((Vgstn * Vgstn) / (Vgstn + ecnln)) * (1 + lambdan * (Vds - VDSsat)): " << std::endl;
                returnval.string_buffer << returnval.value << " = ((" << k << " / 2) * " << ecnln << " ) * ((" << Vgstn << " * " << Vgstn << ") / (" << Vgstn << " + " << ecnln << ")) * (1 + " << lambdan << " * (" << Vds << " - " << VDSsat << "))" << std::endl;
                return returnval;
            }
            return returnval;
        }
        // Short Channel Model using Lambdan and kprime and ecnln
        DigETuple<TransistorPhase> currentSCMNMOSNOVANNOCOX(double Vgs, double Vtn, double Vds, double kprime, double lambdan, double WL, double ecnln)
        {
            return currentSCMNMOSNOVANNOCOX(Vgs, Vtn, Vds, WL * kprime, lambdan, ecnln);
        }
        // Vto == Vtn or Vtp
        DigETuple<TransistorPhase> currentSCMNMOS(double Vgs, double Vtn, double Cox, double Un, double W, double L, double Vds, double Van, double Ecn, double Ln)
        {
            return currentSCMNMOSNOVANNOCOX(Vgs, Vtn, Vds, Un * Cox, 1 / Van, W / L, Ecn * Ln);
        }
        DigETuple<TransistorPhase> currentSCMNMOS(double Vgs, double Vtn, double Cox, double Un, double W, double L, double Vds, double Van, double EcnLn)
        {
            return currentSCMNMOSNOVANNOCOX(Vgs, Vtn, Vds, Un * Cox, 1 / Van, W / L, EcnLn);
        }
        DigETuple<TransistorPhase> currentSCMNMOSNoVan(double Vgs, double Vtn, double Cox, double Un, double W, double L, double Vds, double lambdan, double EcnLn)
        {
            return currentSCMNMOSNOVANNOCOX(Vgs, Vtn, Vds, Un * Cox, lambdan, W / L, EcnLn);
        }

        DigETuple<TransistorPhase> currentLCMNMOS(double Vgs, double Vtn, double Cox, double Un, double W, double L, double Vds, double Van)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            double lambdan = 1 / (Van);
            double VDSsat = Vgs - Vtn;
            double knprime = Un * Cox;
            double WL = W / L;
            if (VDSsat <= 0)
            {
                std::cerr << "VDSsat is below 0, erroring, VDSSat: " << VDSsat << std::endl;
            }
            if (Vds <= 0)
            {
                std::cerr << "VDs is below 0, erroring, Vds: " << Vds << std::endl;
            }
            if (lambdan < 0)
            {
                std::cerr << "lambdan is below 0, erroring, lambdan:" << lambdan << std::endl;
            }
            if (Vgs < Vtn)
            {
                returnval.state = TransistorPhase::OFF;
                returnval.value = 0;
                return returnval;
            }
            if (Vgs > Vtn && Vds <= VDSsat)
            {
                returnval.state = TransistorPhase::TRIODE;
                returnval.value = knprime * WL * (((Vgs - Vtn) * Vds) - ((Vds * Vds) / 2));
                return returnval;
            }
            if (Vgs > Vtn && Vds >= VDSsat)
            {
                returnval.state = TransistorPhase::SATURATED;
                returnval.value = (knprime / 2) * WL * (Vgs - Vtn) * (Vgs - Vtn) * (1 + lambdan * (Vds - VDSsat));
                return returnval;
            }
            return returnval;
        }
        DigETuple<TransistorPhase> currentSCMPMOSNOVANNOCOX(double Vsg, double Vtp, double Vsd, double k, double lambdap, double ecplp)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            double Vsgtp = Vsg + Vtp;
            double VSDsat = (Vsgtp * ecplp) / (Vsgtp + ecplp);
            if (VSDsat <= 0)
            {
                std::cerr << "VDSsat is below 0, erroring, VDSSat: " << VSDsat << std::endl;
            }
            if (Vsd <= 0)
            {
                std::cerr << "VDs is below 0, erroring, Vds: " << Vsd << std::endl;
            }
            if (lambdap < 0)
            {
                std::cerr << "lambdan is below 0, erroring, lambdan:" << lambdap << std::endl;
            }
            if (Vsg < -Vtp)
            {
                return returnval;
            }
            if (Vsg > -Vtp && Vsd <= VSDsat)
            {
                returnval.state = TransistorPhase::TRIODE;
                returnval.value = (k / (1 + (Vsd / ecplp))) * ((Vsgtp * Vsd) - ((Vsd * Vsd) / 2));
                return returnval;
            }
            if (Vsg > -Vtp && Vsd >= VSDsat)
            {
                returnval.state = TransistorPhase::SATURATED;
                returnval.value = ((k / 2) * ecplp) * ((Vsgtp * Vsgtp) / (Vsgtp + ecplp)) * (1 + lambdap * (Vsd - VSDsat));
                return returnval;
            }
            return returnval;
        }
        DigETuple<TransistorPhase> currentSCMPMOSNOVANNOCOX(double Vsg, double Vtp, double Vsd, double kprime, double lambdap, double WL, double ecplp)
        {
            return currentSCMPMOSNOVANNOCOX(Vsg, Vtp, Vsd, WL * kprime, lambdap, ecplp);
        }
        DigETuple<TransistorPhase> currentSCMPMOS(double Vsg, double Vtp, double Cox, double Up, double W, double L, double Vsd, double Vap, double Ecp, double Lp)
        {
            return currentSCMPMOSNOVANNOCOX(Vsg, Vtp, Vsd, Up * Cox, 1 / Vap, W / L, Ecp * Lp);
        }
        DigETuple<TransistorPhase> currentSCMPMOS(double Vsg, double Vtp, double Cox, double Up, double W, double L, double Vsd, double Vap, double EcpLp)
        {
            return currentSCMPMOSNOVANNOCOX(Vsg, Vtp, Vsd, Up * Cox, 1 / Vap, W / L, EcpLp);
        }
        DigETuple<TransistorPhase> currentSCMPMOSNoVan(double Vsg, double Vtp, double Cox, double Up, double W, double L, double Vsd, double lambdap, double EcpLp)
        {
            return currentSCMPMOSNOVANNOCOX(Vsg, Vtp, Vsd, Up * Cox, lambdap, W / L, EcpLp);
        }
        DigETuple<TransistorPhase> currentLCMPMOS(double Vsg, double Vtp, double Cox, double Up, double W, double L, double Vsd, double Vap)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            double VSDsat = Vsg + Vtp;
            double lambdap = 1 / Vap;
            if (VSDsat <= 0)
            {
                std::cerr << "VDSsat is below 0, erroring, VDSSat: " << VSDsat << std::endl;
            }
            if (Vsd <= 0)
            {
                std::cerr << "VDs is below 0, erroring, Vds: " << Vsd << std::endl;
            }
            if (lambdap < 0)
            {
                std::cerr << "lambdan is below 0, erroring, lambdan:" << lambdap << std::endl;
            }
            if (Vsg < -Vtp)
            {
                return returnval;
            }
            if (Vsg > -Vtp && Vsd <= VSDsat)
            {
                returnval.state = TransistorPhase::TRIODE;
                returnval.value = Up * Cox * (W / L) * (((Vsg + Vtp) * Vsd) - (Vsd * Vsd) / 2);
                return returnval;
            }
            if (Vsg > -Vtp && Vsd <= VSDsat)
            {
                returnval.state = TransistorPhase::SATURATED;
                returnval.value = ((Up * Cox) / 2) * (W / L) * ((Vsg + Vtp) * (Vsg + Vtp)) * (1 + lambdap * (Vsd - VSDsat));
                return returnval;
            }
            return returnval;
        }
        // Gamma = Body effect
        // Phif = some body effect thing
        // Vb = Voltage of Body
        // Vs = Voltage of supply
        // Vg = Voltage of the turn/off/on thing
        // Vd = Vdd being used
        DigETuple<TransistorPhase> currentShortChannel(ActivationMode mode, double Vg, double Vs, double Vd, double Vb, double gamma, double Phi, double Vt, double Cox, double Un, double W, double L, double Va, double Ec, double Lpn)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            switch (mode)
            {
            case ActivationMode::NMOS:
            {
                double Vsb = Vs - Vb;
                double Vgs = Vg - Vs;
                double Vtn = Vt + (Vsb == 0 ? 0 : gamma * (sqrt(fabs(2 * Phi) + Vsb) - sqrt(fabs(2 * Phi))));
                double Vds = Vd - Vs;
                returnval.SetAppend(currentSCMNMOS(Vgs, Vtn, Cox, Un, W, L, Vds, Va, Ec, Lpn));
            }
            break;
            case ActivationMode::PMOS:
            {
                double Vbs = Vb - Vs;
                double Vsg = Vs - Vg;
                double Vtp = Vt + (Vbs == 0 ? 0 : -gamma * (sqrt(fabs(2 * Phi) + Vbs) - sqrt(fabs(2 * Phi))));
                double Vsd = Vd - Vs;
                returnval.SetAppend(currentSCMPMOS(Vsg, Vtp, Cox, Un, W, L, Vsd, Va, Ec, Lpn));
            }
            break;
            default:
                break;
            }
            return returnval;
        }
        DigETuple<TransistorPhase> currentLongChannel(ActivationMode mode, double Vg, double Vs, double Vd, double Vb, double gamma, double Phi, double Vt, double Cox, double Un, double W, double L, double Va, double Ec, double Lpn)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            switch (mode)
            {
            case ActivationMode::NMOS:
            {
                double Vsb = Vs - Vb;
                double Vgs = Vg - Vs;
                double Vtn = Vt + (Vsb == 0 ? 0 : gamma * (sqrt(fabs(2 * Phi) + Vsb) - sqrt(fabs(2 * Phi))));
                double Vds = Vd - Vs;
                return currentLCMNMOS(Vgs, Vtn, Cox, Un, W, L, Vds, Va);
            }
            break;
            case ActivationMode::PMOS:
            {
                double Vbs = Vb - Vs;
                double Vsg = Vs - Vg;
                double Vtp = Vt + (Vbs == 0 ? 0 : -gamma * (sqrt(fabs(2 * Phi) + Vbs) - sqrt(fabs(2 * Phi))));
                double Vsd = Vd - Vs;
                return currentLCMPMOS(Vsg, Vtp, Cox, Un, W, L, Vsd, Va);
            }
            break;
            default:
                break;
            }
            return returnval;
        }
        DigETuple<TransistorPhase> RTLInverterVihCalc(TransistorCalcModel model, double Vdd, double R, double Kn, double Voul, double ecnln, double Vtn)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            returnval.electricType = ElectricType::VOLTAGE;
            returnval.state = TransistorPhase::DONTCARE;
            // SCM:
            // (Vdd - Voul) / R =
            // (Kn / (1 + (Voul / ecnln))) * ((Vih - Vtn) * Voul - (Voul * Voul) / 2);
            // LCM: Vih = Vtn + sqrt(8 * Vdd / ( 3 * Kn * R)) - (1 / (Kn * R));
            switch (model)
            {
            case TransistorCalcModel::LCM:
            {
                returnval.value = Vtn + sqrt(8 * Vdd / (3 * Kn * R)) - (1 / (Kn * R));
                returnval.string_buffer << "Vih = Vtn + sqrt(8 * Vdd / (3 * Kn * R)) - (1 / (Kn * R)): ";
                returnval.string_buffer << returnval.value << " = " << Vtn << " + "
                                        << "sqrt(8 * " << Vdd << " / (3 * " << Kn << " * " << R << ")) - (1 / (" << Kn << " * " << R << "))" << std::endl;
            }
            case TransistorCalcModel::SCM:
            {
                returnval.value = ((ecnln * Kn * (2 * Vtn + Voul) * Voul) + 2 * (ecnln + Voul) * (Vdd - Voul)) / (2 * ecnln * Kn * Voul * R);
                returnval.string_buffer << "Vih = ((ecnln * Kn * (2 * Vtn + Voul) * Voul) + 2 * (ecnln + Voul) * (Vdd - Voul)) / (2 * ecnln * Kn * Voul * R)" << std::endl;
                returnval.string_buffer << returnval.value << " = "
                                        << "((" << ecnln << " * " << Kn << " * ("
                                        << "2 * " << Vtn << " + " << Voul << ") * " << Voul << ") + 2 * (" << ecnln << " + " << Voul << ") * (" << Vdd << " - " << Voul << ")) / (2 * " << ecnln << " * " << Kn << " * " << Voul << " * " << R << ")" << std::endl;
            }
            }
            return returnval;
        }
        // For this, Vout = Voul
        DigETuple<TransistorPhase> CMOSInverterVihCalc(double Vdd, double Kn, double Kp, double Vin, double Vtn, double Vtp, double Vout)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            returnval.electricType = ElectricType::VOLTAGE;
            returnval.state = TransistorPhase::DONTCARE;
            // Kn = j
            // Kp = k
            // Vdd = d
            // Vin = i
            // Vtn = n
            // Vtp = p
            // Vout = o
            double Kr = Kn / Kp;
            returnval.value = (Vdd + Vtp + Kr * (2 * Vout + Vtn)) / (1 + Kr);
            return returnval;
        }
        // For this Vout = Vouh
        DigETuple<TransistorPhase> CMOSInverterVilCalc(double Vdd, double Kn, double Kp, double Vin, double Vtn, double Vtp, double Vout)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            returnval.electricType = ElectricType::VOLTAGE;
            returnval.state = TransistorPhase::DONTCARE;
            double Kr = Kn / Kp;
            returnval.value = (2 * Vout + Vtp - Vdd + Kr * Vtn) / (1 + Kr);
            return returnval;
        }
        DigETuple<TransistorPhase> CMOSInverterVthCalc(double Vtn, double Kr, double Vdd, double Vtp)
        {
            DigETuple<TransistorPhase> returnval = {TransistorPhase::OFF, 0};
            returnval.electricType = ElectricType::VOLTAGE;
            returnval.state = TransistorPhase::DONTCARE;
            returnval.value = (Vtn + sqrt(1 / Kr) * (Vdd + Vtp)) / (1 + sqrt(1 / Kr));
            return returnval;
        }
        DigETuple<TransistorPhase> CMOSInverterDeltaTDownSat(DigETuple<TransistorPhase> current_input, double V1, double V2, double Cload)
        {
            DigETuple<TransistorPhase> return_val = {TransistorPhase::OFF, 0};
            double Id = current_input.value;
            double Vab = V1 - V2;
            return_val.value = (Cload / Id) * Vab;
            return_val.electricType = ElectricType::TIME;
            return_val.state = TransistorPhase::SATURATED;
            current_input.SetAppend(return_val);
            return current_input;
        }
        // Vtn here is the actual default val
        DigETuple<TransistorPhase> CMOSInverterDeltaTDownTri(double Vss, double Vgs, double Vtn, double Vc, double Vd, double EcnLn, double Kn, double Cload)
        {
            DigETuple<TransistorPhase> return_val = {TransistorPhase::OFF, 0};
            double inverted = 1 / (Vgs - Vtn);
            double ln1Stage1 = (2 * (Vgs - Vtn) - (Vd - (-Vss))) / (2 * (Vgs - Vtn) - (Vc - (-Vss)));
            double ln1Stage2 = (Vc - (-Vss)) / (Vd - (-Vss));
            double ln1 = std::log(ln1Stage1 * ln1Stage2);
            double ln2 = std::log((2 * (Vgs - Vtn) - (Vd - (-Vss))) / (2 * (Vgs - Vtn) - (Vc - (-Vss))));
            double total = inverted * ln1;
            if (!std::isinf(Ecnln))
            {
                total *= (2 / EcnLn) * ln2;
            }
            return_val.value = total * (Cload / Kn);
            return_val.electricType = ElectricType::TIME;
            return_val.state = TransistorPhase::TRIODE;
            return return_val;
        }
    }
}