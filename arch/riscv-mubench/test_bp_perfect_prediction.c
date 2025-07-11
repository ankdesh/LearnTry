#include <stdio.h>

int main() {
    volatile int i;
    int dummy = 0;
    int num_iter = 10000;
    
    // The branch condition is always true.
    for (i = 0; i < num_iter; i++) {
        // This branch is always taken.
        if (1) {
            dummy++;
        }
    }

    // The branch condition is always false.
    for (i = 0; i < num_iter; i++) {
        // This branch is always not taken.
        if (0) {
            dummy++;
        }
    }

    return 0;
}
