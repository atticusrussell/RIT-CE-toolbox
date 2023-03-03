void thingFunc()
{
    std::complex<double> Ia = std::complex(29.9577, 4.0621);
    std::complex<double> Ib = std::complex(14.8942, 10.1551);
    std::complex<double> Ic = std::complex(7.0409, -3.9267);
    std::complex<double> V1 = 4.0 * Ib + 240.0 - 10.0 * Ia;
    std::cout << polar_form(240.0 * std::conj(Ia));
    // If it's parallel: do the parallel current formula to find the current on the path for the transfer function

    // Nth degree poles get power to Nth degree
    // Zeros make the slope go up
    // Poles make the slope go down
    // Zero = +20DB per DEC
    // Pole = -20DB per DEC
    // Point it changes: It's (S + position) -> (S/position + 1)
    // (Zeros / Poles) * K

    // Poles at origin = -90 for Phase across whole
    // Zeros at origins = 90 for Phase across whole
    // Zeros are +90 CHANGES
    // Poles are -90 CHANGES
    // FOR PHASES, ALL CHANGES APPLY 1 DECADE BEFORE OR ONE DECADE AFTER THE POINT OF INTEREST, e.g. if they happen at
    // 10, it starts at 1, and ends at 100
    // It goes in its own couse until something else happensa
    // Ns change Nx as fast (Doubles change 2x as fast)

    // HOW TO DEAL WITH PARALLEL, PERFORM THE RIGHT SIDE ALONE FROM THE LEFT SIDE
    // THEN CALCULATE THE PARALLEL RESISTANCE
    // AFTER THAT WE CAN DETERMINE THE CURRENT THROUGH IT WITH EASE BY VOLTAGE /
    // RESISTANCE THROUGH LOOP
}