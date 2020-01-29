#include "printi.h"
int divisors(int n) {
	int i = 2, divs = 0;
	while (i <= n/2) {
		if (n % i == 0) {
			printi(i, 10);
			putchar('\n');
			divs++;
		}
		i++;
	}
	return divs;
}

int main() { return divisors(144); }
