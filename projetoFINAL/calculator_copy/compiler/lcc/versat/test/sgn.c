#define one() asm("\tldi 0x31\n\twrw CPRT_BASE\n")
#define zero() asm("\tldi 0x30\n\twrw CPRT_BASE\n")
#define nl() asm("\tldi 0xA\n\twrw CPRT_BASE\n")

void compare(int a, int b) {
	if (a == b) one(); else zero();
	if (a != b) one(); else zero();
	if (a <  b) one(); else zero();
	if (a <= b) one(); else zero();
	if (a >  b) one(); else zero();
	if (a >= b) one(); else zero();
	nl();
}

int main() {
	compare(-12,0);		/* 011100 */
	compare(10,15);		/* 011100 */
	compare(15,10);		/* 010011 */
	compare(10,10);		/* 100101 */
	compare(-10,15);	/* 011100 */
	compare(10,-15);	/* 010011 */

	compare(2147483647,15);
	compare(10,2147483647);

	return 0;
}
