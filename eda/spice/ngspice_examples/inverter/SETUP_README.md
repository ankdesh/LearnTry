# Sky130 PDK Setup and Simulation Walkthrough

I have successfully set up the Sky130 PDK using `volare` and ran a sample inverter simulation with `ngspice`.

## Setup Details
- **Volare Installation**: Installed in `~/virtualenvs/open_pdks`.
- **PDK Version**: `0fe599b2afb6708d281543108caf8310912f54af` (Sky130A).
- **PDK Location**: `~/.volare/volare/sky130/versions/...`

## Simulation Files
- **[inverter.spice](inverter.spice)**: A simple inverter circuit using Sky130 models.

## How to Run
To run the simulation again:

```bash
ngspice -b inverter.spice
```

## Results
The simulation ran successfully, producing transient analysis data.
Output excerpt:
```
Circuit: * sky130 inverter simulation
Doing analysis at TEMP = 27.000000 and TNOM = 27.000000
...
No. of Data Rows : 4032
```
To view the waveform, you can run `ngspice inverter.spice` (interactive mode) and use `plot in out`.
