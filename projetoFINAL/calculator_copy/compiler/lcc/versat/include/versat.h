#ifndef _VERSAT_H_
#define _VERSAT_H_

#include "ends.h"

#ifndef str
#define str(s) #s /* stringify */
#endif

#define versatSet(val,base,offset) asm("\tldi " str(base) "\n\taddi " str(offset) "\n\twrw RB\n\tldi " str(val) "\n\twrwb\n")

#define versatClear() asm("\tldi 0\n\twrw " str(VERSAT_CLEAR) "\n")
#define versatConfig(n) asm("\tldi " str(n) "\n\twrw " str(CONF_MEM_BASE) "\n")
#define versatMemory(mem, iter, per, duty, sela, start, shift, incr, delay, rvrs) \
	asm("\tldi " str(mem) "\n\twrw RB\n\tldi " str(iter) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(per) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(duty) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(sela) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(selb) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(start) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(shft) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(incr) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(delay) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(rvrs) "\n\twrwb\n")
#define versatALU(alu, sela, selb, fns) \
	asm("\tldi " str(alu) "\n\twrw RB\n\tldi " str(sela) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(selb) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(fns) "\n\twrwb\n")
#define versatMult(mult, sela, selb, lonhi, div2) \
	asm("\tldi " str(mult) "\n\twrw RB\n\tldi " str(sela) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(selb) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(lonhi) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(div2) "\n\twrwb\n")
#define versatBS(sela, selb, lna, lnr) \
	asm("\tldi " str(VERSAT_BS0) "\n\twrw RB\n\tldi " str(sela) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(selb) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(lna) "\n\twrwb\n" \
		"\trdw RB\n\taddi 1\n\twrw RB\tldi " str(lnr) "\n\twrwb\n")
#define versatRun(low,high) \
	asm("\tldi " str(low) "\n\tldih " str(high) \
		"\n\twrw ENG_CTRL_REG\n\tldi " str(low) \
		"\n\tldih " str(high) "\n\twrw ENG_CTRL_REG\n")
#define versatWait(val,label) \
	asm( str(label) "\tldi " str(val) "\n\tand ENG_STATUS_REG\n"\
		"\taddi -" str(val) "\n\tbneqi " str(label) "\n\tnop\n")

#define VERSAT_CLEAR	5119
#define VERSAT_MEM0A	5120
#define VERSAT_MEM0B	5129
#define VERSAT_MEM1A	5138
#define VERSAT_MEM1B	5147
#define VERSAT_MEM2A	5156
#define VERSAT_MEM2B	5165
#define VERSAT_MEM3A	5174
#define VERSAT_MEM3B	5183
#define VERSAT_ALU0	5192
#define VERSAT_ALU1	5195
#define VERSAT_ALU_LITE0	5198
#define VERSAT_ALU_LITE1	5201
#define VERSAT_ALU_LITE2	5204
#define VERSAT_ALU_LITE3	5207
#define VERSAT_MULT0	5210
#define VERSAT_MULT1	5214
#define VERSAT_MULT2	5218
#define VERSAT_MULT3	5222
#define VERSAT_BS0	5226
#define VERSAT_FU	6176	/* N_W=5 */

typedef struct versatFU {
	struct mem { int iter, per, duty, sela, start, shift, incr, delay, rvrs; }
		mem0A, mem0B, mem1A, mem1B, mem2A, mem2B, mem3A, mem3B; 
	struct alu { int sela, selb, fns; }
		alu0, alu1, alulite0, alulite1, alulite2, alulite3;
	struct mult { int sela, selb, lonhi, div2; }
		mult0, mult1, mult2, mult3; 
	struct bs { int sela, selb, lna, lnr; } bs;
} Versat;

typedef struct versatDE {
	int mem0A, mem0B, mem1A, mem1B, mem2A, mem2B, mem3A, mem3B;
	int alu0, alu1, alulite0, alulite1, alulite2, alulite3;
	int mult0, mult1, mult2, mult3, bs0; 
} VersatDE;

#endif /* _VERSAT_H_ */
