# Top Matter
import numpy as np
import matplotlib.pyplot as plt
import sys

#import PySpice
# import PySpice.Logging.Logging as Logging
from PySpice.Spice.Netlist import Circuit
from PySpice.Unit import u_V, u_kOhm

# logger = Logging.setup_logging() # This can be removed


circuit = Circuit('Voltage Divider')

circuit.V('input', 'in_cir', circuit.gnd, 10@u_V)
circuit.R(1, 'in_cir', 'out', 9@u_kOhm)  # @u_kΩ is a unit of kOhms
circuit.R(2, 'out', circuit.gnd, 1@u_kOhm)

print("------Circuit----------")
print(circuit)
print("------------------------")

simulator = circuit.simulator(simulator='ngspice-subprocess', temperature=25, nominal_temperature=25, compatibility="ps")
#simulator.options(ngbehavior='ps') # Set PSpice compatibility mode

print("------Simulator----------")
print(simulator)
print("------------------------")

analysis = simulator.operating_point()


print("------Analysis----------")
print(analysis)
print("------------------------")
