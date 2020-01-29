void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }
int _mul(int a, int b) {
	int c = 0;
	while (a) {
		if (a & 1) c += b;
		a >>= 1;
		b <<= 1;
	}
	return c;
}
int _div(int a, int b) {
	int c = 1, neg = 0, aux;
	if (!a) return 0;
	if (!b) return 2147483647; /* divide by zero */
	if (a < 0) a = -a, neg = 1;
	if (b < 0) b = -b, neg = 1 - neg;
	aux = b;
	if (b < a) {
		while ((aux << 1) - a < 0)
			aux <<= 1, c <<= 1;
		while (aux + b <= a)
			aux += b, c++;
	} else c = 0;
	if (neg) c = -c;
	return c;
}
int _mod(int a, int b) { return a - (a / b) * b; }

void printi(int n, int b) {
	int a;
	if (a = n / b) printi(a, b);
	putchar(n % b + '0');
}
int main() { printi(13579, 10); putchar('\n'); return 0; }
/* 13579 => 33756 cycles (4x times faster than basic _mod _div */
