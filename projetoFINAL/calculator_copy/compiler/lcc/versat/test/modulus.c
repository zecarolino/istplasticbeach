int _mul(int a, int b) {
	int mul;
	for (mul = 0; b; b >>= 1, a <<= 1)
		if (b & 1)
			mul += a;
	return mul;
}
int _div(int a, int b) {
	int c = 1, neg = 0, aux;
	if (!a) return 0;
	if (!b) return 2147483647; /* divide by zero */
	if (a < 0) a = -a, neg = 1;
	if (b < 0) b = -b, neg = 1 - neg;
	aux = b;
	if (a && b && b < a) {
		while ((aux << 1) - a < 0)
			aux <<= 1, c <<= 1;
		while (aux + b <= a)
			aux += b, c++;
	}
	if (neg) c = -c;
	return c;
}

int _mod(int a, int b) { return a - (a / b) * b; }
int main() { return 13852 % 1258; } /* expect 14 */
