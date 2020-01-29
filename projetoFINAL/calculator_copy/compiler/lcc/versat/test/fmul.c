int _mul(int a, int b) {
	int mul;
	for (mul = 0; b; b >>= 1, a <<= 1)
		if (b & 1)
			mul += a;
	return mul;
}
int x = 4;
int main() { return x * 3; }
/*
#include <stdio.h>
int main(int argc, char *argv[]) {
	if (argc < 3) return 1;
	printf("%d\n", _mul(atoi(argv[1]), atoi(argv[2])));
	return 0;
}
*/
