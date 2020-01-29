#include "printi.h"

int bubble(int list[], int n) {
	int c, d, t, swap, cnt = 0;

	for (c = 0; c < n - 1; c++) {
		for (swap = 0, d = n - 1; d > c; d--)
			if (list[d - 1] > list[d]) {	/* Swapping */
				swap++;
				t = list[d];
				list[d] = list[d - 1];
				list[d - 1] = t;
			}
		if (!swap)
			break;
		cnt++;
	}
	return cnt;
}

int v[] = { 7, 4, 9, 6, 2, 1, 3, 5, 8, 0 };

int main() {
	int i, size = sizeof(v) / sizeof(v[0]), cnt = bubble(v, size);
	for (i = 0; i < size; i++) {
		putchar(v[i] + '0');
		putchar(' ');
	}
	printi(cnt, 10);
	putchar('\n');
	return 0;
}
