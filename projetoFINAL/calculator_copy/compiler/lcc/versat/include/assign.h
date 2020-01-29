#ifndef _ASSIGN_H_
#define _ASSIGN_H_

void assign(int value, int *addr) {
	asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw R1\n");
	asm("\trdw R11\n\taddi 3\n\twrw RB\n\trdwb\n\trdwb\n\twrw RB\n");
	asm("\trdw R1\n\twrwb\n");
}

#endif /* _ASSIGN_H_ */
