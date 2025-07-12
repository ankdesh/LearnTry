
import m5
from m5.objects import *
import argparse # Import the argparse module

# --- 1. Set up argument parser ---
parser = argparse.ArgumentParser(description="Run a RISC-V binary in gem5 with MinorCPU and a branch predictor.")
parser.add_argument("binary", help="Path to the RISC-V binary to execute.")
args = parser.parse_args()

# Create the system
system = System()

# Set up the clock and voltage domains
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

# Set up the memory
system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]

# Create the CPU. We'll use MinorCPU, a simple in-order CPU.
system.cpu = MinorCPU()

# Set the branch predictor for the CPU
#system.cpu.branchPred = LocalBP()
#system.cpu.branchPred.localPredictorSize = 2

system.cpu.branchPred = BiModeBP()

# Create the memory bus
system.membus = SystemXBar()

# Connect the CPU to the memory bus
system.cpu.icache_port = system.membus.cpu_side_ports
system.cpu.dcache_port = system.membus.cpu_side_ports

# Create a memory controller and connect it to the bus
system.cpu.createInterruptController()
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

# --- 2. Use the command-line argument for the workload ---
# Set up the process to run the compiled program
system.workload = SEWorkload.init_compatible(args.binary)
process = Process()
process.cmd = [args.binary] # Use the binary name for the command
system.cpu.workload = process
system.cpu.createThreads()

# Instantiate the system and start the simulation
root = Root(full_system = False, system = system)
m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
