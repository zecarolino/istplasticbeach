#ifndef _UMUL_H_
#define _UMUL_H_
unsigned _umul(unsigned a, unsigned b) {
	unsigned c = 0;
	while (a) {
		if (a & 1) c += b;
		a >>= 1;
		b <<= 1;
	}
	return c;
}
#endif /* _UMUL_H_ */
