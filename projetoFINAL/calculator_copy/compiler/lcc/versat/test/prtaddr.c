void putchar(int ch) {
	asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n");
}
void printx(int val) {
	if (val > 0) printx(val >> 4);
	putchar((val & 0xF)+0x30);
}

int var;
int main() {
	printx((int)&var);
	return 0;
}
