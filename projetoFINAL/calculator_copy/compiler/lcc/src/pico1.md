%{
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
"DELAY_SLOTS", "MEM_BASE", "SEL_ADDR_W", "beqi", "R14", "R15", "xor",
"sub", "R10", "R11", "wrw", "add", "RB", "ldih", "addi", "R4", "R5",
"R6", "R7", "R0", "R1", "R2", "R3", "RC", "R8", "REGF_BASE", "R9",
"CPRT_BASE", "TRAP_BASE", "DATA_W", "R12", "OPCODESZ", "R13", "rdw",
"beq", "ADDR_W", "shft", "wrwb", "INSTR_W", "bneqi", "REGF_ADDR_W",
"nop", "wrc", 0 };
static int blkregs[] = { ACC+1, ACC+2 };
%}
%start stmt
%term CNSTI1=1045 CNSTU1=1046 CNSTP1=1047
%term ARGB=41
%term ARGI1=1061 ARGU1=1062 ARGP1=1063
%term ASGNB=57
%term ASGNI1=1077 ASGNU1=1078 ASGNP1=1079
%term INDIRB=73
%term INDIRI1=1093 INDIRU1=1094 INDIRP1=1095
%term CVII1=1157 CVIU1=1158
%term CVPP1=1175 CVPU1=1176
%term CVUI1=1205 CVUU1=1206 CVUP1=1207
%term NEGI1=1221
%term CALLASM=215 CALLV=216 CALLB=217
%term CALLI1=1237 CALLU1=1238 CALLP1=1239
%term RETV=248 RETI1=1269 RETU1=1270 RETP1=1271
%term ADDRGP1=1287 ADDRFP1=1303 ADDRLP1=1319
%term ADDI1=1333 ADDU1=1334 ADDP1=1335
%term SUBI1=1349 SUBU1=1350 SUBP1=1351
%term LSHI1=1365 LSHU1=1366
%term MODI1=1381 MODU1=1382
%term RSHI1=1397 RSHU1=1398
%term BANDI1=1413 BANDU1=1414
%term BCOMI1=1429 BCOMU1=1430
%term BORI1=1445 BORU1=1446
%term BXORI1=1461 BXORU1=1462
%term DIVI1=1477 DIVU1=1478
%term MULI1=1493 MULU1=1494
%term EQI1=1509 EQU1=1510
%term GEI1=1525 GEU1=1526
%term GTI1=1541 GTU1=1542
%term LEI1=1557 LEU1=1558
%term LTI1=1573 LTU1=1574
%term NEI1=1589 NEU1=1590
%term JUMPV=584
%term LABELV=600
%term LOADB=233
%term LOADI1=1253 LOADU1=1254 LOADP1=1255
%term VREGP=711
%%
reg:	INDIRI1(VREGP)	"# read register\n"
reg:	INDIRU1(VREGP)	"# read register\n"
reg:	INDIRP1(VREGP)	"# read register\n"

stmt:	ASGNI1(VREGP,reg)	"# write register\n"
stmt:	ASGNU1(VREGP,reg)	"# write register\n"
stmt:	ASGNP1(VREGP,reg)	"# write register\n"
stmt:	reg	""

stmt: ARGB(INDIRB(reg))  "# ARGB\n"
stmt: ASGNB(reg,INDIRB(reg))  "# ASGNB\n"

con:	CNSTI1	"%a" range(a, -134217728, 134217727)
con:	CNSTU1	"%a" range(a, -134217728, 134217727)
con:	CNSTP1	"%a" range(a, -134217728, 134217727)

reg:	CNSTI1	"# long constant\n" 2
reg:	CNSTU1	"# long constant\n" 2
reg:	CNSTP1	"# long constant\n" 2

fpN:	ADDRFP1 "%a" 1
fpN:	ADDRLP1 "%a" 1

reg:	fpN " # fpN\n\trdw R11\n\taddi %0\n\twrw %c\n" 3
reg:	INDIRI1(fpN) " # INDIRI1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n" 6
reg:	INDIRU1(fpN) " # INDIRU1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n" 6
reg:	INDIRP1(fpN) " # INDIRP1(fpN)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n" 6
stmt:	ASGNI1(fpN,reg)	" # ASGNI1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n" 5
stmt:	ASGNU1(fpN,reg)	" # ASGNU1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n" 5
stmt:	ASGNP1(fpN,reg)	" # ASGNP1(fpN,reg)\n\trdw R11\n\taddi %0\n\twrw RB\n\trdw %1\n\twrwb\n" 5
stmt:	ASGNI1(fpN,con)	" # ASGNI1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n" 5
stmt:	ASGNU1(fpN,con)	" # ASGNU1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n" 5
stmt:	ASGNP1(fpN,con)	" # ASGNP1(fpN,con)\n\trdw R11\n\taddi %0\n\twrw RB\n\tldi %1\n\twrwb\n" 5

addrg:	ADDRGP1		" # ADDRGP1\n\tldi %a\n\twrw %c\n"	3
reg:	INDIRP1(addrg)	" # INDIRP1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n" 5
reg:	INDIRU1(addrg)	" # INDIRI1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n" 5
reg:	INDIRI1(addrg)	" # INDIRI1(addrg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n" 5
stmt:	ASGNI1(addrg,reg)	" # ASGNI1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n" 4
stmt:	ASGNU1(addrg,reg)	" # ASGNU1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n" 4
stmt:	ASGNP1(addrg,reg)	" # ASGNP1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n" 4

reg:	con		" # reg: con\n\tldi %0\n\twrw %c\n"	2
reg:	INDIRI1(reg)	" # reg: INDIRI1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n"	5
reg:	INDIRU1(reg)	" # reg: INDIRU1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n"	5
reg:	INDIRP1(reg)	" # reg: INDIRP1(reg)\n\trdw %0\n\twrw RB\n\trdwb\n\trdwb\n\twrw %c\n"	5
reg:	addrg	"%0"

reg:	LOADI1(reg)	" # LOADI1(reg)\n\trdw %0\n\twrw %c\n" move(a)
reg:	LOADU1(reg)	" # LOADU1(reg)\n\trdw %0\n\twrw %c\n" move(a)
reg:	LOADP1(reg)	" # LOADP1(reg)\n\trdw %0\n\twrw %c\n" move(a)

reg:	ADDI1(reg,con)	" # ADDI1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n" 3
reg:	ADDI1(reg,reg)	" # ADDI1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n" 3
reg:	ADDU1(reg,con)	" # ADDU1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n" 3
reg:	ADDU1(reg,reg)	" # ADDU1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n" 3
reg:	ADDP1(reg,con)	" # ADDP1(reg,con)\n\trdw %0\n\taddi %1\n\twrw %c\n" 3
reg:	ADDP1(reg,reg)	" # ADDP1(reg,reg)\n\trdw %0\n\tadd %1\n\twrw %c\n" 3
reg:	SUBI1(reg,reg)	" # SUBI1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n" 3
reg:	SUBP1(reg,reg)	" # SUBP1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n" 3
reg:	SUBU1(reg,reg)	" # SUBU1(reg,reg)\n\trdw %0\n\tsub %1\n\twrw %c\n" 3

reg:	BANDI1(reg,con)	" # BANDI1(reg,con)\n\tldi %1\n\tand %0\n\twrw %c\n" 3
reg:	BANDI1(reg,reg)	" # BANDI1(reg,reg)\n\trdw %0\n\tand %1\n\twrw %c\n" 3
reg:	BANDU1(reg,con)	" # BANDU1(reg,con)\n\tldi %1\n\tand %0\n\twrw %c\n" 3
reg:	BANDU1(reg,reg)	" # BANDU1(reg,reg)\n\trdw %0\n\tand %1\n\twrw %c\n" 3
reg:	BORI1(reg,reg)	" # BORI1 \n\tldi -1\n\txor %0\n\twrw %c\n\tldi -1\n\txor %1\n\tand %c\n\twrw %c\n\tldi -1\n\txor %c\n\twrw %c\n" 10
reg:	BORU1(reg,reg)	" # BORU1 \n\tldi -1\n\txor %0\n\twrw %c\n\tldi -1\n\txor %1\n\tand %c\n\twrw %c\n\tldi -1\n\txor %c\n\twrw %c\n" 10
reg:	BXORI1(reg,con)	" # BXORI1(reg,con)\n\tldi %1\n\txor %0\n\twrw %c\n" 3
reg:	BXORI1(reg,reg)	" # BXORI1(reg,reg)\n\trdw %0\n\txor %1\n\twrw %c\n" 3
reg:	BXORU1(reg,con)	" # BXORU1(reg,con)\n\tldi %1\n\txor %0\n\twrw %c\n" 3
reg:	BXORU1(reg,reg)	" # BXORU1(reg,reg)\n\trdw %0\n\txor %1\n\twrw %c\n" 3
reg:	BCOMI1(reg)	" # NOT\n\tldi -1\n\txor %0\n\twrw %c\n" 3
reg:	BCOMU1(reg)	" # NOT\n\tldi -1\n\txor %0\n\twrw %c\n" 3
reg:	NEGI1(reg)	" # NEG\n\tldi -1\n\txor %0\n\taddi 1\n\twrw %c\n" 4

con5:	CNSTI1	"%a"	range(a, 0, 32)
con5:	CNSTU1	"%a"	range(a, 0, 32)
reg5:	con5		" # reg5: con5\n\tldi %0\n\twrw %c\n"	2
reg5:	reg	"%a"
reg:	LSHI1(reg,reg5)	"# SHL\n" 8
reg:	LSHU1(reg,reg5)	"# SHL\n" 8
reg:	RSHI1(reg,reg5)	"# SHR\n" 8
reg:	RSHU1(reg,reg5)	"# SHR\n" 8

con1:	CNSTI1	"%a"	range(a, 1, 1)
reg:	LSHI1(reg,con1)	" # SHL 1\n\trdw %0\n\tshft -1\n\twrw %c\n" 3
reg:	RSHI1(reg,con1)	" # SHR 1\n\trdw %0\n\tshft 1\n\twrw %c\n" 3

reg:	MULI1(reg,reg)	"# call _mul\n" 1
reg:	MULU1(reg,reg)	"# call _umul\n" 1
reg:	DIVI1(reg,reg)	"# call _div\n" 1
reg:	DIVU1(reg,reg)	"# call _udiv\n" 1
reg:	MODI1(reg,reg)	"# call _mod\n" 1
reg:	MODU1(reg,reg)	"# call _umod\n" 1

reg:	CVII1(reg)	"# extend\n"	move(a)
reg:	CVIU1(reg)	"# extend\n"	move(a)
reg:	CVUI1(reg)	"# extend\n"	move(a)
reg:	CVUU1(reg)	"# extend\n"	move(a)
reg:	CVPU1(reg)	"# extend\n"	move(a)
reg:	CVUP1(reg)	"# extend\n"	move(a)
reg:	CVPP1(reg)	"# extend\n"	move(a)

addr:	reg	"%0"	1
stmt:	ASGNI1(addrg,reg)	" # ASGNI1(addrg,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n"	5
stmt:	ASGNI1(addrg,con)	" # ASGNI1(addrg,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n"	5
stmt:	ASGNI1(addr,reg)	" # ASGNI1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n"	4
stmt:	ASGNU1(addr,reg)	" # ASGNU1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n"	4
stmt:	ASGNP1(addr,reg)	" # ASGNP1(addr,reg)\n\trdw %0\n\twrw RB\n\trdw %1\n\twrwb\n"	4
stmt:	ASGNI1(addr,con)	" # ASGNI1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n"	4
stmt:	ASGNU1(addr,con)	" # ASGNU1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n"	4
stmt:	ASGNP1(addr,con)	" # ASGNP1(addr,con)\n\trdw %0\n\twrw RB\n\tldi %1\n\twrwb\n"	4

stmt:	ASGNI1(ADDP1(INDIRP1(addrg),con),con) " # ASGN(ADD(INDIR(addrg),con),con)\n\twrw RB\n\trdwb\n\trdwb\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n" 7
stmt:	ASGNI1(ADDP1(addrg,con),con) " # ASGN(ADD(addrg,con),con)\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n" 4

stmt:	ARGI1(reg)	" # ARGI1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n"	6
stmt:	ARGU1(reg)	" # ARGU1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n"	6
stmt:	ARGP1(reg)	" # ARGP1(reg)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\trdw %0\n\twrwb\n"	6
stmt:	ARGI1(con)	" # ARGI1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n"	6
stmt:	ARGU1(con)	" # ARGU1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n"	6
stmt:	ARGP1(con)	" # ARGP1(con)\n\trdw R12\n\taddi -1\n\twrw R12\n\twrw RB\n\tldi %0\n\twrwb\n"	6

addrj:	ADDRGP1	"%a"
stmt:	JUMPV(addrj)	" # JUMPV(addrj)\n\tldi 0\n\tbeqi %0\n\tnop\n"	3
stmt:	JUMPV(reg)	" # JUMPV(reg)\n\trdw %0\n\twrw RB\n\tldi 0\n\tbeqi RB\n\tnop\n"	5
stmt:	LABELV	" # LABELV\n%a\tnop\n"

stmt:	EQI1(reg,reg)	" # EQI1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tnop\n"	3
stmt:	NEI1(reg,reg)	" # NEI1\n\trdw %0\n\tsub %1\n\tbneqi %a\n\tnop\n"	3
stmt:	GEI1(reg,reg)	" # GEI1\n\trdw %0\n\tsub %1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbeqi %a\n\tnop\n"	8
stmt:	LTI1(reg,reg)	" # LTI1\n\trdw %0\n\tsub %1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbneqi %a\n\tnop\n"	8
stmt:	GTI1(reg,reg)	" # GTI1\n\trdw %0\n\tsub %1\n\taddi -1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbeqi %a\n\tnop\n"	9
stmt:	LEI1(reg,reg)	" # LEI1\n\trdw %0\n\tsub %1\n\taddi -1\n\twrw RB\n\tldi 0\n\tldih 0x8\n\tand RB\n\tbneqi %a\n\tnop\n"	9
stmt:	EQU1(reg,reg)	" # EQU1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tnop\n"	3
stmt:	NEU1(reg,reg)	" # NEU1\n\trdw %0\n\tsub %1\n\tbneqi %a\n\tnop\n"	3
stmt:	GEU1(reg,reg)	" # GEU1\n\trdw %0\n\tsub %1\n\tldi 1\n\tand RC\n\tbeqi %a\n\tnop\n"	6
stmt:	LTU1(reg,reg)	" # LTU1\n\trdw %0\n\tsub %1\n\tldi 1\n\tand RC\n\tbneqi %a\n\tnop\n"	6
stmt:	GTU1(reg,reg)	"# GTU1\n"	9
stmt:	LEU1(reg,reg)	" # LEU1\n\trdw %0\n\tsub %1\n\tbeqi %a\n\tldi 1\n\tand RC\n\tbneqi %a\n\tnop\n"	7

reg:	CALLI1(reg)	"# call\n" 1
reg:	CALLU1(reg)	"# call\n" 1
reg:	CALLP1(reg)	"# call\n" 1
stmt:	CALLV(reg)	"# call\n" 1

reg:	CALLI1(addrj)	"# call\n" 1
reg:	CALLU1(addrj)	"# call\n" 1
reg:	CALLP1(addrj)	"# call\n" 1
stmt:	CALLV(addrj)	"# call\n" 1
stmt:	CALLASM(addrj)	" # ASM\n%0\n"	1

stmt:	RETI1(reg)	"# ret\n"
stmt:	RETU1(reg)	"# ret\n"
stmt:	RETP1(reg)	"# ret\n"
%%
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
	print("start\tldi 0x1FFF\n\twrw R12 # SP=TOP\n\twrw RB\n\tldi end\n\twrwb\n\tldi 0\n\tbeqi main\n\twrw R11 #FP=0\nend\t");
	if (!noret) print("ldi 0xF\n\tand R1\n\taddi 0x30\n\twrw CPRT_BASE\n\tldi 0xa\n\twrw CPRT_BASE\n\t");
	print("wrw TRAP_BASE\n");
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
Interface pico1IR = {
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
