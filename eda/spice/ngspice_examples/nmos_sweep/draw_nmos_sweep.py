import matplotlib.pyplot as plt

# --- 1. Data provided by the user ---
raw_data = """
0	1.000000e-01	1.000000e-01	-1.86328e-42	
1	2.000000e-01	2.000000e-01	-1.15881e-53	
2	3.000000e-01	3.000000e-01	1.158814e-53	
3	4.000000e-01	4.000000e-01	1.810909e-64	
4	5.000000e-01	5.000000e-01	-6.03636e-65	
5	6.000000e-01	6.000000e-01	-7.83091e-76	
6	7.000000e-01	7.000000e-01	1.566182e-76	
7	8.000000e-01	8.000000e-01	-1.49388e-86	
8	9.000000e-01	9.000000e-01	2.134115e-87	
9	1.000000e+00	1.000000e+00	4.772070e-97	
10	1.100000e+00	1.100000e+00	-5.30230e-98	
11	1.200000e+00	1.200000e+00	-8.93358e-108	
12	1.300000e+00	1.300000e+00	8.121437e-109	
13	1.400000e+00	1.400000e+00	1.395462e-118	
14	1.500000e+00	1.500000e+00	-1.07343e-119	
15	1.600000e+00	1.600000e+00	-1.98816e-129	
16	1.700000e+00	1.700000e+00	1.325438e-130	
17	1.800000e+00	1.800000e+00	2.681554e-140	
18	1.000000e-01	1.000000e-01	-1.23455e-12	
19	2.000000e-01	2.000000e-01	-1.05262e-11	
20	3.000000e-01	3.000000e-01	-1.38326e-10	
21	4.000000e-01	4.000000e-01	-1.86451e-09	
22	5.000000e-01	5.000000e-01	-2.37542e-08	
23	6.000000e-01	6.000000e-01	-2.53718e-07	
24	7.000000e-01	7.000000e-01	-1.89128e-06	
25	8.000000e-01	8.000000e-01	-8.97538e-06	
26	9.000000e-01	9.000000e-01	-2.70968e-05	
27	1.000000e+00	1.000000e+00	-5.65524e-05	
28	1.100000e+00	1.100000e+00	-9.34701e-05	
29	1.200000e+00	1.200000e+00	-1.34728e-04	
30	1.300000e+00	1.300000e+00	-1.78535e-04	
31	1.400000e+00	1.400000e+00	-2.23807e-04	
32	1.500000e+00	1.500000e+00	-2.69821e-04	
33	1.600000e+00	1.600000e+00	-3.16049e-04	
34	1.700000e+00	1.700000e+00	-3.62081e-04	
35	1.800000e+00	1.800000e+00	-4.07573e-04	
36	1.000000e-01	1.000000e-01	-2.42106e-12	
37	2.000000e-01	2.000000e-01	-1.98798e-11	
38	3.000000e-01	3.000000e-01	-2.52157e-10	
39	4.000000e-01	4.000000e-01	-3.28714e-09	
40	5.000000e-01	5.000000e-01	-4.05489e-08	
41	6.000000e-01	6.000000e-01	-4.19718e-07	
42	7.000000e-01	7.000000e-01	-2.98102e-06	
43	8.000000e-01	8.000000e-01	-1.28976e-05	
44	9.000000e-01	9.000000e-01	-3.54059e-05	
45	1.000000e+00	1.000000e+00	-6.94215e-05	
46	1.100000e+00	1.100000e+00	-1.10572e-04	
47	1.200000e+00	1.200000e+00	-1.55822e-04	
48	1.300000e+00	1.300000e+00	-2.03552e-04	
49	1.400000e+00	1.400000e+00	-2.52833e-04	
50	1.500000e+00	1.500000e+00	-3.03061e-04	
51	1.600000e+00	1.600000e+00	-3.53817e-04	
52	1.700000e+00	1.700000e+00	-4.04806e-04	
53	1.800000e+00	1.800000e+00	-4.55810e-04	
54	1.000000e-01	1.000000e-01	-3.83513e-12	
55	2.000000e-01	2.000000e-01	-3.16131e-11	
56	3.000000e-01	3.000000e-01	-3.89389e-10	
57	4.000000e-01	4.000000e-01	-4.91543e-09	
58	5.000000e-01	5.000000e-01	-5.87725e-08	
59	6.000000e-01	6.000000e-01	-5.91685e-07	
60	7.000000e-01	7.000000e-01	-4.08032e-06	
61	8.000000e-01	8.000000e-01	-1.67989e-05	
62	9.000000e-01	9.000000e-01	-4.35030e-05	
63	1.000000e+00	1.000000e+00	-8.15634e-05	
64	1.100000e+00	1.100000e+00	-1.26052e-04	
65	1.200000e+00	1.200000e+00	-1.74028e-04	
66	1.300000e+00	1.300000e+00	-2.24062e-04	
67	1.400000e+00	1.400000e+00	-2.75368e-04	
68	1.500000e+00	1.500000e+00	-3.27439e-04	
69	1.600000e+00	1.600000e+00	-3.79924e-04	
70	1.700000e+00	1.700000e+00	-4.32570e-04	
71	1.800000e+00	1.800000e+00	-4.85196e-04	
72	1.000000e-01	1.000000e-01	-5.53167e-12	
73	2.000000e-01	2.000000e-01	-4.61874e-11	
74	3.000000e-01	3.000000e-01	-5.53523e-10	
75	4.000000e-01	4.000000e-01	-6.77232e-09	
76	5.000000e-01	5.000000e-01	-7.85539e-08	
77	6.000000e-01	6.000000e-01	-7.70374e-07	
78	7.000000e-01	7.000000e-01	-5.19479e-06	
79	8.000000e-01	8.000000e-01	-2.07246e-05	
80	9.000000e-01	9.000000e-01	-5.16096e-05	
81	1.000000e+00	1.000000e+00	-9.36205e-05	
82	1.100000e+00	1.100000e+00	-1.41258e-04	
83	1.200000e+00	1.200000e+00	-1.91690e-04	
84	1.300000e+00	1.300000e+00	-2.43695e-04	
85	1.400000e+00	1.400000e+00	-2.96641e-04	
86	1.500000e+00	1.500000e+00	-3.50126e-04	
87	1.600000e+00	1.600000e+00	-4.03867e-04	
88	1.700000e+00	1.700000e+00	-4.57657e-04	
89	1.800000e+00	1.800000e+00	-5.11346e-04	
90	1.000000e-01	1.000000e-01	-7.59739e-12	
91	2.000000e-01	2.000000e-01	-6.43923e-11	
92	3.000000e-01	3.000000e-01	-7.51584e-10	
93	4.000000e-01	4.000000e-01	-8.91976e-09	
94	5.000000e-01	5.000000e-01	-1.00445e-07	
95	6.000000e-01	6.000000e-01	-9.60480e-07	
96	7.000000e-01	7.000000e-01	-6.35422e-06	
97	8.000000e-01	8.000000e-01	-2.47912e-05	
98	9.000000e-01	9.000000e-01	-6.00161e-05	
99	1.000000e+00	1.000000e+00	-1.06124e-04	
100	1.100000e+00	1.100000e+00	-1.57003e-04	
101	1.200000e+00	1.200000e+00	-2.09934e-04	
102	1.300000e+00	1.300000e+00	-2.63911e-04	
103	1.400000e+00	1.400000e+00	-3.18466e-04	
104	1.500000e+00	1.500000e+00	-3.73306e-04	
105	1.600000e+00	1.600000e+00	-4.28216e-04	
106	1.700000e+00	1.700000e+00	-4.83039e-04	
107	1.800000e+00	1.800000e+00	-5.37655e-04
"""

# --- 2. Parsing the Data ---
vin_all = []
idd_all = []

# Process line by line
for line in raw_data.strip().split('\n'):
    # Split by whitespace and remove empty strings
    parts = line.split()
    
    # Ensure the line has enough data points (index, v-sweep, vin, iddd)
    if len(parts) >= 4:
        try:
            # Column index 2 is v(in), index 3 is i(vdd)
            v_val = float(parts[2])
            i_val = float(parts[3])
            vin_all.append(v_val)
            idd_all.append(i_val)
        except ValueError:
            # Could not convert to float (e.g., header lines if included)
            continue

# --- 3. Separating Data into Curves ---
# The data contains multiple sweeps. We detect a new sweep when 
# the voltage goes back down (e.g., from 1.8V back to 0.1V).
curves = []
current_vin_curve = []
current_idd_curve = []

for i in range(len(vin_all)):
    val_v = vin_all[i]
    val_i = idd_all[i]
    
    # If current_vin_curve has data AND the new voltage is lower than 
    # the last one added, it means a new sweep has started.
    if len(current_vin_curve) > 0 and val_v < current_vin_curve[-1]:
        # Save the completed curve
        curves.append((current_vin_curve, current_idd_curve))
        # Start fresh lists for the new curve
        current_vin_curve = []
        current_idd_curve = []
        
    current_vin_curve.append(val_v)
    current_idd_curve.append(val_i)

# Add the very last curve processed after the loop finishes
if current_vin_curve:
    curves.append((current_vin_curve, current_idd_curve))


# --- 4. Plotting ---
fig, ax = plt.subplots(figsize=(10, 6))

# Iterate through the separated curves and plot them
for i, (vin_data, idd_data) in enumerate(curves):
    # Determine label based on data content
    # The first dataset (index 0) has incredibly small numbers (e-42 to e-140), 
    # likely simulation noise/leakage. We label it differently.
    if i == 0:
         label = "Leakage/Noise Floor (Sweep 1)"
    else:
         label = f"Sweep {i+1}"
         
    ax.plot(vin_data, idd_data, marker='.', linestyle='-', label=label)

# Chart formatting
ax.set_title('Vin vs Idd Characteristics')
ax.set_xlabel('Vin (V)')
ax.set_ylabel('Idd (A)')
ax.grid(True, which='both', linestyle='--', linewidth=0.5)
ax.legend()

# Optional: Use a log scale for Y-axis if you want to see the turn-on behavior better
# ax.set_yscale('log') 

plt.tight_layout()
plt.show()