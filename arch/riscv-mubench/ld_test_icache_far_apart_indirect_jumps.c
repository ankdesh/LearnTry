void __attribute__((section(".jump_A"))) jump_target_A() { /* Do nothing */ }
void __attribute__((section(".jump_B"))) jump_target_B() { /* Do nothing */ }
void __attribute__((section(".jump_C"))) jump_target_C() { /* Do nothing */ }
// Jump table (array of function pointers).
void (*jump_table[])() = { jump_target_A, jump_target_B, jump_target_C };

void main() {
    int path[] = {0, 2, 0, 1, 2, 2, 0, 1, 0, 2, 1, 1};
    int path_len = sizeof(path) / sizeof(path[0]);
    for (int i = 0; i < path_len; ++i) {
        jump_table[path[i]]();
    }
}
