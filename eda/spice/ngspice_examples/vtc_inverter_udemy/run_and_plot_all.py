import os
import subprocess
import matplotlib.pyplot as plt
import argparse

# --- Configuration ---
# Defaults
default_output_plot_file = "combined_vtc_plot.png"

# Python executable to use (if needed for specific environment, though this script runs in it)
# We assume ngspice is in the path.

# --- Function to parse ngspice output ---
def parse_ngspice_output(filename):
    """
    Parses an ngspice output file (raw print output) and extracts v(in) and v(out).
    Assumes the format: Index v-sweep v(in) v(out)
    Returns: (vin_list, vout_list)
    """
    vin = []
    vout = []
    
    if not os.path.exists(filename):
        print(f"Warning: Output file {filename} not found.")
        return vin, vout

    with open(filename, 'r') as f:
        lines = f.readlines()
        start_parsing = False
        for line in lines:
            # Look for the header line to start parsing
            if line.strip().startswith('Index'):
                start_parsing = True
                continue
            
            # Stop if we hit the end footer
            if line.strip().startswith('ngspice'):
                break
                
            if not start_parsing:
                continue
                
            # Skip separator lines
            if line.strip().startswith('---'):
                continue
                
            parts = line.split()
            # We expect at least 4 columns: Index, v-sweep, v(in), v(out)
            if len(parts) >= 4:
                try:
                    # Extract last two columns
                    # v(in) is at index 2, v(out) is at index 3 (0-indexed)
                    v_in_val = float(parts[-2])
                    v_out_val = float(parts[-1])
                    vin.append(v_in_val)
                    vout.append(v_out_val)
                except ValueError:
                    continue
    return vin, vout

# --- Main Execution ---
def main():
    parser = argparse.ArgumentParser(description="Run ngspice simulations and plot VTCs.")
    parser.add_argument('-i', '--input', nargs='+', required=True, help="List of input SPICE files")
    parser.add_argument('-o', '--output', default=default_output_plot_file, help="Output plot filename")
    
    args = parser.parse_args()
    
    plt.figure(figsize=(10, 6))
    
    for spice_file in args.input:
        if not os.path.exists(spice_file):
            print(f"Error: SPICE file {spice_file} does not exist. Skipping.")
            continue
            
        base_name = os.path.splitext(spice_file)[0]
        output_file = f"{base_name}_output.txt"
        
        print(f"Running simulation for {spice_file}...")
        
        # Run ngspice in batch mode
        # Command: ngspice -b <spice_file> -o <output_file>
        cmd = ["ngspice", "-b", spice_file, "-o", output_file]
        
        try:
            subprocess.run(cmd, check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error running ngspice for {spice_file}: {e}")
            # Even if it fails with exit code 1 (common with some models), 
            # we check if output was generated.
        
        print(f"Parsing output from {output_file}...")
        vin, vout = parse_ngspice_output(output_file)
        
        if vin and vout:
            plt.plot(vin, vout, linewidth=2, label=base_name)
        else:
            print(f"Warning: No valid data found for {spice_file}")

    # --- Plotting Details ---
    plt.xlabel('Input Voltage (Vin) [V]')
    plt.ylabel('Output Voltage (Vout) [V]')
    plt.title('Combined Inverter VTC')
    plt.grid(True, which='both', linestyle='--', alpha=0.7)
    plt.legend()
    plt.tight_layout()

    plt.savefig(args.output)
    print(f"Combined plot successfully saved to {args.output}")

if __name__ == "__main__":
    main()
