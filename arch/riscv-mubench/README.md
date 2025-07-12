# Execution instructions

### Compile all .c files
./build-all.sh

### Run on simple RISCV CPU
gem5.opt --debug-flags=Branch simple_gem5_riscv_cpu.py test_bp_perfect_prediction.out

------------
# Test Description

## test_bp_perfect_prediction.c
*Test Case:* The Highly Biased "Always-Taken" and "Always-Not-Taken" Branches leading to ~100% correct prediction

*Purpose:* To verify the core "increment and saturate" functionality of the counter. This test confirms that after a brief warm-up period, a loop with always taken branch makes the predictor learns a consistently taken branch, transitions to the Strongly Taken state, and remain there. Then the second loop transitions it to strongly not taken and stays there. The predcition accuracy should be near 100% for this test.


## test_bp_alternate.c
*Expected Observation:* After an initial warm-up, the predictor state will become trapped, oscillating between Weakly Not-Taken (1) and Weakly Taken (2). It will mispredict every single branch for the entire duration of the test, resulting in a near 100% misprediction rate and demonstrating a sustained worst-case scenario. (This depends on assumption that it starts from a weekly-taken state. In case not, it should lead to 50% accuracy.

## test_bp_miss_pred_in_strong_taken.c
*Expected Observation:* After warming up to the Strongly Taken state, the predictor will settle into a stable rhythm. In each repetition of the 4-element sub-pattern (T, T, T, N), it will correctly predict the three 'Taken' outcomes and mispredict the single 'Not-Taken' outcome. This yields a steady-state accuracy of 75%,

## test_bp_state_swing.c
*Purpose:* To verify the predictor's ability to transition through its entire state range, from Strongly Not-Taken (SNT) to Strongly Taken (ST) and back down, exercising all state transition paths.

## test_btb_capacity_miss.c
*Expected Observation:* After filling up the BTB, it should start eviting the enrties from BTB, which will lead to lots of (almost all for func pointers) BTB misses.

## test_btb_force_misspredict.c
*Expected Observation:* Changes target of call everytime leading to misprediction of target everytime (assuming single entry for each target).




