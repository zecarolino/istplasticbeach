#ifndef _PUTS_H_
#define _PUTS_H_

#include "putchar.h"

int puts(char *s) {
	while (*s) putchar(*s++);
	return 0;
}

#endif /* _PUTS_H_ */
