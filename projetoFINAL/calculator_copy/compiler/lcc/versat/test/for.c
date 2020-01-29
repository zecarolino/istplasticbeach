void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int main() { int i; for (i = 0; i < 7; i++) putchar('0'+i); putchar('\n'); return 0; }
