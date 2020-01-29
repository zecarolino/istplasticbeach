#ifndef _UDIV_H_
#define _UDIV_H_

unsigned _udiv(unsigned a, unsigned b) {
	unsigned c = 1, aux;
	if (!a) return 0;
	if (!b) return 2147483647; /* divide by zero */
	aux = b;
	if (b < a) {
		while ((aux << 1) - a < 0)
			aux <<= 1, c <<= 1;
		while (aux + b <= a)
			aux += b, c++;
	} else c = 0;
	return c;
}

#endif /* _UDIV_H_ */
