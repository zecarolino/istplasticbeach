void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int main() {
	char *s = "hello world!\n";
	while (*s) putchar(*s++);
	return 0;
}
