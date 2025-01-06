v {xschem version=3.4.4 file_version=1.2
}
G {}
K {}
V {}
S {}
E {}
N 220 -50 240 -90 {
lab=vout}
N 220 10 220 60 {
lab=GND}
N 220 -20 260 -20 {
lab=GND}
N 260 -20 260 30 {
lab=GND}
N 220 30 260 30 {
lab=GND}
N 240 -120 310 -120 {
lab=vcc}
N 310 -170 310 -120 {
lab=vcc}
N 180 -20 200 -120 {
lab=vin}
N 230 -70 400 -70 {
lab=vout}
N 240 -220 240 -150 {
lab=vcc}
N 240 -170 310 -170 {
lab=vcc}
N 180 -80 190 -70 {
lab=vin}
C {vsource.sym} -40 -30 0 0 {name=vcc value=1.8v savecurrent=false}
C {vsource.sym} 100 -70 0 0 {name=vcc1 value="pulse(0 1.8 1ns 1ns 1ns 5ns 10ns") savecurrent=false}
C {sky130_fd_pr/nfet_01v8.sym} 200 -20 0 0 {name=M1
W=1
L=0.15
nf=1 
mult=1
ad="'int((nf+1)/2) * W/nf * 0.29'" 
pd="'2*int((nf+1)/2) * (W/nf + 0.29)'"
as="'int((nf+2)/2) * W/nf * 0.29'" 
ps="'2*int((nf+2)/2) * (W/nf + 0.29)'"
nrd="'0.29 / W'" nrs="'0.29 / W'"
sa=0 sb=0 sd=0
model=nfet_01v8
spiceprefix=X
}
C {sky130_fd_pr/pfet_01v8.sym} 220 -120 0 0 {name=M2
W=1
L=0.15
nf=1
mult=1
ad="'int((nf+1)/2) * W/nf * 0.29'" 
pd="'2*int((nf+1)/2) * (W/nf + 0.29)'"
as="'int((nf+2)/2) * W/nf * 0.29'" 
ps="'2*int((nf+2)/2) * (W/nf + 0.29)'"
nrd="'0.29 / W'" nrs="'0.29 / W'"
sa=0 sb=0 sd=0
model=pfet_01v8
spiceprefix=X
}
C {lab_pin.sym} -20 -80 0 0 {name=p2 sig_type=std_logic lab=vcc}
C {lab_pin.sym} 240 -220 0 0 {name=p5 sig_type=std_logic lab=vcc
}
C {lab_pin.sym} 400 -70 0 0 {name=p8 sig_type=std_logic lab=vout
}
C {gnd.sym} -40 0 0 0 {name=l2 lab=GND}
C {gnd.sym} 220 60 0 0 {name=l3 lab=GND}
C {code_shown.sym} 380 -280 0 0 {name=s1 only_toplevel=false value=".lib /home/ankdesh/explore/eda/open_pdks/sky130/sky130A/libs.tech/ngspice/sky130.lib.spice tt 
.tran 0.1n 100n
.save all"}
C {gnd.sym} 100 -40 0 0 {name=l1 lab=GND}
C {lab_pin.sym} 100 -100 0 0 {name=vcc2 sig_type=std_logic lab=vin}
C {lab_pin.sym} 180 -80 0 0 {name=p1 sig_type=std_logic lab=vin}
