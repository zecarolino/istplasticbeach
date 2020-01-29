#ifndef _MUL_H_
#define _MUL_H_
int _mul(int a, int b) {
	int c = 0;
	if (a < 0) b = -b, a = -a;
	while (a) {
		if (a & 1) c += b;
		a >>= 1;
		b <<= 1;
	}
	return c;
}
#endif /* _MUL_H_ */
