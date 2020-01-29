void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int x = 3, y = 3, z = 3;
int main() {
	if (x < 0) return 0;
	if (y < 0) return 0;
	if (z < 0) return 0;
	if (x + y <= z) {
		putchar('0');
		putchar('\n');
		return 1;
	}
	if (y + z <= x) {
		putchar('0');
		putchar('\n');
		return 1;
	}
	if (z + x <= y) {
		putchar('0');
		putchar('\n');
		return 1;
	}
	if (x == y) {
		if (y == z) putchar('3');
		else putchar('2');
		putchar('\n');
		return 1;
	}
	if (z == y) {
		putchar('2');
		putchar('\n');
		return 1;
	}
	if (z == x) {
		putchar('2');
		putchar('\n');
		return 1;
	}
	putchar('1');
	putchar('\n');
	return 1;
}
