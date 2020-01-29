/* ../obj/cpp mem_ends.c | ../obj/rcc -target=versat > mem_ends.va */
#include "ends.h"
#define str(s) #s /* stringify */
#define ALU_CLZ 13 /* program.h */
#define versat(alu,base,offset) asm("\tldi " str(alu) "\n\twrc " str(base) "," str(offset) "\n")
void set(int value, int *addr) { asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n\twrw R1\n\trdw R11\n\taddi 3\n\twrw RB\n\trdwb\n\trdwb\n\twrw RB\n\trdw R1\n\twrwb\n"); }
void setvar(int value, int *addr) { *addr = value; }
int main() {
	int pos = 0x123456, *addr = (int*)pos;
	versat(ALU_CLZ,ALU0_CONFIG_ADDR,ALU_CONF_FNS_OFFSET);
	set(12, (int*)pos);
	setvar(13, (int*)pos);
	*addr++ = 14;
	*addr++ = 15;
	*addr = 16;
	return 1;
}
