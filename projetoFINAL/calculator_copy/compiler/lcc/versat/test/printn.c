void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int _mod(int a, int b) {
	while (a >= b) a -= b;
	return a;
}
int _div(int a, int b) {
	int x = 0;
	while (a >= b) a -= b, x++;
	return x;
}
void printn(int n, int b) {
	int a;
	if (a = n / b) printn(a, b);
	putchar(n % b + '0');
}
int main() { printn(579, 10); putchar('\n'); return 0; }
/* 13579 => 136015 cycles
 * 3579 => 36754 cycles
 * 579 => 6735 cycles
 */
