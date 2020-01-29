35,36c35,36
< "DELAY_SLOTS", "MEM_BASE", "beqi", "R14", "R15", "xor", "sub", "R10",
< "R11", "wrw", "add", "RB", "ldih", "PROG_ADDR_W", "addi", "R4", "R5",
---
> "DELAY_SLOTS", "MEM_BASE", "SEL_ADDR_W", "beqi", "R14", "R15", "xor",
> "sub", "R10", "R11", "wrw", "add", "RB", "ldih", "addi", "R4", "R5",
38,40c38,40
< "CPRT_BASE", "DATA_W", "R12", "OPCODESZ", "R13", "rdw", "beq", "ADDR_W",
< "PROG_ROM_ADDR_W", "PROG_ROM", "PROG_RAM", "shft", "wrwb", "INSTR_W",
< "PROG_RAM_ADDR_W", "bneqi", "REGF_ADDR_W", "nop", "wrc", 0 };
---
> "CPRT_BASE", "TRAP_BASE", "DATA_W", "R12", "OPCODESZ", "R13", "rdw",
> "beq", "ADDR_W", "shft", "wrwb", "INSTR_W", "bneqi", "REGF_ADDR_W",
> "nop", "wrc", 0 };
116c116
< addrg:	ADDRGP1		" # ADDRGP1\n\tldi %a\n\taddi MEM_BASE\n\twrw %c\n"	3
---
> addrg:	ADDRGP1		" # ADDRGP1\n\tldi %a\n\twrw %c\n"	3
126c126
< reg:	ADDRGP1		" # reg: ADDRGP1\n\tldi %a\n\taddi MEM_BASE\n\twrw %c\n"	3
---
> reg:	ADDRGP1		" # reg: ADDRGP1\n\tldi %a\n\twrw %c\n"	3
184,202c184,201
< addrb:	ADDRGP1		" # ADDRGP1\n\tldi %a\n\taddi MEM_BASE\n"	2
< stmt:	ASGNI1(ADDP1(INDIRP1(addrb),con),con) " # ASGN(ADD(INDIR(addrb),con),con)\n\twrw RB\n\trdwb\n\trdwb\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n" 7
< stmt:	ASGNI1(ADDP1(addrb,con),con) " # ASGN(ADD(addrb,con),con)\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n" 4
---
> stmt:	ASGNI1(ADDP1(INDIRP1(addrg),con),con) " # ASGN(ADD(INDIR(addrg),con),con)\n\twrw RB\n\trdwb\n\trdwb\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n" 7
> stmt:	ASGNI1(ADDP1(addrg,con),con) " # ASGN(ADD(addrg,con),con)\n\taddi %1\n\twrw RB\n\tldi %2\n\twrwb\n" 4
245c244
< 	print("start\tldi MEM_BASE\n\taddi 0x1FF\n\twrw R12\n\twrw RB\n\tldi end\n\twrwb\n\tldi 0\n\tbeqi main\n\twrw R11\nend\t");
---
> 	print("start\tldi 0x1FFF\n\twrw R12 # SP=TOP\n\twrw RB\n\tldi end\n\twrwb\n\tldi 0\n\tbeqi main\n\twrw R11 #FP=0\nend\t");
247c246
< 	print("ldi 0\n\tbeqi PROG_ROM\n\tnop\n\n");
---
> 	print("wrw TRAP_BASE\n");
