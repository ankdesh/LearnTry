# Inverter VTC Variation Study

This project investigates the effect of varying the PMOS and NMOS transistor widths on the Voltage Transfer Characteristic (VTC) of a CMOS inverter.

## Files

- **`inverter_variation.cir`**: The main SPICE netlist. It contains a `.control` block that performs a loop, varying the widths of the NMOS and PMOS transistors in opposite directions while maintaining a constant total width pitch.
- **`tsmc_025um_model.mod`**: The TSMC 0.25um CMOS model parameters used for the simulation.

## Simulation Details

The simulation performs a DC sweep of the input voltage (`Vin`) from 0V to 2.5V.
It iterates 5 times, modifying the `W` (width) parameter of the transistors:
- **NMOS Width**: Starts at 0.375u and increases.
- **PMOS Width**: Starts at 1.875u and decreases.

## How to Run

1. Open a terminal and navigate to this directory:
   ```bash
   cd /home/ankdesh/explore/LearnTry/eda/spice/ngspice_examples/vtc_inverter_variation_study
   ```

2. Start `ngspice` in interactive mode:
   ```bash
   ngspice
   ```

3. Source the circuit file to run the simulation and generate the plot:
   ```ngspice
   source inverter_variation.cir
   ```

## Output

The simulation will generate a plot window showing 5 VTC curves (`dc1.out` to `dc5.out`) corresponding to the different width ratios, demonstrating how the switching threshold shifts.
