void set(int value, int *addr) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw R1\n\trdw R11\n\taddi 3\n\twrw RB\n\trdwb\n\trdwb\n\twrw RB\n\trdw R1\n\twrwb\n"); }
int var;
int main() { set(14, &var); return var; }
