#include "putchar.h"
#include "alloca.h"

void printhex(int x) {
	int vec[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	if (x) printhex(x >> 4);
	putchar(vec[x & 0xF]);
}


int pos;
void func(int ch) { /* must have a local */
	ch = ' ';
	sp(pos);
	printhex(pos);
	putchar(ch);
	pos = 12;
	alloca(pos);
	printhex(pos);
	putchar(ch);
	sp(pos);
	printhex(pos);
	ch = '\n';
	putchar(ch);
}

int main() { /* main can not take arguments */
	func(0);
	return 0;
}
