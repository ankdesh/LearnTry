#include <stdio.h>

__attribute__((noinline)) void target_A() { asm volatile("nop"); }
__attribute__((noinline)) void target_B() { asm volatile("nop"); }

const int num_iters = 10000;

int main() {
    volatile int i;
    // A function pointer that will be the source of our indirect branch.
    void (*indirect_call)();

    for (i = 0; i < num_iters; i++) {
        // The target of the call changes on each iteration.
        if (i % 2 == 0) {
            indirect_call = target_A;
        } else {
            indirect_call = target_B;
        }
        // This call is an indirect branch via a register.
        indirect_call();
    }
    return 0;
}
