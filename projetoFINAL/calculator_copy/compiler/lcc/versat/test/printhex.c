int x = 0xDB97531, vec[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int main() {
	do
		putchar(vec[x & 0xF]);
	while (x >>= 4);
	putchar('\n');
	return 0;
}
