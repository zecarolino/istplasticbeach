int main() {
	asm("\tldi 0x36\n\twrw CPRT_BASE\n");
	asm("\tldi 0xa\n\twrw CPRT_BASE\n");
	return 1;
}
