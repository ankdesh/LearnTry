# CMOS Inverter VTC Simulation

This project simulates the Voltage Transfer Characteristic (VTC) of a CMOS inverter using `ngspice`. It compares the VTC for different W/L ratios of the PMOS and NMOS transistors.

## Device Schematic

The following image shows the device setup being simulated:

![Device Schematic](device.png)

## Files

- **`vtc_inverter_equal_w_l.spice`**: SPICE netlist for an inverter with equal W/L ratios for PMOS and NMOS.
- **`vtc_inverter_different_w_l.spice`**: SPICE netlist for an inverter with different W/L ratios (PMOS W is larger to compensate for lower mobility).
- **`tsmc_025um_model.mod`**: TSMC 0.25um CMOS model parameters.
- **`run_and_plot_all.py`**: Python script to automate running the simulations and plotting the results.

## Usage

To run the simulations and generate the combined VTC plot, use the following command:

```bash
python3 run_and_plot_all.py -i vtc_inverter_different_w_l.spice vtc_inverter_equal_w_l.spice -o combined_vtc_plot.png
```

This command will:
1. Run `ngspice` for each input SPICE file.
2. Parse the output data.
3. Generate a combined plot named `combined_vtc_plot.png`.

## Requirements

- `ngspice` must be installed and in your PATH.
- Python 3 with `matplotlib` installed.
