void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int vec[] = { 9, 7, 5, 3, 1, 0 };
int main() {
	int i;
	for (i = 0; vec[i]; i++)
		putchar(vec[i] + '0');
	putchar('\n');
	return 0;
}
