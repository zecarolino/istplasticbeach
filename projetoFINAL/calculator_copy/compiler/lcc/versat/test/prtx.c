int x, vec[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
void printx(int val) {
	if (val > 0) printx(val >> 4);
	x = vec[val & 0xF];
	asm("\tldi x\n\taddi MEM_BASE\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n");
}

int main() {
	printx(0x2468A);
	return 0;
}
