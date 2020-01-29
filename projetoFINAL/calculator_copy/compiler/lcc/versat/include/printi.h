#ifndef _PRINTI_H_
#define _PRINTI_H_

#include "mod.h"
#include "div.h"
#include "putchar.h"

void printi(int n, int b) {
	int a, c;
	if (a = n / b) printi(a, b);
	c = n % b;
	if (c <= 9) putchar(c + '0');
	else putchar(c + 'A' -10);
}

#endif /* _PRINTI_H_ */
