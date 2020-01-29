int x;
int main() {
	x = 0x38;
	asm("\tldi x\n\taddi MEM_BASE\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n");
	asm("\tldi 0xa\n\twrw CPRT_BASE\n");
	return 0;
}
