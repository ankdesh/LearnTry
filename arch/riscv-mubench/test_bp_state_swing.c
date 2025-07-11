#include <stdio.h>

// Pattern: T, T, T, N, N, N
// This pattern drives the state from SNT up to ST, then back down to SNT.
const int pattern[] = {1, 1, 1, 0, 0, 0};
const int pattern_len = sizeof(pattern) / sizeof(pattern[0]);
const int num_iter = 1000; // Repeat the pattern 10 times

int main() {
    volatile int i;
    int dummy = 0;

    for (i = 0; i < pattern_len * num_iter; i++) {
        if (pattern[i % pattern_len]) {
            dummy++;
        }
    }
    printf("Dummy value: %d\n", dummy);
    return 0;
}

