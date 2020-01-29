#ifndef _PUTCHAR_H_
#define _PUTCHAR_H_

void putchar(int ch) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw CPRT_BASE\n"); }

#define getchar #error "no getchar in versat"

#endif /* _PUTCHAR_H_ */
