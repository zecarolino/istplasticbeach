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

int main() { return 13579 / 2456; } /* expect 5 */

/*
#include <stdio.h>
int main(int argc, char *argv[]) { printf("%d\n", _div(atoi(argv[1]), atoi(argv[2]))); return 0; }
*/
