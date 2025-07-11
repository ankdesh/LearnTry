## test_bp_perfect_prediction.c
Test Case: The Highly Biased "Always-Taken" Branch
Purpose: To verify the core "increment and saturate" functionality of the counter. This test confirms that after a brief warm-up period, a loop with always taken branch makes the predictor learns a consistently taken branch, transitions to the Strongly Taken state, and remain there. Then the second loop transitions it to strongly not taken and stays there. The predcition accuracy should be near 100% for this test.

#### Gem5 stats output
system.cpu.branchPred.mispredicted_0::NoBranch            0      0.00%      0.00% # Number of committed branches that were mispredicted. (Count)




