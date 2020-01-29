/* versat.md by gcrs IST,2019 */
#define ACC 0
#include "c.h"
#define NODEPTR_TYPE Node
#define OP_LABEL(p) ((p)->op)
#define LEFT_CHILD(p) ((p)->kids[0])
#define RIGHT_CHILD(p) ((p)->kids[1])
#define STATE_LABEL(p) ((p)->x.state)
static void address(Symbol, Symbol, long);
static void blkfetch(int, int, int, int);
static void blkloop(int, int, int, int, int, int[]);
static void blkstore(int, int, int, int);
static void defaddress(Symbol);
static void defconst(int, int, Value);
static void defstring(int, char *);
static void defsymbol(Symbol);
static void doarg(Node);
static void emit2(Node);
static void export(Symbol);
static void clobber(Node);
static void function(Symbol, Symbol [], Symbol [], int);
static void global(Symbol);
static void import(Symbol);
static void local(Symbol);
static void progbeg(int, char **);
static void progend(void);
static void segment(int);
static void space(int);
static void target(Node);
extern int ckstack(Node, int);
static Symbol intregw, intreg[32]; /* must be 32! */
static int cseg;
static char *invalid[] = { "and", "bneq", "IMM_W", "rdwb", "ldi",
"DELAY_SLOTS", "MEM_BASE", "beqi", "R14", "R15", "xor", "sub", "R10",
"R11", "wrw", "add", "RB", "ldih", "PROG_ADDR_W", "addi", "R4", "R5",
"R6", "R7", "R0", "R1", "R2", "R3", "RC", "R8", "REGF_BASE", "R9",
"CPRT_BASE", "DATA_W", "R12", "OPCODESZ", "R13", "rdw", "beq", "ADDR_W",
"PROG_ROM_ADDR_W", "PROG_ROM", "PROG_RAM", "shft", "wrwb", "INSTR_W",
"PROG_RAM_ADDR_W", "bneqi", "REGF_ADDR_W", "nop", "wrc", 0 };
static int blkregs[] = { ACC+1, ACC+2 };
/*
generated at Tue Dec 10 13:46:27 2019
by $Id$
*/
static void _kids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
static void _label(NODEPTR_TYPE);
static int _rule(void*, int);

#define _stmt_NT 1
#define _reg_NT 2
#define _con_NT 3
#define _fpN_NT 4
#define _addrg_NT 5
#define _con5_NT 6
#define _reg5_NT 7
#define _con1_NT 8
#define _addr_NT 9
#define _addrj_NT 10

static char *_ntname[] = {
	0,
	"stmt",
	"reg",
	"con",
	"fpN",
	"addrg",
	"con5",
	"reg5",
	"con1",
	"addr",
	"addrj",
	0
};

struct _state {
	short cost[11];
	struct {
		unsigned int _stmt:6;
		unsigned int _reg:7;
		unsigned int _con:2;
		unsigned int _fpN:2;
		unsigned int _addrg:1;
		unsigned int _con5:2;
		unsigned int _reg5:2;
		unsigned int _con1:1;
		unsigned int _addr:1;
		unsigned int _addrj:1;
	} rule;
};

static short _nts_0[] = { 0 };
static short _nts_1[] = { _reg_NT, 0 };
static short _nts_2[] = { _reg_NT, _reg_NT, 0 };
static short _nts_3[] = { _fpN_NT, 0 };
static short _nts_4[] = { _fpN_NT, _reg_NT, 0 };
static short _nts_5[] = { _fpN_NT, _con_NT, 0 };
static short _nts_6[] = { _addrg_NT, 0 };
static short _nts_7[] = { _addrg_NT, _reg_NT, 0 };
static short _nts_8[] = { _con_NT, 0 };
static short _nts_9[] = { _reg_NT, _con_NT, 0 };
static short _nts_10[] = { _con5_NT, 0 };
static short _nts_11[] = { _reg_NT, _reg5_NT, 0 };
static short _nts_12[] = { _reg_NT, _con1_NT, 0 };
static short _nts_13[] = { _addrg_NT, _con_NT, 0 };
static short _nts_14[] = { _addr_NT, _reg_NT, 0 };
static short _nts_15[] = { _addr_NT, _con_NT, 0 };
static short _nts_16[] = { _addrg_NT, _con_NT, _con_NT, 0 };
static short _nts_17[] = { _addrj_NT, 0 };

static short *_nts[] = {
	0,	/* 0 */
	_nts_0,	/* 1 */
	_nts_0,	/* 2 */
	_nts_0,	/* 3 */
	_nts_1,	/* 4 */
	_nts_1,	/* 5 */
	_nts_1,	/* 6 */
	_nts_1,	/* 7 */
	_nts_1,	/* 8 */
	_nts_2,	/* 9 */
	_nts_0,	/* 10 */
	_nts_0,	/* 11 */
	_nts_0,	/* 12 */
	_nts_0,	/* 13 */
	_nts_0,	/* 14 */
	_nts_0,	/* 15 */
	_nts_0,	/* 16 */
	_nts_0,	/* 17 */
	_nts_3,	/* 18 */
	_nts_3,	/* 19 */
	_nts_3,	/* 20 */
	_nts_3,	/* 21 */
	_nts_4,	/* 22 */
	_nts_4,	/* 23 */
	_nts_4,	/* 24 */
	_nts_5,	/* 25 */
	_nts_5,	/* 26 */
	_nts_5,	/* 27 */
	_nts_0,	/* 28 */
	_nts_6,	/* 29 */
	_nts_6,	/* 30 */
	_nts_6,	/* 31 */
	_nts_7,	/* 32 */
	_nts_7,	/* 33 */
	_nts_7,	/* 34 */
	_nts_8,	/* 35 */
	_nts_1,	/* 36 */
	_nts_1,	/* 37 */
	_nts_1,	/* 38 */
	_nts_6,	/* 39 */
	_nts_1,	/* 40 */
	_nts_1,	/* 41 */
	_nts_1,	/* 42 */
	_nts_9,	/* 43 */
	_nts_2,	/* 44 */
	_nts_9,	/* 45 */
	_nts_2,	/* 46 */
	_nts_9,	/* 47 */
	_nts_2,	/* 48 */
	_nts_2,	/* 49 */
	_nts_2,	/* 50 */
	_nts_2,	/* 51 */
	_nts_9,	/* 52 */
	_nts_2,	/* 53 */
	_nts_9,	/* 54 */
	_nts_2,	/* 55 */
	_nts_2,	/* 56 */
	_nts_2,	/* 57 */
	_nts_9,	/* 58 */
	_nts_2,	/* 59 */
	_nts_9,	/* 60 */
	_nts_2,	/* 61 */
	_nts_1,	/* 62 */
	_nts_1,	/* 63 */
	_nts_1,	/* 64 */
	_nts_0,	/* 65 */
	_nts_0,	/* 66 */
	_nts_10,	/* 67 */
	_nts_1,	/* 68 */
	_nts_11,	/* 69 */
	_nts_11,	/* 70 */
	_nts_11,	/* 71 */
	_nts_11,	/* 72 */
	_nts_0,	/* 73 */
	_nts_12,	/* 74 */
	_nts_12,	/* 75 */
	_nts_2,	/* 76 */
	_nts_2,	/* 77 */
	_nts_2,	/* 78 */
	_nts_2,	/* 79 */
	_nts_2,	/* 80 */
	_nts_2,	/* 81 */
	_nts_1,	/* 82 */
	_nts_1,	/* 83 */
	_nts_1,	/* 84 */
	_nts_1,	/* 85 */
	_nts_1,	/* 86 */
	_nts_1,	/* 87 */
	_nts_1,	/* 88 */
	_nts_1,	/* 89 */
	_nts_7,	/* 90 */
	_nts_13,	/* 91 */
	_nts_14,	/* 92 */
	_nts_14,	/* 93 */
	_nts_14,	/* 94 */
	_nts_15,	/* 95 */
	_nts_15,	/* 96 */
	_nts_15,	/* 97 */
	_nts_16,	/* 98 */
	_nts_16,	/* 99 */
	_nts_1,	/* 100 */
	_nts_1,	/* 101 */
	_nts_1,	/* 102 */
	_nts_8,	/* 103 */
	_nts_8,	/* 104 */
	_nts_8,	/* 105 */
	_nts_0,	/* 106 */
	_nts_17,	/* 107 */
	_nts_1,	/* 108 */
	_nts_0,	/* 109 */
	_nts_2,	/* 110 */
	_nts_2,	/* 111 */
	_nts_2,	/* 112 */
	_nts_2,	/* 113 */
	_nts_2,	/* 114 */
	_nts_2,	/* 115 */
	_nts_2,	/* 116 */
	_nts_2,	/* 117 */
	_nts_2,	/* 118 */
	_nts_2,	/* 119 */
	_nts_2,	/* 120 */
	_nts_2,	/* 121 */
	_nts_1,	/* 122 */
	_nts_1,	/* 123 */
	_nts_1,	/* 124 */
	_nts_1,	/* 125 */
	_nts_17,	/* 126 */
	_nts_17,	/* 127 */
	_nts_17,	/* 128 */
	_nts_17,	/* 129 */
	_nts_17,	/* 130 */
	_nts_1,	/* 131 */
	_nts_1,	/* 132 */
	_nts_1,	/* 133 */
};

static char *_templates[] = {
/* 0 */	0,
/* 1 */	"# read register\n",	/* reg: INDIRI1(VREGP) */
/* 2 */	"# read register\n",	/* reg: INDIRU1(VREGP) */
/* 3 */	"# read register\n",	/* reg: INDIRP1(VREGP) */
/* 4 */	"# write register\n",	/* stmt: ASGNI1(VREGP,reg) */
/* 5 */	"# write register\n",	/* stmt: ASGNU1(VREGP,reg) */
/* 6 */	"# write register\n",	/* stmt: ASGNP1(VREGP,reg) */
/* 7 */	"",	/* stmt: reg */
/* 8 */	"# ARGB\n",	/* stmt: ARGB(INDIRB(reg)) */
/* 9 */	"# ASGNB\n",	/* stmt: ASGNB(reg,INDIRB(reg)) */
/* 10 */	"%a",	/* con: CNSTI1 */
/* 11 */	"%a",	/* con: CNSTU1 */
/* 12 */	"%a",	/* con: CNSTP1 */
/* 13 */	"# long constant\n",	/* reg: CNSTI1 */
/* 14 */	"# long constant\n",	/* reg: CNSTU1 */
/* 15 */	"# long constant\n",	/* reg: CNSTP1 */
/* 16 */	"%a",	/* fpN: ADDRFP1 */
/* 17 */	"%a",	/* fpN: ADDRLP1 */
/* 18 */	" # fpN\n\trdw R11\n\taddi %0\n\twrw %c\n",	/* reg: fpN */
/* 19 */	" # INDIRI1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRI1(fpN) */
/* 20 */	" # INDIRU1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRU1(fpN) */
/* 21 */	" # INDIRP1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRP1(fpN) */
/* 22 */	" # ASGNI1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNI1(fpN,reg) */
/* 23 */	" # ASGNU1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNU1(fpN,reg) */
/* 24 */	" # ASGNP1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNP1(fpN,reg) */
/* 25 */	" # ASGNI1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNI1(fpN,con) */
/* 26 */	" # ASGNU1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNU1(fpN,con) */
/* 27 */	" # ASGNP1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNP1(fpN,con) */
/* 28 */	" # ADDRGP1\n\tldi %a\n\taddi MEM_BASE\n\twrw %c\n",	/* addrg: ADDRGP1 */
/* 29 */	" # INDIRP1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRP1(addrg) */
/* 30 */	" # INDIRI1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRU1(addrg) */
/* 31 */	" # INDIRI1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRI1(addrg) */
/* 32 */	" # ASGNI1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNI1(addrg,reg) */
/* 33 */	" # ASGNU1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNU1(addrg,reg) */
/* 34 */	" # ASGNP1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNP1(addrg,reg) */
/* 35 */	" # reg: con\n\tldi %0\n\twrw %c\n",	/* reg: con */
/* 36 */	" # reg: INDIRI1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRI1(reg) */
/* 37 */	" # reg: INDIRU1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRU1(reg) */
/* 38 */	" # reg: INDIRP1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n",	/* reg: INDIRP1(reg) */
/* 39 */	"%0",	/* reg: addrg */
/* 40 */	" # LOADI1(reg)\n\trdw %0\n\twrw %c\n",	/* reg: LOADI1(reg) */
/* 41 */	" # LOADU1(reg)\n\trdw %0\n\twrw %c\n",	/* reg: LOADU1(reg) */
/* 42 */	" # LOADP1(reg)\n\trdw %0\n\twrw %c\n",	/* reg: LOADP1(reg) */
/* 43 */	" # ADDI1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n",	/* reg: ADDI1(reg,con) */
/* 44 */	" # ADDI1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n",	/* reg: ADDI1(reg,reg) */
/* 45 */	" # ADDU1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n",	/* reg: ADDU1(reg,con) */
/* 46 */	" # ADDU1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n",	/* reg: ADDU1(reg,reg) */
/* 47 */	" # ADDP1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n",	/* reg: ADDP1(reg,con) */
/* 48 */	" # ADDP1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n",	/* reg: ADDP1(reg,reg) */
/* 49 */	" # SUBI1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n",	/* reg: SUBI1(reg,reg) */
/* 50 */	" # SUBP1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n",	/* reg: SUBP1(reg,reg) */
/* 51 */	" # SUBU1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n",	/* reg: SUBU1(reg,reg) */
/* 52 */	" # BANDI1(reg,con)\n\tldi %1\n\tand %0\n\twrw %c\n",	/* reg: BANDI1(reg,con) */
/* 53 */	" # BANDI1(reg,reg)\n\trdw %0\n\tand %1\n\twrw %c\n",	/* reg: BANDI1(reg,reg) */
/* 54 */	" # BANDU1(reg,con)\n\tldi %1\n\tand %0\n\twrw %c\n",	/* reg: BANDU1(reg,con) */
/* 55 */	" # BANDU1(reg,reg)\n\trdw %0\n\tand %1\n\twrw %c\n",	/* reg: BANDU1(reg,reg) */
/* 56 */	" # BORI1 \n\tldi -1\n\txor %0\n\twrw %c\n\tldi -1\n\txor %1\n\tand %c\n\twrw %c\n\tldi -1\n\txor %c\n\twrw %c\n",	/* reg: BORI1(reg,reg) */
/* 57 */	" # BORU1 \n\tldi -1\n\txor %0\n\twrw %c\n\tldi -1\n\txor %1\n\tand %c\n\twrw %c\n\tldi -1\n\txor %c\n\twrw %c\n",	/* reg: BORU1(reg,reg) */
/* 58 */	" # BXORI1(reg,con)\n\tldi %1\n\txor %0\n\twrw %c\n",	/* reg: BXORI1(reg,con) */
/* 59 */	" # BXORI1(reg,reg)\n\trdw %0\n\txor %1\n\twrw %c\n",	/* reg: BXORI1(reg,reg) */
/* 60 */	" # BXORU1(reg,con)\n\tldi %1\n\txor %0\n\twrw %c\n",	/* reg: BXORU1(reg,con) */
/* 61 */	" # BXORU1(reg,reg)\n\trdw %0\n\txor %1\n\twrw %c\n",	/* reg: BXORU1(reg,reg) */
/* 62 */	" # NOT\n\tldi -1\n\txor %0\n\twrw %c\n",	/* reg: BCOMI1(reg) */
/* 63 */	" # NOT\n\tldi -1\n\txor %0\n\twrw %c\n",	/* reg: BCOMU1(reg) */
/* 64 */	" # NEG\n\tldi -1\n\txor %0\n\taddi 1\n\twrw %c\n",	/* reg: NEGI1(reg) */
/* 65 */	"%a",	/* con5: CNSTI1 */
/* 66 */	"%a",	/* con5: CNSTU1 */
/* 67 */	" # reg5: con5\n\tldi %0\n\twrw %c\n",	/* reg5: con5 */
/* 68 */	"%a",	/* reg5: reg */
/* 69 */	"# SHL\n",	/* reg: LSHI1(reg,reg5) */
/* 70 */	"# SHL\n",	/* reg: LSHU1(reg,reg5) */
/* 71 */	"# SHR\n",	/* reg: RSHI1(reg,reg5) */
/* 72 */	"# SHR\n",	/* reg: RSHU1(reg,reg5) */
/* 73 */	"%a",	/* con1: CNSTI1 */
/* 74 */	" # SHL 1\n\trdw %0\n\tshft -1\n\twrw %c\n",	/* reg: LSHI1(reg,con1) */
/* 75 */	" # SHR 1\n\trdw %0\n\tshft 1\n\twrw %c\n",	/* reg: RSHI1(reg,con1) */
/* 76 */	"# call _mul\n",	/* reg: MULI1(reg,reg) */
/* 77 */	"# call _umul\n",	/* reg: MULU1(reg,reg) */
/* 78 */	"# call _div\n",	/* reg: DIVI1(reg,reg) */
/* 79 */	"# call _udiv\n",	/* reg: DIVU1(reg,reg) */
/* 80 */	"# call _mod\n",	/* reg: MODI1(reg,reg) */
/* 81 */	"# call _umod\n",	/* reg: MODU1(reg,reg) */
/* 82 */	"# extend\n",	/* reg: CVII1(reg) */
/* 83 */	"# extend\n",	/* reg: CVIU1(reg) */
/* 84 */	"# extend\n",	/* reg: CVUI1(reg) */
/* 85 */	"# extend\n",	/* reg: CVUU1(reg) */
/* 86 */	"# extend\n",	/* reg: CVPU1(reg) */
/* 87 */	"# extend\n",	/* reg: CVUP1(reg) */
/* 88 */	"# extend\n",	/* reg: CVPP1(reg) */
/* 89 */	"%0",	/* addr: reg */
/* 90 */	" # ASGNI1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNI1(addrg,reg) */
/* 91 */	" # ASGNI1(addrg,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNI1(addrg,con) */
/* 92 */	" # ASGNI1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNI1(addr,reg) */
/* 93 */	" # ASGNU1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNU1(addr,reg) */
/* 94 */	" # ASGNP1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n",	/* stmt: ASGNP1(addr,reg) */
/* 95 */	" # ASGNI1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNI1(addr,con) */
/* 96 */	" # ASGNU1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNU1(addr,con) */
/* 97 */	" # ASGNP1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n",	/* stmt: ASGNP1(addr,con) */
/* 98 */	" # ASGN(ADD(INDIR(addrg),con),con)\n\twrw RB\n\trdwb\n\trdwb\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n",	/* stmt: ASGNI1(ADDP1(INDIRP1(addrg),con),con) */
/* 99 */	" # ASGN(ADD(addrg,con),con)\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n",	/* stmt: ASGNI1(ADDP1(addrg,con),con) */
/* 100 */	" # ARGI1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n",	/* stmt: ARGI1(reg) */
/* 101 */	" # ARGU1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n",	/* stmt: ARGU1(reg) */
/* 102 */	" # ARGP1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n",	/* stmt: ARGP1(reg) */
/* 103 */	" # ARGI1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n",	/* stmt: ARGI1(con) */
/* 104 */	" # ARGU1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n",	/* stmt: ARGU1(con) */
/* 105 */	" # ARGP1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n",	/* stmt: ARGP1(con) */
/* 106 */	"%a",	/* addrj: ADDRGP1 */
/* 107 */	" # JUMPV(addrj)\n\tldi 0\n\tbeqi %0\n\tnop\n",	/* stmt: JUMPV(addrj) */
/* 108 */	" # JUMPV(reg)\n\trdw %0\n\twrw RB\n\tldi 0\n\tbeqi RB\n\tnop\n",	/* stmt: JUMPV(reg) */
/* 109 */	" # LABELV\n%a\tnop\n",	/* stmt: LABELV */
/* 110 */	" # EQI1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tnop\n",	/* stmt: EQI1(reg,reg) */
/* 111 */	" # NEI1\n\trdw %0\n\tsub %1\n\tbneqi %a\n\tnop\n",	/* stmt: NEI1(reg,reg) */
/* 112 */	" # GEI1\n\trdw %0\n\tsub %1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbeqi %a\n\tnop\n",	/* stmt: GEI1(reg,reg) */
/* 113 */	" # LTI1\n\trdw %0\n\tsub %1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbneqi %a\n\tnop\n",	/* stmt: LTI1(reg,reg) */
/* 114 */	" # GTI1\n\trdw %0\n\tsub %1\n\taddi -1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbeqi %a\n\tnop\n",	/* stmt: GTI1(reg,reg) */
/* 115 */	" # LEI1\n\trdw %0\n\tsub %1\n\taddi -1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbneqi %a\n\tnop\n",	/* stmt: LEI1(reg,reg) */
/* 116 */	" # EQU1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tnop\n",	/* stmt: EQU1(reg,reg) */
/* 117 */	" # NEU1\n\trdw %0\n\tsub %1\n\tbneqi %a\n\tnop\n",	/* stmt: NEU1(reg,reg) */
/* 118 */	" # GEU1\n\trdw %0\n\tsub %1\n\tldi 1\n\tand RC\n\tbeqi %a\n\tnop\n",	/* stmt: GEU1(reg,reg) */
/* 119 */	" # LTU1\n\trdw %0\n\tsub %1\n\tldi 1\n\tand RC\n\tbneqi %a\n\tnop\n",	/* stmt: LTU1(reg,reg) */
/* 120 */	"# GTU1\n",	/* stmt: GTU1(reg,reg) */
/* 121 */	" # LEU1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tldi 1\n\tand RC\n\tbneqi %a\n\tnop\n",	/* stmt: LEU1(reg,reg) */
/* 122 */	"# call\n",	/* reg: CALLI1(reg) */
/* 123 */	"# call\n",	/* reg: CALLU1(reg) */
/* 124 */	"# call\n",	/* reg: CALLP1(reg) */
/* 125 */	"# call\n",	/* stmt: CALLV(reg) */
/* 126 */	"# call\n",	/* reg: CALLI1(addrj) */
/* 127 */	"# call\n",	/* reg: CALLU1(addrj) */
/* 128 */	"# call\n",	/* reg: CALLP1(addrj) */
/* 129 */	"# call\n",	/* stmt: CALLV(addrj) */
/* 130 */	" # ASM\n%0\n",	/* stmt: CALLASM(addrj) */
/* 131 */	"# ret\n",	/* stmt: RETI1(reg) */
/* 132 */	"# ret\n",	/* stmt: RETU1(reg) */
/* 133 */	"# ret\n",	/* stmt: RETP1(reg) */
};

static char _isinstruction[] = {
/* 0 */	0,
/* 1 */	1,	/* # read register\n */
/* 2 */	1,	/* # read register\n */
/* 3 */	1,	/* # read register\n */
/* 4 */	1,	/* # write register\n */
/* 5 */	1,	/* # write register\n */
/* 6 */	1,	/* # write register\n */
/* 7 */	0,	/*  */
/* 8 */	1,	/* # ARGB\n */
/* 9 */	1,	/* # ASGNB\n */
/* 10 */	0,	/* %a */
/* 11 */	0,	/* %a */
/* 12 */	0,	/* %a */
/* 13 */	1,	/* # long constant\n */
/* 14 */	1,	/* # long constant\n */
/* 15 */	1,	/* # long constant\n */
/* 16 */	0,	/* %a */
/* 17 */	0,	/* %a */
/* 18 */	1,	/*  # fpN\n\trdw R11\n\taddi %0\n\twrw %c\n */
/* 19 */	1,	/*  # INDIRI1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 20 */	1,	/*  # INDIRU1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 21 */	1,	/*  # INDIRP1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 22 */	1,	/*  # ASGNI1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 23 */	1,	/*  # ASGNU1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 24 */	1,	/*  # ASGNP1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 25 */	1,	/*  # ASGNI1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 26 */	1,	/*  # ASGNU1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 27 */	1,	/*  # ASGNP1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 28 */	1,	/*  # ADDRGP1\n\tldi %a\n\taddi MEM_BASE\n\twrw %c\n */
/* 29 */	1,	/*  # INDIRP1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 30 */	1,	/*  # INDIRI1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 31 */	1,	/*  # INDIRI1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 32 */	1,	/*  # ASGNI1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 33 */	1,	/*  # ASGNU1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 34 */	1,	/*  # ASGNP1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 35 */	1,	/*  # reg: con\n\tldi %0\n\twrw %c\n */
/* 36 */	1,	/*  # reg: INDIRI1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 37 */	1,	/*  # reg: INDIRU1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 38 */	1,	/*  # reg: INDIRP1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n */
/* 39 */	0,	/* %0 */
/* 40 */	1,	/*  # LOADI1(reg)\n\trdw %0\n\twrw %c\n */
/* 41 */	1,	/*  # LOADU1(reg)\n\trdw %0\n\twrw %c\n */
/* 42 */	1,	/*  # LOADP1(reg)\n\trdw %0\n\twrw %c\n */
/* 43 */	1,	/*  # ADDI1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n */
/* 44 */	1,	/*  # ADDI1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n */
/* 45 */	1,	/*  # ADDU1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n */
/* 46 */	1,	/*  # ADDU1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n */
/* 47 */	1,	/*  # ADDP1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n */
/* 48 */	1,	/*  # ADDP1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n */
/* 49 */	1,	/*  # SUBI1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n */
/* 50 */	1,	/*  # SUBP1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n */
/* 51 */	1,	/*  # SUBU1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n */
/* 52 */	1,	/*  # BANDI1(reg,con)\n\tldi %1\n\tand %0\n\twrw %c\n */
/* 53 */	1,	/*  # BANDI1(reg,reg)\n\trdw %0\n\tand %1\n\twrw %c\n */
/* 54 */	1,	/*  # BANDU1(reg,con)\n\tldi %1\n\tand %0\n\twrw %c\n */
/* 55 */	1,	/*  # BANDU1(reg,reg)\n\trdw %0\n\tand %1\n\twrw %c\n */
/* 56 */	1,	/*  # BORI1 \n\tldi -1\n\txor %0\n\twrw %c\n\tldi -1\n\txor %1\n\tand %c\n\twrw %c\n\tldi -1\n\txor %c\n\twrw %c\n */
/* 57 */	1,	/*  # BORU1 \n\tldi -1\n\txor %0\n\twrw %c\n\tldi -1\n\txor %1\n\tand %c\n\twrw %c\n\tldi -1\n\txor %c\n\twrw %c\n */
/* 58 */	1,	/*  # BXORI1(reg,con)\n\tldi %1\n\txor %0\n\twrw %c\n */
/* 59 */	1,	/*  # BXORI1(reg,reg)\n\trdw %0\n\txor %1\n\twrw %c\n */
/* 60 */	1,	/*  # BXORU1(reg,con)\n\tldi %1\n\txor %0\n\twrw %c\n */
/* 61 */	1,	/*  # BXORU1(reg,reg)\n\trdw %0\n\txor %1\n\twrw %c\n */
/* 62 */	1,	/*  # NOT\n\tldi -1\n\txor %0\n\twrw %c\n */
/* 63 */	1,	/*  # NOT\n\tldi -1\n\txor %0\n\twrw %c\n */
/* 64 */	1,	/*  # NEG\n\tldi -1\n\txor %0\n\taddi 1\n\twrw %c\n */
/* 65 */	0,	/* %a */
/* 66 */	0,	/* %a */
/* 67 */	1,	/*  # reg5: con5\n\tldi %0\n\twrw %c\n */
/* 68 */	0,	/* %a */
/* 69 */	1,	/* # SHL\n */
/* 70 */	1,	/* # SHL\n */
/* 71 */	1,	/* # SHR\n */
/* 72 */	1,	/* # SHR\n */
/* 73 */	0,	/* %a */
/* 74 */	1,	/*  # SHL 1\n\trdw %0\n\tshft -1\n\twrw %c\n */
/* 75 */	1,	/*  # SHR 1\n\trdw %0\n\tshft 1\n\twrw %c\n */
/* 76 */	1,	/* # call _mul\n */
/* 77 */	1,	/* # call _umul\n */
/* 78 */	1,	/* # call _div\n */
/* 79 */	1,	/* # call _udiv\n */
/* 80 */	1,	/* # call _mod\n */
/* 81 */	1,	/* # call _umod\n */
/* 82 */	1,	/* # extend\n */
/* 83 */	1,	/* # extend\n */
/* 84 */	1,	/* # extend\n */
/* 85 */	1,	/* # extend\n */
/* 86 */	1,	/* # extend\n */
/* 87 */	1,	/* # extend\n */
/* 88 */	1,	/* # extend\n */
/* 89 */	0,	/* %0 */
/* 90 */	1,	/*  # ASGNI1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 91 */	1,	/*  # ASGNI1(addrg,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 92 */	1,	/*  # ASGNI1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 93 */	1,	/*  # ASGNU1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 94 */	1,	/*  # ASGNP1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n */
/* 95 */	1,	/*  # ASGNI1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 96 */	1,	/*  # ASGNU1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 97 */	1,	/*  # ASGNP1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n */
/* 98 */	1,	/*  # ASGN(ADD(INDIR(addrg),con),con)\n\twrw RB\n\trdwb\n\trdwb\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n */
/* 99 */	1,	/*  # ASGN(ADD(addrg,con),con)\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n */
/* 100 */	1,	/*  # ARGI1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n */
/* 101 */	1,	/*  # ARGU1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n */
/* 102 */	1,	/*  # ARGP1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n */
/* 103 */	1,	/*  # ARGI1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n */
/* 104 */	1,	/*  # ARGU1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n */
/* 105 */	1,	/*  # ARGP1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n */
/* 106 */	0,	/* %a */
/* 107 */	1,	/*  # JUMPV(addrj)\n\tldi 0\n\tbeqi %0\n\tnop\n */
/* 108 */	1,	/*  # JUMPV(reg)\n\trdw %0\n\twrw RB\n\tldi 0\n\tbeqi RB\n\tnop\n */
/* 109 */	1,	/*  # LABELV\n%a\tnop\n */
/* 110 */	1,	/*  # EQI1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tnop\n */
/* 111 */	1,	/*  # NEI1\n\trdw %0\n\tsub %1\n\tbneqi %a\n\tnop\n */
/* 112 */	1,	/*  # GEI1\n\trdw %0\n\tsub %1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbeqi %a\n\tnop\n */
/* 113 */	1,	/*  # LTI1\n\trdw %0\n\tsub %1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbneqi %a\n\tnop\n */
/* 114 */	1,	/*  # GTI1\n\trdw %0\n\tsub %1\n\taddi -1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbeqi %a\n\tnop\n */
/* 115 */	1,	/*  # LEI1\n\trdw %0\n\tsub %1\n\taddi -1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbneqi %a\n\tnop\n */
/* 116 */	1,	/*  # EQU1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tnop\n */
/* 117 */	1,	/*  # NEU1\n\trdw %0\n\tsub %1\n\tbneqi %a\n\tnop\n */
/* 118 */	1,	/*  # GEU1\n\trdw %0\n\tsub %1\n\tldi 1\n\tand RC\n\tbeqi %a\n\tnop\n */
/* 119 */	1,	/*  # LTU1\n\trdw %0\n\tsub %1\n\tldi 1\n\tand RC\n\tbneqi %a\n\tnop\n */
/* 120 */	1,	/* # GTU1\n */
/* 121 */	1,	/*  # LEU1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tldi 1\n\tand RC\n\tbneqi %a\n\tnop\n */
/* 122 */	1,	/* # call\n */
/* 123 */	1,	/* # call\n */
/* 124 */	1,	/* # call\n */
/* 125 */	1,	/* # call\n */
/* 126 */	1,	/* # call\n */
/* 127 */	1,	/* # call\n */
/* 128 */	1,	/* # call\n */
/* 129 */	1,	/* # call\n */
/* 130 */	1,	/*  # ASM\n%0\n */
/* 131 */	1,	/* # ret\n */
/* 132 */	1,	/* # ret\n */
/* 133 */	1,	/* # ret\n */
};

static char *_string[] = {
/* 0 */	0,
/* 1 */	"reg: INDIRI1(VREGP)",
/* 2 */	"reg: INDIRU1(VREGP)",
/* 3 */	"reg: INDIRP1(VREGP)",
/* 4 */	"stmt: ASGNI1(VREGP,reg)",
/* 5 */	"stmt: ASGNU1(VREGP,reg)",
/* 6 */	"stmt: ASGNP1(VREGP,reg)",
/* 7 */	"stmt: reg",
/* 8 */	"stmt: ARGB(INDIRB(reg))",
/* 9 */	"stmt: ASGNB(reg,INDIRB(reg))",
/* 10 */	"con: CNSTI1",
/* 11 */	"con: CNSTU1",
/* 12 */	"con: CNSTP1",
/* 13 */	"reg: CNSTI1",
/* 14 */	"reg: CNSTU1",
/* 15 */	"reg: CNSTP1",
/* 16 */	"fpN: ADDRFP1",
/* 17 */	"fpN: ADDRLP1",
/* 18 */	"reg: fpN",
/* 19 */	"reg: INDIRI1(fpN)",
/* 20 */	"reg: INDIRU1(fpN)",
/* 21 */	"reg: INDIRP1(fpN)",
/* 22 */	"stmt: ASGNI1(fpN,reg)",
/* 23 */	"stmt: ASGNU1(fpN,reg)",
/* 24 */	"stmt: ASGNP1(fpN,reg)",
/* 25 */	"stmt: ASGNI1(fpN,con)",
/* 26 */	"stmt: ASGNU1(fpN,con)",
/* 27 */	"stmt: ASGNP1(fpN,con)",
/* 28 */	"addrg: ADDRGP1",
/* 29 */	"reg: INDIRP1(addrg)",
/* 30 */	"reg: INDIRU1(addrg)",
/* 31 */	"reg: INDIRI1(addrg)",
/* 32 */	"stmt: ASGNI1(addrg,reg)",
/* 33 */	"stmt: ASGNU1(addrg,reg)",
/* 34 */	"stmt: ASGNP1(addrg,reg)",
/* 35 */	"reg: con",
/* 36 */	"reg: INDIRI1(reg)",
/* 37 */	"reg: INDIRU1(reg)",
/* 38 */	"reg: INDIRP1(reg)",
/* 39 */	"reg: addrg",
/* 40 */	"reg: LOADI1(reg)",
/* 41 */	"reg: LOADU1(reg)",
/* 42 */	"reg: LOADP1(reg)",
/* 43 */	"reg: ADDI1(reg,con)",
/* 44 */	"reg: ADDI1(reg,reg)",
/* 45 */	"reg: ADDU1(reg,con)",
/* 46 */	"reg: ADDU1(reg,reg)",
/* 47 */	"reg: ADDP1(reg,con)",
/* 48 */	"reg: ADDP1(reg,reg)",
/* 49 */	"reg: SUBI1(reg,reg)",
/* 50 */	"reg: SUBP1(reg,reg)",
/* 51 */	"reg: SUBU1(reg,reg)",
/* 52 */	"reg: BANDI1(reg,con)",
/* 53 */	"reg: BANDI1(reg,reg)",
/* 54 */	"reg: BANDU1(reg,con)",
/* 55 */	"reg: BANDU1(reg,reg)",
/* 56 */	"reg: BORI1(reg,reg)",
/* 57 */	"reg: BORU1(reg,reg)",
/* 58 */	"reg: BXORI1(reg,con)",
/* 59 */	"reg: BXORI1(reg,reg)",
/* 60 */	"reg: BXORU1(reg,con)",
/* 61 */	"reg: BXORU1(reg,reg)",
/* 62 */	"reg: BCOMI1(reg)",
/* 63 */	"reg: BCOMU1(reg)",
/* 64 */	"reg: NEGI1(reg)",
/* 65 */	"con5: CNSTI1",
/* 66 */	"con5: CNSTU1",
/* 67 */	"reg5: con5",
/* 68 */	"reg5: reg",
/* 69 */	"reg: LSHI1(reg,reg5)",
/* 70 */	"reg: LSHU1(reg,reg5)",
/* 71 */	"reg: RSHI1(reg,reg5)",
/* 72 */	"reg: RSHU1(reg,reg5)",
/* 73 */	"con1: CNSTI1",
/* 74 */	"reg: LSHI1(reg,con1)",
/* 75 */	"reg: RSHI1(reg,con1)",
/* 76 */	"reg: MULI1(reg,reg)",
/* 77 */	"reg: MULU1(reg,reg)",
/* 78 */	"reg: DIVI1(reg,reg)",
/* 79 */	"reg: DIVU1(reg,reg)",
/* 80 */	"reg: MODI1(reg,reg)",
/* 81 */	"reg: MODU1(reg,reg)",
/* 82 */	"reg: CVII1(reg)",
/* 83 */	"reg: CVIU1(reg)",
/* 84 */	"reg: CVUI1(reg)",
/* 85 */	"reg: CVUU1(reg)",
/* 86 */	"reg: CVPU1(reg)",
/* 87 */	"reg: CVUP1(reg)",
/* 88 */	"reg: CVPP1(reg)",
/* 89 */	"addr: reg",
/* 90 */	"stmt: ASGNI1(addrg,reg)",
/* 91 */	"stmt: ASGNI1(addrg,con)",
/* 92 */	"stmt: ASGNI1(addr,reg)",
/* 93 */	"stmt: ASGNU1(addr,reg)",
/* 94 */	"stmt: ASGNP1(addr,reg)",
/* 95 */	"stmt: ASGNI1(addr,con)",
/* 96 */	"stmt: ASGNU1(addr,con)",
/* 97 */	"stmt: ASGNP1(addr,con)",
/* 98 */	"stmt: ASGNI1(ADDP1(INDIRP1(addrg),con),con)",
/* 99 */	"stmt: ASGNI1(ADDP1(addrg,con),con)",
/* 100 */	"stmt: ARGI1(reg)",
/* 101 */	"stmt: ARGU1(reg)",
/* 102 */	"stmt: ARGP1(reg)",
/* 103 */	"stmt: ARGI1(con)",
/* 104 */	"stmt: ARGU1(con)",
/* 105 */	"stmt: ARGP1(con)",
/* 106 */	"addrj: ADDRGP1",
/* 107 */	"stmt: JUMPV(addrj)",
/* 108 */	"stmt: JUMPV(reg)",
/* 109 */	"stmt: LABELV",
/* 110 */	"stmt: EQI1(reg,reg)",
/* 111 */	"stmt: NEI1(reg,reg)",
/* 112 */	"stmt: GEI1(reg,reg)",
/* 113 */	"stmt: LTI1(reg,reg)",
/* 114 */	"stmt: GTI1(reg,reg)",
/* 115 */	"stmt: LEI1(reg,reg)",
/* 116 */	"stmt: EQU1(reg,reg)",
/* 117 */	"stmt: NEU1(reg,reg)",
/* 118 */	"stmt: GEU1(reg,reg)",
/* 119 */	"stmt: LTU1(reg,reg)",
/* 120 */	"stmt: GTU1(reg,reg)",
/* 121 */	"stmt: LEU1(reg,reg)",
/* 122 */	"reg: CALLI1(reg)",
/* 123 */	"reg: CALLU1(reg)",
/* 124 */	"reg: CALLP1(reg)",
/* 125 */	"stmt: CALLV(reg)",
/* 126 */	"reg: CALLI1(addrj)",
/* 127 */	"reg: CALLU1(addrj)",
/* 128 */	"reg: CALLP1(addrj)",
/* 129 */	"stmt: CALLV(addrj)",
/* 130 */	"stmt: CALLASM(addrj)",
/* 131 */	"stmt: RETI1(reg)",
/* 132 */	"stmt: RETU1(reg)",
/* 133 */	"stmt: RETP1(reg)",
};

static short _decode_stmt[] = {
	0,
	4,
	5,
	6,
	7,
	8,
	9,
	22,
	23,
	24,
	25,
	26,
	27,
	32,
	33,
	34,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	125,
	129,
	130,
	131,
	132,
	133,
};

static short _decode_reg[] = {
	0,
	1,
	2,
	3,
	13,
	14,
	15,
	18,
	19,
	20,
	21,
	29,
	30,
	31,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	69,
	70,
	71,
	72,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	122,
	123,
	124,
	126,
	127,
	128,
};

static short _decode_con[] = {
	0,
	10,
	11,
	12,
};

static short _decode_fpN[] = {
	0,
	16,
	17,
};

static short _decode_addrg[] = {
	0,
	28,
};

static short _decode_con5[] = {
	0,
	65,
	66,
};

static short _decode_reg5[] = {
	0,
	67,
	68,
};

static short _decode_con1[] = {
	0,
	73,
};

static short _decode_addr[] = {
	0,
	89,
};

static short _decode_addrj[] = {
	0,
	106,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 10)
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case _stmt_NT:	return _decode_stmt[((struct _state *)state)->rule._stmt];
	case _reg_NT:	return _decode_reg[((struct _state *)state)->rule._reg];
	case _con_NT:	return _decode_con[((struct _state *)state)->rule._con];
	case _fpN_NT:	return _decode_fpN[((struct _state *)state)->rule._fpN];
	case _addrg_NT:	return _decode_addrg[((struct _state *)state)->rule._addrg];
	case _con5_NT:	return _decode_con5[((struct _state *)state)->rule._con5];
	case _reg5_NT:	return _decode_reg5[((struct _state *)state)->rule._reg5];
	case _con1_NT:	return _decode_con1[((struct _state *)state)->rule._con1];
	case _addr_NT:	return _decode_addr[((struct _state *)state)->rule._addr];
	case _addrj_NT:	return _decode_addrj[((struct _state *)state)->rule._addrj];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_con(NODEPTR_TYPE, int);
static void _closure_fpN(NODEPTR_TYPE, int);
static void _closure_addrg(NODEPTR_TYPE, int);
static void _closure_con5(NODEPTR_TYPE, int);

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 1;
		p->rule._addr = 1;
	}
	if (c + 0 < p->cost[_reg5_NT]) {
		p->cost[_reg5_NT] = c + 0;
		p->rule._reg5 = 2;
	}
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 4;
	}
}

static void _closure_con(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 2 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 2;
		p->rule._reg = 14;
		_closure_reg(a, c + 2);
	}
}

static void _closure_fpN(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 3 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 3;
		p->rule._reg = 7;
		_closure_reg(a, c + 3);
	}
}

static void _closure_addrg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 0;
		p->rule._reg = 18;
		_closure_reg(a, c + 0);
	}
}

static void _closure_con5(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 2 < p->cost[_reg5_NT]) {
		p->cost[_reg5_NT] = c + 2;
		p->rule._reg5 = 1;
	}
}

static void _label(NODEPTR_TYPE a) {
	int c;
	struct _state *p;

	if (!a)
		fatal("_label", "Null tree\n", 0);
	STATE_LABEL(a) = p = allocate(sizeof *p, FUNC);
	p->rule._stmt = 0;
	p->cost[1] =
	p->cost[2] =
	p->cost[3] =
	p->cost[4] =
	p->cost[5] =
	p->cost[6] =
	p->cost[7] =
	p->cost[8] =
	p->cost[9] =
	p->cost[10] =
		0x7fff;
	switch (OP_LABEL(a)) {
	case 41: /* ARGB */
		_label(LEFT_CHILD(a));
		if (	/* stmt: ARGB(INDIRB(reg)) */
			LEFT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 5;
			}
		}
		break;
	case 57: /* ASGNB */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNB(reg,INDIRB(reg)) */
			RIGHT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 6;
			}
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		break;
	case 215: /* CALLASM */
		_label(LEFT_CHILD(a));
		/* stmt: CALLASM(addrj) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrj_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 49;
		}
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 47;
		}
		/* stmt: CALLV(addrj) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrj_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 48;
		}
		break;
	case 217: /* CALLB */
		break;
	case 233: /* LOADB */
		break;
	case 248: /* RETV */
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(addrj) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrj_NT] + 3;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 32;
		}
		/* stmt: JUMPV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 33;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 34;
		}
		break;
	case 711: /* VREGP */
		break;
	case 1045: /* CNSTI1 */
		/* con: CNSTI1 */
		c = (range(a, -134217728, 134217727));
		if (c + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = c + 0;
			p->rule._con = 1;
			_closure_con(a, c + 0);
		}
		/* reg: CNSTI1 */
		if (2 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 2 + 0;
			p->rule._reg = 4;
			_closure_reg(a, 2 + 0);
		}
		/* con5: CNSTI1 */
		c = (range(a, 0, 32));
		if (c + 0 < p->cost[_con5_NT]) {
			p->cost[_con5_NT] = c + 0;
			p->rule._con5 = 1;
			_closure_con5(a, c + 0);
		}
		/* con1: CNSTI1 */
		c = (range(a, 1, 1));
		if (c + 0 < p->cost[_con1_NT]) {
			p->cost[_con1_NT] = c + 0;
			p->rule._con1 = 1;
		}
		break;
	case 1046: /* CNSTU1 */
		/* con: CNSTU1 */
		c = (range(a, -134217728, 134217727));
		if (c + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = c + 0;
			p->rule._con = 2;
			_closure_con(a, c + 0);
		}
		/* reg: CNSTU1 */
		if (2 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 2 + 0;
			p->rule._reg = 5;
			_closure_reg(a, 2 + 0);
		}
		/* con5: CNSTU1 */
		c = (range(a, 0, 32));
		if (c + 0 < p->cost[_con5_NT]) {
			p->cost[_con5_NT] = c + 0;
			p->rule._con5 = 2;
			_closure_con5(a, c + 0);
		}
		break;
	case 1047: /* CNSTP1 */
		/* con: CNSTP1 */
		c = (range(a, -134217728, 134217727));
		if (c + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = c + 0;
			p->rule._con = 3;
			_closure_con(a, c + 0);
		}
		/* reg: CNSTP1 */
		if (2 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 2 + 0;
			p->rule._reg = 6;
			_closure_reg(a, 2 + 0);
		}
		break;
	case 1061: /* ARGI1 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 26;
		}
		/* stmt: ARGI1(con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 29;
		}
		break;
	case 1062: /* ARGU1 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 27;
		}
		/* stmt: ARGU1(con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 30;
		}
		break;
	case 1063: /* ARGP1 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 28;
		}
		/* stmt: ARGP1(con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_con_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 31;
		}
		break;
	case 1077: /* ASGNI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 1;
			}
		}
		/* stmt: ASGNI1(fpN,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 7;
		}
		/* stmt: ASGNI1(fpN,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 10;
		}
		/* stmt: ASGNI1(addrg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 13;
		}
		/* stmt: ASGNI1(addrg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 16;
		}
		/* stmt: ASGNI1(addrg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 17;
		}
		/* stmt: ASGNI1(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 18;
		}
		/* stmt: ASGNI1(addr,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 21;
		}
		if (	/* stmt: ASGNI1(ADDP1(INDIRP1(addrg),con),con) */
			LEFT_CHILD(a)->op == 1335 && /* ADDP1 */
			LEFT_CHILD(LEFT_CHILD(a))->op == 1095 /* INDIRP1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(LEFT_CHILD(a))->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 7;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 24;
			}
		}
		if (	/* stmt: ASGNI1(ADDP1(addrg,con),con) */
			LEFT_CHILD(a)->op == 1335 /* ADDP1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(LEFT_CHILD(a))->x.state))->cost[_con_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 4;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 25;
			}
		}
		break;
	case 1078: /* ASGNU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 2;
			}
		}
		/* stmt: ASGNU1(fpN,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 8;
		}
		/* stmt: ASGNU1(fpN,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 11;
		}
		/* stmt: ASGNU1(addrg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 14;
		}
		/* stmt: ASGNU1(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 19;
		}
		/* stmt: ASGNU1(addr,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 22;
		}
		break;
	case 1079: /* ASGNP1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNP1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 3;
			}
		}
		/* stmt: ASGNP1(fpN,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 9;
		}
		/* stmt: ASGNP1(fpN,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 5;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 12;
		}
		/* stmt: ASGNP1(addrg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 15;
		}
		/* stmt: ASGNP1(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 20;
		}
		/* stmt: ASGNP1(addr,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 4;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 23;
		}
		break;
	case 1093: /* INDIRI1 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRI1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_fpN_NT] == 0) {
					p->cost[_fpN_NT] = 0;
					p->rule._fpN = q->rule._fpN;
				}
				if (q->cost[_addrg_NT] == 0) {
					p->cost[_addrg_NT] = 0;
					p->rule._addrg = q->rule._addrg;
				}
				if (q->cost[_con5_NT] == 0) {
					p->cost[_con5_NT] = 0;
					p->rule._con5 = q->rule._con5;
				}
				if (q->cost[_reg5_NT] == 0) {
					p->cost[_reg5_NT] = 0;
					p->rule._reg5 = q->rule._reg5;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_addrj_NT] == 0) {
					p->cost[_addrj_NT] = 0;
					p->rule._addrj = q->rule._addrj;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 1;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI1(fpN) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + 6;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 8;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI1(addrg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + 5;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 13;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 15;
			_closure_reg(a, c + 0);
		}
		break;
	case 1094: /* INDIRU1 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRU1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_fpN_NT] == 0) {
					p->cost[_fpN_NT] = 0;
					p->rule._fpN = q->rule._fpN;
				}
				if (q->cost[_addrg_NT] == 0) {
					p->cost[_addrg_NT] = 0;
					p->rule._addrg = q->rule._addrg;
				}
				if (q->cost[_con5_NT] == 0) {
					p->cost[_con5_NT] = 0;
					p->rule._con5 = q->rule._con5;
				}
				if (q->cost[_reg5_NT] == 0) {
					p->cost[_reg5_NT] = 0;
					p->rule._reg5 = q->rule._reg5;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_addrj_NT] == 0) {
					p->cost[_addrj_NT] = 0;
					p->rule._addrj = q->rule._addrj;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 2;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU1(fpN) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + 6;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 9;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU1(addrg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + 5;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 12;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 16;
			_closure_reg(a, c + 0);
		}
		break;
	case 1095: /* INDIRP1 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRP1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_fpN_NT] == 0) {
					p->cost[_fpN_NT] = 0;
					p->rule._fpN = q->rule._fpN;
				}
				if (q->cost[_addrg_NT] == 0) {
					p->cost[_addrg_NT] = 0;
					p->rule._addrg = q->rule._addrg;
				}
				if (q->cost[_con5_NT] == 0) {
					p->cost[_con5_NT] = 0;
					p->rule._con5 = q->rule._con5;
				}
				if (q->cost[_reg5_NT] == 0) {
					p->cost[_reg5_NT] = 0;
					p->rule._reg5 = q->rule._reg5;
				}
				if (q->cost[_con1_NT] == 0) {
					p->cost[_con1_NT] = 0;
					p->rule._con1 = q->rule._con1;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_addrj_NT] == 0) {
					p->cost[_addrj_NT] = 0;
					p->rule._addrj = q->rule._addrj;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 3;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRP1(fpN) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_fpN_NT] + 6;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 10;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRP1(addrg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrg_NT] + 5;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 11;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 5;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 17;
			_closure_reg(a, c + 0);
		}
		break;
	case 1157: /* CVII1 */
		_label(LEFT_CHILD(a));
		/* reg: CVII1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 56;
			_closure_reg(a, c + 0);
		}
		break;
	case 1158: /* CVIU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 57;
			_closure_reg(a, c + 0);
		}
		break;
	case 1175: /* CVPP1 */
		_label(LEFT_CHILD(a));
		/* reg: CVPP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		break;
	case 1176: /* CVPU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVPU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		break;
	case 1205: /* CVUI1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 58;
			_closure_reg(a, c + 0);
		}
		break;
	case 1206: /* CVUU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 59;
			_closure_reg(a, c + 0);
		}
		break;
	case 1207: /* CVUP1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 61;
			_closure_reg(a, c + 0);
		}
		break;
	case 1221: /* NEGI1 */
		_label(LEFT_CHILD(a));
		/* reg: NEGI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 4;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 43;
			_closure_reg(a, c + 0);
		}
		break;
	case 1237: /* CALLI1 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 63;
			_closure_reg(a, c + 0);
		}
		/* reg: CALLI1(addrj) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrj_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 66;
			_closure_reg(a, c + 0);
		}
		break;
	case 1238: /* CALLU1 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 64;
			_closure_reg(a, c + 0);
		}
		/* reg: CALLU1(addrj) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrj_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 67;
			_closure_reg(a, c + 0);
		}
		break;
	case 1239: /* CALLP1 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		/* reg: CALLP1(addrj) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addrj_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 68;
			_closure_reg(a, c + 0);
		}
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
			_closure_reg(a, c + 0);
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 20;
			_closure_reg(a, c + 0);
		}
		break;
	case 1255: /* LOADP1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 21;
			_closure_reg(a, c + 0);
		}
		break;
	case 1269: /* RETI1 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 50;
		}
		break;
	case 1270: /* RETU1 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 51;
		}
		break;
	case 1271: /* RETP1 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 52;
		}
		break;
	case 1287: /* ADDRGP1 */
		/* addrg: ADDRGP1 */
		if (3 + 0 < p->cost[_addrg_NT]) {
			p->cost[_addrg_NT] = 3 + 0;
			p->rule._addrg = 1;
			_closure_addrg(a, 3 + 0);
		}
		/* addrj: ADDRGP1 */
		if (0 + 0 < p->cost[_addrj_NT]) {
			p->cost[_addrj_NT] = 0 + 0;
			p->rule._addrj = 1;
		}
		break;
	case 1303: /* ADDRFP1 */
		/* fpN: ADDRFP1 */
		if (1 + 0 < p->cost[_fpN_NT]) {
			p->cost[_fpN_NT] = 1 + 0;
			p->rule._fpN = 1;
			_closure_fpN(a, 1 + 0);
		}
		break;
	case 1319: /* ADDRLP1 */
		/* fpN: ADDRLP1 */
		if (1 + 0 < p->cost[_fpN_NT]) {
			p->cost[_fpN_NT] = 1 + 0;
			p->rule._fpN = 2;
			_closure_fpN(a, 1 + 0);
		}
		break;
	case 1333: /* ADDI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 22;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 23;
			_closure_reg(a, c + 0);
		}
		break;
	case 1334: /* ADDU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDU1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 24;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 25;
			_closure_reg(a, c + 0);
		}
		break;
	case 1335: /* ADDP1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDP1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 26;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 27;
			_closure_reg(a, c + 0);
		}
		break;
	case 1349: /* SUBI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 28;
			_closure_reg(a, c + 0);
		}
		break;
	case 1350: /* SUBU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 30;
			_closure_reg(a, c + 0);
		}
		break;
	case 1351: /* SUBP1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBP1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		break;
	case 1365: /* LSHI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI1(reg,reg5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg5_NT] + 8;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 44;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI1(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 48;
			_closure_reg(a, c + 0);
		}
		break;
	case 1366: /* LSHU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU1(reg,reg5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg5_NT] + 8;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 45;
			_closure_reg(a, c + 0);
		}
		break;
	case 1381: /* MODI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 54;
			_closure_reg(a, c + 0);
		}
		break;
	case 1382: /* MODU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		break;
	case 1397: /* RSHI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI1(reg,reg5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg5_NT] + 8;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 46;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHI1(reg,con1) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con1_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		break;
	case 1398: /* RSHU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU1(reg,reg5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg5_NT] + 8;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 47;
			_closure_reg(a, c + 0);
		}
		break;
	case 1413: /* BANDI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 31;
			_closure_reg(a, c + 0);
		}
		/* reg: BANDI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 32;
			_closure_reg(a, c + 0);
		}
		break;
	case 1414: /* BANDU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDU1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 33;
			_closure_reg(a, c + 0);
		}
		/* reg: BANDU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		break;
	case 1429: /* BCOMI1 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		break;
	case 1430: /* BCOMU1 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 42;
			_closure_reg(a, c + 0);
		}
		break;
	case 1445: /* BORI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 10;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 35;
			_closure_reg(a, c + 0);
		}
		break;
	case 1446: /* BORU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 10;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 36;
			_closure_reg(a, c + 0);
		}
		break;
	case 1461: /* BXORI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORI1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		/* reg: BXORI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 38;
			_closure_reg(a, c + 0);
		}
		break;
	case 1462: /* BXORU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU1(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 39;
			_closure_reg(a, c + 0);
		}
		/* reg: BXORU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 40;
			_closure_reg(a, c + 0);
		}
		break;
	case 1477: /* DIVI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		break;
	case 1478: /* DIVU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 53;
			_closure_reg(a, c + 0);
		}
		break;
	case 1493: /* MULI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 50;
			_closure_reg(a, c + 0);
		}
		break;
	case 1494: /* MULU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 51;
			_closure_reg(a, c + 0);
		}
		break;
	case 1509: /* EQI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 35;
		}
		break;
	case 1510: /* EQU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 41;
		}
		break;
	case 1525: /* GEI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 37;
		}
		break;
	case 1526: /* GEU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 43;
		}
		break;
	case 1541: /* GTI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 9;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 39;
		}
		break;
	case 1542: /* GTU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 9;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 45;
		}
		break;
	case 1557: /* LEI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 9;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 40;
		}
		break;
	case 1558: /* LEU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 7;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 46;
		}
		break;
	case 1573: /* LTI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 8;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 38;
		}
		break;
	case 1574: /* LTU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 6;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 44;
		}
		break;
	case 1589: /* NEI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 36;
		}
		break;
	case 1590: /* NEU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 3;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 42;
		}
		break;
	default:
		fatal("_label", "Bad terminal %d\n", OP_LABEL(a));
	}
}

static void _kids(NODEPTR_TYPE p, int eruleno, NODEPTR_TYPE kids[]) {
	if (!p)
		fatal("_kids", "Null tree\n", 0);
	if (!kids)
		fatal("_kids", "Null kids\n", 0);
	switch (eruleno) {
	case 109: /* stmt: LABELV */
	case 106: /* addrj: ADDRGP1 */
	case 73: /* con1: CNSTI1 */
	case 66: /* con5: CNSTU1 */
	case 65: /* con5: CNSTI1 */
	case 28: /* addrg: ADDRGP1 */
	case 17: /* fpN: ADDRLP1 */
	case 16: /* fpN: ADDRFP1 */
	case 15: /* reg: CNSTP1 */
	case 14: /* reg: CNSTU1 */
	case 13: /* reg: CNSTI1 */
	case 12: /* con: CNSTP1 */
	case 11: /* con: CNSTU1 */
	case 10: /* con: CNSTI1 */
	case 3: /* reg: INDIRP1(VREGP) */
	case 2: /* reg: INDIRU1(VREGP) */
	case 1: /* reg: INDIRI1(VREGP) */
		break;
	case 6: /* stmt: ASGNP1(VREGP,reg) */
	case 5: /* stmt: ASGNU1(VREGP,reg) */
	case 4: /* stmt: ASGNI1(VREGP,reg) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 89: /* addr: reg */
	case 68: /* reg5: reg */
	case 67: /* reg5: con5 */
	case 39: /* reg: addrg */
	case 35: /* reg: con */
	case 18: /* reg: fpN */
	case 7: /* stmt: reg */
		kids[0] = p;
		break;
	case 8: /* stmt: ARGB(INDIRB(reg)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		break;
	case 9: /* stmt: ASGNB(reg,INDIRB(reg)) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	case 133: /* stmt: RETP1(reg) */
	case 132: /* stmt: RETU1(reg) */
	case 131: /* stmt: RETI1(reg) */
	case 130: /* stmt: CALLASM(addrj) */
	case 129: /* stmt: CALLV(addrj) */
	case 128: /* reg: CALLP1(addrj) */
	case 127: /* reg: CALLU1(addrj) */
	case 126: /* reg: CALLI1(addrj) */
	case 125: /* stmt: CALLV(reg) */
	case 124: /* reg: CALLP1(reg) */
	case 123: /* reg: CALLU1(reg) */
	case 122: /* reg: CALLI1(reg) */
	case 108: /* stmt: JUMPV(reg) */
	case 107: /* stmt: JUMPV(addrj) */
	case 105: /* stmt: ARGP1(con) */
	case 104: /* stmt: ARGU1(con) */
	case 103: /* stmt: ARGI1(con) */
	case 102: /* stmt: ARGP1(reg) */
	case 101: /* stmt: ARGU1(reg) */
	case 100: /* stmt: ARGI1(reg) */
	case 88: /* reg: CVPP1(reg) */
	case 87: /* reg: CVUP1(reg) */
	case 86: /* reg: CVPU1(reg) */
	case 85: /* reg: CVUU1(reg) */
	case 84: /* reg: CVUI1(reg) */
	case 83: /* reg: CVIU1(reg) */
	case 82: /* reg: CVII1(reg) */
	case 64: /* reg: NEGI1(reg) */
	case 63: /* reg: BCOMU1(reg) */
	case 62: /* reg: BCOMI1(reg) */
	case 42: /* reg: LOADP1(reg) */
	case 41: /* reg: LOADU1(reg) */
	case 40: /* reg: LOADI1(reg) */
	case 38: /* reg: INDIRP1(reg) */
	case 37: /* reg: INDIRU1(reg) */
	case 36: /* reg: INDIRI1(reg) */
	case 31: /* reg: INDIRI1(addrg) */
	case 30: /* reg: INDIRU1(addrg) */
	case 29: /* reg: INDIRP1(addrg) */
	case 21: /* reg: INDIRP1(fpN) */
	case 20: /* reg: INDIRU1(fpN) */
	case 19: /* reg: INDIRI1(fpN) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 121: /* stmt: LEU1(reg,reg) */
	case 120: /* stmt: GTU1(reg,reg) */
	case 119: /* stmt: LTU1(reg,reg) */
	case 118: /* stmt: GEU1(reg,reg) */
	case 117: /* stmt: NEU1(reg,reg) */
	case 116: /* stmt: EQU1(reg,reg) */
	case 115: /* stmt: LEI1(reg,reg) */
	case 114: /* stmt: GTI1(reg,reg) */
	case 113: /* stmt: LTI1(reg,reg) */
	case 112: /* stmt: GEI1(reg,reg) */
	case 111: /* stmt: NEI1(reg,reg) */
	case 110: /* stmt: EQI1(reg,reg) */
	case 97: /* stmt: ASGNP1(addr,con) */
	case 96: /* stmt: ASGNU1(addr,con) */
	case 95: /* stmt: ASGNI1(addr,con) */
	case 94: /* stmt: ASGNP1(addr,reg) */
	case 93: /* stmt: ASGNU1(addr,reg) */
	case 92: /* stmt: ASGNI1(addr,reg) */
	case 91: /* stmt: ASGNI1(addrg,con) */
	case 90: /* stmt: ASGNI1(addrg,reg) */
	case 81: /* reg: MODU1(reg,reg) */
	case 80: /* reg: MODI1(reg,reg) */
	case 79: /* reg: DIVU1(reg,reg) */
	case 78: /* reg: DIVI1(reg,reg) */
	case 77: /* reg: MULU1(reg,reg) */
	case 76: /* reg: MULI1(reg,reg) */
	case 75: /* reg: RSHI1(reg,con1) */
	case 74: /* reg: LSHI1(reg,con1) */
	case 72: /* reg: RSHU1(reg,reg5) */
	case 71: /* reg: RSHI1(reg,reg5) */
	case 70: /* reg: LSHU1(reg,reg5) */
	case 69: /* reg: LSHI1(reg,reg5) */
	case 61: /* reg: BXORU1(reg,reg) */
	case 60: /* reg: BXORU1(reg,con) */
	case 59: /* reg: BXORI1(reg,reg) */
	case 58: /* reg: BXORI1(reg,con) */
	case 57: /* reg: BORU1(reg,reg) */
	case 56: /* reg: BORI1(reg,reg) */
	case 55: /* reg: BANDU1(reg,reg) */
	case 54: /* reg: BANDU1(reg,con) */
	case 53: /* reg: BANDI1(reg,reg) */
	case 52: /* reg: BANDI1(reg,con) */
	case 51: /* reg: SUBU1(reg,reg) */
	case 50: /* reg: SUBP1(reg,reg) */
	case 49: /* reg: SUBI1(reg,reg) */
	case 48: /* reg: ADDP1(reg,reg) */
	case 47: /* reg: ADDP1(reg,con) */
	case 46: /* reg: ADDU1(reg,reg) */
	case 45: /* reg: ADDU1(reg,con) */
	case 44: /* reg: ADDI1(reg,reg) */
	case 43: /* reg: ADDI1(reg,con) */
	case 34: /* stmt: ASGNP1(addrg,reg) */
	case 33: /* stmt: ASGNU1(addrg,reg) */
	case 32: /* stmt: ASGNI1(addrg,reg) */
	case 27: /* stmt: ASGNP1(fpN,con) */
	case 26: /* stmt: ASGNU1(fpN,con) */
	case 25: /* stmt: ASGNI1(fpN,con) */
	case 24: /* stmt: ASGNP1(fpN,reg) */
	case 23: /* stmt: ASGNU1(fpN,reg) */
	case 22: /* stmt: ASGNI1(fpN,reg) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 98: /* stmt: ASGNI1(ADDP1(INDIRP1(addrg),con),con) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		kids[2] = RIGHT_CHILD(p);
		break;
	case 99: /* stmt: ASGNI1(ADDP1(addrg,con),con) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		kids[2] = RIGHT_CHILD(p);
		break;
	default:
		fatal("_kids", "Bad rule number %d\n", eruleno);
	}
}

static void progbeg(int argc, char *argv[]) {
	int i, noret = getenv("NORET") ? 1 : 0;
	parseflags(argc, argv);
	for (i = 0; i < 10; i++)
		intreg[i] = mkreg("R%d", i+1, 1, IREG);
	intregw = mkwildcard(intreg);

	tmask[IREG] = 0x003e; /* R1-R5 */
	vmask[IREG] = 0x07c0; /* R6-R10 */
	cseg = 0;
	doasm = 1;
	print("# VERSAT@lcc (IST: gcrs 2019)\n");
	print("# R12 = SP; R11 = FP\n");
	print("start\tldi MEM_BASE\n\taddi 0x1FF\n\twrw R12\n\twrw RB\n\tldi end\n\twrwb\n\tldi 0\n\tbeqi main\n\twrw R11\nend\t");
	if (!noret) print("ldi 0xF\n\tand R1\n\taddi 0x30\n\twrw CPRT_BASE\n\tldi 0xa\n\twrw CPRT_BASE\n\t");
	print("ldi 0\n\tbeqi PROG_ROM\n\tnop\n\n");
}
static Symbol rmap(int opk) {
	switch (optype(opk)) {
	case B:	case P:	case I:	case U:
		return intregw;
	default:
		return 0;
	}
}
static void segment(int n) {
	if (n == cseg)
		return;
	cseg = n;
	if (cseg == CODE)
		print("# TEXT\n");
	else if (cseg == DATA)
		print("# DATA\n");
	else if (cseg == LIT)
		print("# RODATA\n");
	else if (cseg == BSS)
		print("# BSS\n");
}
static void progend(void) {
	print("_end\t.memset 0\n"); /* for malloc */
	print("### The end ###\n");
}

/* CALL e RET no 'R1'(ACC) */
static void target(Node p) {
	assert(p);
	switch (specific(p->op)) {
	case CALL+I:	case CALL+U:	case CALL+P:
		setreg(p, intreg[ACC]);
		break;
	case RET+I:	case RET+U:	case RET+P:
		rtarget(p, 0, intreg[ACC]);
		break;
	/*
	case DIV+I: case DIV+U:
	case MOD+I: case MOD+U:
	case MUL+I: case MUL+U:
		setreg(p, intreg[ACC]);
		rtarget(p, 0, intreg[ACC]);
		rtarget(p, 1, intreg[ACC+1]);
		break;
	*/
	}
}

/* spill the clobbered registers before the instruction */
static void clobber(Node p) {
	static int nstack = 0;

	assert(p);
	nstack = ckstack(p, nstack);
	switch (specific(p->op)) {
	case ASGN+B:
		spill(ACC|(ACC+1), IREG, p);
		break;
	case CALL+I:	case CALL+U:	case CALL+P:
		spill(ACC, IREG, p);
	}
}
static void emit2(Node p) {
	int op = specific(p->op);
	/* fprintf(stderr, "%d: specific = %d generic = %d (%d)\n", p->op, op, generic(op), CNST+I); */
	if (generic(op) == CNST) {
		int reg = getregnum(p);
		print("\tldi 0x%x\n\tldih 0x%x\n\twrw R%d\n", p->syms[0]->u.value & 0xFFFFFFF, p->syms[0]->u.c.v.u >> 28, reg);
	}
	else if (generic(op) == LOAD || generic(op) == CVI || generic(op) == CVU || generic(op) == CVP) {
		char *dst = intreg[getregnum(p)]->x.name;
		char *src = intreg[getregnum(p->x.kids[0])]->x.name;
		int a = getregnum(p->x.kids[0]); /* %0 */
		int c = getregnum(p); /* %c */
		assert(opsize(p->op) <= opsize(p->x.kids[0]->op));
		if (dst != src)
			print("# MOV R%d,R%d\n\trdw R%d\n\twrw R%d\n", c, a, a, c);
		if (a != c)
			print("# MOV %s,%s\n\trdw %s\n\twrw %s\n", dst, src, src, dst);
	}
	else if (generic(op) == CALL) {
		int l = genlabel(1);
		char *n = p->syms[0]->x.name; /* %a */
		print("# CALL\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi L%d\n\twrwb\n", l);
		if (p->kids[0]->syms[0]) {
			char *f = p->kids[0]->syms[0]->x.name; /* %0 */
			print("\tldi 0\n\tbeqi %s\nL%d\tnop\n", f, l);
		} else {
			char *r = p->kids[0]->syms[2]->name; /* %0 */
			print("\trdw %s\n\twrw RB\n\tldi 0\n\tbeq RB\nL%d\tnop\n", r, l);
		}
		if (p->syms[0]->u.c.v.i > 0) print("\trdw R12\n\taddi %s\n\twrw R12\n", n);
	}
	else if (generic(op) == LSH) {
		int l = genlabel(2);
		int a = getregnum(p->x.kids[0]); /* %0 */
		int b = getregnum(p->x.kids[1]); /* %1 */
		int c = getregnum(p); /* %c */
		print("# SHL\n\trdw R%d\n\twrw R%d\n\trdw R%d\n\twrw RB\n\tbeqi L%d\n\tnop\nL%d\trdw R%d\n\tshft -1\n\twrw R%d\n\trdw RB\n\taddi -1\n\twrw RB\n\tbneqi L%d\nL%d\tnop\n", a, c, b, l+1, l, c, c, l, l+1);
	}
	else if (generic(op) == GT) {
		int l = genlabel(1);
		int a = getregnum(p->x.kids[0]);
		int b = getregnum(p->x.kids[1]);
		char *n = p->syms[0]->x.name; /* %a */
		print("# GTU1\n\trdw R%d\n\tsub R%d\n\tbeqi L%d\n\tldi 1\n\tand RC\n\tbneqi L%d\n\tldi 0\n\tbeqi %s\nL%d\tnop\n", a, b, l, l, n, l);
	}
	else if (generic(op) == RSH) {
		int l = genlabel(2);
		int a = getregnum(p->x.kids[0]);
		int b = getregnum(p->x.kids[1]);
		int c = getregnum(p);
		print("# SHR\n\trdw R%d\n\twrw R%d\n\trdw R%d\n\twrw RB\n\tbeqi L%d\n\tnop\nL%d\trdw R%d\n\tshft 1\n\twrw R%d\n\trdw RB\n\taddi -1\n\twrw RB\n\tbneqi L%d\nL%d\tnop\n", a, c, b, l+1, l, c, c, l, l+1);
	}
	else if (generic(op) == MUL || generic(op) == DIV || generic(op) == MOD) {
		int l = genlabel(1);
		int a = getregnum(p->x.kids[0]);
		int b = getregnum(p->x.kids[1]);
		int c = getregnum(p);
		char *opc = (op & 3) == 2 ? "_umul" : "_mul";
		if (generic(op) == DIV) opc = (op & 3) == 2 ? "_udiv" : "_div";
		if (generic(op) == MOD) opc = (op & 3) == 2 ? "_umod" : "_mod";
		print("# %s\n\trdw R12\n\taddi -1\n\twrw RB\n\trdw R%d\n\twrwb\n\trdw R12\n\taddi -2\n\twrw RB\n\trdw R%d\n\twrwb\n\trdw R12\n\taddi -3\n\twrw R12\n\twrw RB\n\tldi L%d\n\twrwb\n\tldi 0\n\tbeqi %s\nL%d\trdw R12\n\taddi 2\n\twrw R12\n\trdw R1\n\twrw R%d\n", opc, b, a, l, opc, l, c);
	}
	else if (op == ASGN+B) {
		int a = getregnum(p->x.kids[0]);
		int b = getregnum(p->x.kids[1]);
		print("## ASGNB=%d ## R%d -> #%d!%d -> R%d\n", p->op, a, p->syms[0]->u.c.v.i, p->syms[1]->u.c.v.i, b);
		blkloop(a, 0, b, 0, p->syms[0]->u.c.v.i, blkregs);
	}
	else if (op == ARG+B)
		print("## ARGB ##=%d\n", p->op);
	else if (generic(op) == RET)
		print("## RET=%d ##\n", p->op);
	else if (generic(op) == ASGN)
		print("## ASGN=%d ##\n", p->op);
	else if (generic(op) == INDIR)
		print("## INDIR=%d ##\n", p->op);
	else
		print("## emit2=%d ##\n", p->op);
}
static void doarg(Node p) {
	assert(p && p->syms[0]);
	mkactual(1, p->syms[0]->u.c.v.i);
}
static void blkfetch(int size, int off, int reg, int tmp) {
	if (size != 1) print("## blkfetch\n");
	else print("# blkfetch\n\trdw R%d\n\taddi %d\n\trdwb\n\trdwb\n\twrw R%d\n", reg, off, tmp);
}
static void blkstore(int size, int off, int reg, int tmp) {
	if (size != 1) print("## blkstore\n");
	else print("# blkstore\n\trdw R%d\n\taddi %d\n\twrw RB\n\trdw R%d\n\twrwb\n", reg, off, tmp);
}
static void blkloop(int dreg, int doff, int sreg, int soff, int size, int tmps[]) {
	int l = genlabel(2); /* use l and l+1 */
	print("## blkloop: copy R%d words from R%d to R%d (uses R%d to store value)\n", tmps[0], sreg, dreg, tmps[1]);
	if (soff) print("\trdw R%d\n\taddi %d\n\twrw R%d\n", sreg, soff, sreg); /* add offset to src */
	if (doff) print("\trdw R%d\n\taddi %d\n\twrw R%d\n", dreg, doff, dreg); /* add offset to dst */
	print("\tldi %d\n\twrw R%d\n", size, tmps[0]); /* init counter */
	print("L%d\trdw R%d\n\tbeqi L%d\n\twrw R%d # beqi decrements RA\n", l, tmps[0], l+1, tmps[0]);
	print("\trdw R%d\n\twrw RB\n\taddi 1\n\twrw R%d\n\trdwb\n\trdwb\n\twrw R%d\n", sreg, sreg, tmps[1]);
	print("\trdw R%d\n\twrw RB\n\taddi 1\n\twrw R%d\n\trdw R%d\n\twrwb\n", dreg, dreg, tmps[1]);
	print("\tldi 0\n\tbeqi L%d\nL%d\tnop\n", l, l+1);
}
static void local(Symbol p) {
	if (askregvar(p, (*IR->x.rmap)(ttob(p->type))) == 0)
		mkauto(p);
}
static void function(Symbol f, Symbol caller[], Symbol callee[], int ncalls) {
	int i, nargs = 0, dont_opt = 0, nofp = 0;

	for (i = 0; invalid[i]; i++)
		if (!strcmp(invalid[i], f->x.name))
			error("'%s' can not be used as a function name, in the versat backend\n", f->x.name);

	usedmask[0] = usedmask[1] = 0;
	freemask[0] = freemask[1] = ~(unsigned)0;
	offset = 1 + 1;
	for (i = 0; callee[i]; i++) {
		Symbol p = callee[i];
		Symbol q = caller[i];
		assert(q);
		p->x.offset = q->x.offset = offset;
		p->x.name = q->x.name = stringf("%d", offset);
		p->sclass = q->sclass = AUTO;
		offset += roundup(q->type->size, 1);
		if (isstruct(p->type))
			dont_opt = 1;
	}
	nargs = i;
	assert(caller[i] == 0);
	dont_opt |= variadic(f->type)
		|| (i > 0 && strcmp(callee[i-1]->name, "va_alist") == 0)
		|| isstruct(freturn(f->type));
	offset = maxoffset = 0;
	gencode(caller, callee);

	print("# %s ncalls=%d nargs=%d used=%x\n", f->x.name, ncalls, nargs, usedmask[IREG]);
	print("%s\tnop\n", f->x.name);
	if (!strcmp(f->x.name, "main") && getenv("NOSAV")) {
		usedmask[IREG] = 0;
		print("# NOSAV in main\n");
	}
	offset = 1 + 1;
	for (i = 2; i <= 10; i++) /* Don't save R1 */
		if (usedmask[IREG]&(1<<i)) {
			print("# PUSH r%d\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw R%d\n\twrwb\n", i, i);
			offset += 1;
		}

	for (i = 0; callee[i]; i++) {
		Symbol p = callee[i];
		Symbol q = caller[i];
		assert(q);
		p->x.offset = q->x.offset = offset;
		p->x.name = q->x.name = stringf("%d", offset);
		offset += roundup(q->type->size, 1);
	}
	framesize = roundup(maxoffset, 1);
	if (!nargs && !framesize) nofp = 1;
	if (!nofp)
		print("# save fp: PUSH fp; MOV fp, sp\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw R11\n\twrwb\n\trdw R12\n\twrw R11\n");
	if (framesize > 0) {
		print("# alloc var space: SUB sp, %d\n\trdw R12\n\taddi %d\n\twrw R12\n", framesize, -framesize);
	}
	print("# %s {begin} framesize=%d nofp=%d\n", f->x.name, framesize, nofp);
	emitcode();
	print("# %s {end}\n", f->x.name);
	if (!nofp)
		print("# restore fp: MOV sp, fp; POP fp\n\trdw R11\n\twrw R12\n\twrw RB\n\trdwb\n\trdwb\n\twrw R11\n\trdw R12\n\taddi 1\n\twrw R12\n");
	for (i = 10; i >= 2; i--)
		if (usedmask[IREG]&(1<<i))
			print("# POP r%d\n\trdw R12\n\twrw RB\n\trdwb\n\trdwb\n\twrw R%d\n\trdw R12\n\taddi 1\n\twrw R12\n", i, i);
	print("# RET\n\trdw R12\n\twrw RB\n\trdwb\n\trdwb\n\twrw RB\n\trdw R12\n\taddi 1\n\twrw R12\n\tldi 0\n\tbeq RB\n\tnop\n\n");
}
static void defsymbol(Symbol p) {
	if (p->scope >= LOCAL && p->sclass == STATIC)
		p->x.name = stringf("L%d", genlabel(1));
	else if (p->generated)
		p->x.name = stringf("L%s", p->name);
	else if (p->scope == GLOBAL || p->sclass == EXTERN)
		p->x.name = stringf("%s", p->name);
	else
		p->x.name = p->name;
}
static void address(Symbol q, Symbol p, long n) {
	if (p->scope == GLOBAL
	|| p->sclass == STATIC || p->sclass == EXTERN) {
		q->x.name = p->x.name;
		if (n > 0)
			q->x.name = stringf("%s\n\taddi %D", p->x.name, n);
	} else {
		assert(n <= INT_MAX && n >= INT_MIN);
		q->x.offset = p->x.offset + n;
		q->x.name = stringd(q->x.offset);
	}
}
static void defconst(int suffix, int size, Value v) {
	if (suffix == I || suffix == U || suffix == P)
		print("\t.memset %u\n", v.u); /* va does not sign extend */
	else {
		print("\t.memset %g\n", v.d);
		error("'%g' floating point not supported.\n", v.d);
	}
}
static void defaddress(Symbol p) {
	print("\t.memset %s\n", p->x.name);
}
static void defstring(int n, char *str) {
	char *s;

	for (s = str; s < str + n; s++)
		print("\t.memset 0x%x\n", *s);
}
static void export(Symbol p) {
	print("# global %s\n", p->x.name);
}
static void import(Symbol p) {
	if (p->ref > 0) {
		print("# extern %s\n", p->x.name);
	}
}
static void global(Symbol p) {
	int i;
	for (i = 0; invalid[i]; i++)
		if (!strcmp(invalid[i], p->x.name))
			error("'%s' can not be used as a name, in the versat backend\n", p->x.name);
	print("%s", p->x.name);
	if (p->u.seg == BSS)
		for (i = 0; i < p->type->size; i++)
			print("\t.memset 0x00\n");
}
static void space(int n) {
	int i;
	if (cseg != BSS)
		for (i = 0; i < n; i++)
			print("\t.memset 0x00\n");
}
Interface pico0IR = {
	1, 1, 0, /* char */
	1, 1, 0, /* short */
	1, 1, 0, /* int */
	1, 1, 0, /* long */
	2, 1, 0, /* long long */
	1, 1, 1, /* float */
	2, 1, 1, /* double */
	2, 1, 1, /* long double */
	1, 1, 0, /* T * */
	0, 1, 0, /* struct; so that ARGB keeps stack aligned */
	1,	/* little_endian */
	1,	/* mulops_calls */
	0,	/* wants_callb */
	0,	/* wants_argb */
	0,	/* left_to_right */
	0,	/* wants_dag */
	0,	/* unsigned_char */
	address,
	blockbeg,
	blockend,
	defaddress,
	defconst,
	defstring,
	defsymbol,
	emit,
	export,
	function,
	gen,
	global,
	import,
	local,
	progbeg,
	progend,
	segment,
	space,
	0, 0, 0, 0, 0, 0, 0,
	{ 1, rmap,
		blkfetch, blkstore, blkloop,
		_label,
		_rule,
		_nts,
		_kids,
		_string,
		_templates,
		_isinstruction,
		_ntname,
		emit2,
		doarg,
		target,
		clobber,
	}
};
static char rcsid[] = "$Id: versat.md,v 1.02 2019/07/30 21:43:32 gcrs Exp $";
