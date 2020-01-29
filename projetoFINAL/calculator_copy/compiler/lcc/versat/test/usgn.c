#ifdef versat
#define str(s) #s
#define putchar(c) asm("\tldi " str(c) "\n\twrw CPRT_BASE\n")
#else
#include <stdio.h>
#endif
#define zero() putchar(0x30)
#define one() putchar(0x31)
#define nl() putchar(0xA)

void compare(unsigned a, unsigned b) {
	if (a == b) one(); else zero();
	if (a != b) one(); else zero();
	if (a >  b) one(); else zero();
	if (a >= b) one(); else zero();
	if (a <  b) one(); else zero();
	if (a <= b) one(); else zero();
	nl();
}

int main() {
  compare(21U,15U);			/* 011100 */ /* sa=0 sb=0 sc=0 */
  compare(4294967295U,15U);		/* 011100 */ /* sa=1 sb=0 sc=1 E */
  compare(2147483649U,2147483648U);	/* 011100 */ /* sa=1 sb=1 sc=0 */
  compare(2147483648U,2147483647U);	/* 011100 */ /* sa=1 sb=0 sc=0 */
  nl();

  compare(2147483648U,2147483648U);	/* 100101 */ /* sa=1 sb=1 sc=0 */
  compare(21U,21U);			/* 100101 */ /* sa=0 sb=0 sc=0 */
  nl();

  compare(2147483648U,2147483649U);	/* 010011 */ /* sa=1 sb=1 sc=1 */
  compare(10U,21U);			/* 010011 */ /* sa=0 sb=0 sc=1 */
  compare(10U,4294967295U);		/* 010011 */ /* sa=0 sb=1 sc=0 E */
  compare(2147483647U,2147483648U);	/* 010011 */ /* sa=0 sb=1 sc=1 */

  return 0;
}
